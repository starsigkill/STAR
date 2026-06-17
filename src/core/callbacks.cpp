#include "core/callbacks.h"

class CBAccess : public CCallbackBase {
public:
    static void set_registered(CCallbackBase* cb, bool reg) {
        CBAccess* a = static_cast<CBAccess*>(cb);
        if (reg) a->m_nCallbackFlags |= k_ECallbackFlagsRegistered;
        else a->m_nCallbackFlags &= ~(uint8)k_ECallbackFlagsRegistered;
    }
};

std::unordered_map<int, std::vector<CCallbackBase*>> g_callbacks;
std::map<uint64_t, PendingResult> g_pending_results;
std::map<uint64_t, CCallbackBase*> g_callresult_regs;
std::vector<QueuedCallback> g_callback_queue;
uint64_t g_next_api_call = 1;
std::mutex g_callbacks_mutex;

bool g_manual_dispatch_enabled = false;
std::deque<QueuedManualCallback> g_manual_callback_queue;
std::vector<uint8_t> g_last_callback_data;


void STAR_RegisterCallback(CCallbackBase* cb, int id)
{
    if (!cb) return;
    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    auto& vec = g_callbacks[id];
    for (auto* existing : vec) {
        if (existing == cb) return;
    }
    vec.push_back(cb);
    CBAccess::set_registered(cb, true);
    STAR_LOG("RegisterCallback id=%d", id);
}

void STAR_UnregisterCallback(CCallbackBase* cb)
{
    if (!cb) return;
    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    for (auto& kv : g_callbacks) {
        auto& vec = kv.second;
        vec.erase(std::remove(vec.begin(), vec.end(), cb), vec.end());
    }
    CBAccess::set_registered(cb, false);
}

void STAR_RegisterCallResult(CCallbackBase* cb, uint64_t handle)
{
    if (!cb || handle == 0) return;
    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    g_callresult_regs[handle] = cb;
}

void STAR_UnregisterCallResult(CCallbackBase* cb, uint64_t handle)
{
    STAR_UNREFERENCED(cb);
    if (handle == 0) return;
    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    g_callresult_regs.erase(handle);
}

uint64_t STAR_ReserveCallHandle()
{
    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    return g_next_api_call++;
}

uint64_t STAR_PostCallResult(int cb_id, const void* data, size_t size, bool io_fail, uint64_t reserved_handle)
{
    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    uint64_t handle = (reserved_handle != 0) ? reserved_handle : g_next_api_call++;
    PendingResult pr;
    pr.callback_id = cb_id;
    pr.io_failure = io_fail;
    if (data && size > 0) {
        pr.data.resize(size);
        memcpy(pr.data.data(), data, size);
    }
    g_pending_results[handle] = std::move(pr);
    STAR_LOG("PostCallResult handle=%llu cb_id=%d", handle, cb_id);

    if (g_manual_dispatch_enabled) {
        #pragma pack(push, 8)
        struct SteamAPICallCompleted_t {
            uint64_t m_hAsyncCall;
            int m_iCallback;
            uint32_t m_cubParam;
        };
        #pragma pack(pop)

        SteamAPICallCompleted_t completed;
        completed.m_hAsyncCall = handle;
        completed.m_iCallback = cb_id;
        completed.m_cubParam = (uint32_t)size;

        QueuedManualCallback qmc;
        qmc.hSteamUser = 1;
        qmc.iCallback = 503;
        qmc.data.resize(sizeof(completed));
        memcpy(qmc.data.data(), &completed, sizeof(completed));
        g_manual_callback_queue.push_back(std::move(qmc));
    }

    return handle;
}

void STAR_PostCallback(int cb_id, const void* data, size_t size)
{
    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    if (g_manual_dispatch_enabled) {
        QueuedManualCallback qmc;
        qmc.hSteamUser = 1;
        qmc.iCallback = cb_id;
        if (data && size > 0) {
            qmc.data.resize(size);
            memcpy(qmc.data.data(), data, size);
        }
        g_manual_callback_queue.push_back(std::move(qmc));
    } else {
        QueuedCallback qc;
        qc.callback_id = cb_id;
        if (data && size > 0) {
            qc.data.resize(size);
            memcpy(qc.data.data(), data, size);
        }
        g_callback_queue.push_back(std::move(qc));
    }
}

void STAR_RunCallbacks()
{

    std::vector<QueuedCallback> queued;
    {
        std::lock_guard<std::mutex> lock(g_callbacks_mutex);
        queued.swap(g_callback_queue);
    }
    for (auto& qc : queued) {
        void* pData = qc.data.empty() ? nullptr : qc.data.data();
        STAR_DispatchCallback(qc.callback_id, pData, qc.data.size());
    }

    struct Work { uint64_t handle; int cb_id; std::vector<uint8_t> data; bool io_fail; CCallbackBase* cr; bool broadcast; };
    std::vector<Work> work;
    {
        std::lock_guard<std::mutex> lock(g_callbacks_mutex);
        for (auto& [handle, pr] : g_pending_results) {
            auto it = g_callresult_regs.find(handle);
            CCallbackBase* cr = (it != g_callresult_regs.end()) ? it->second : nullptr;

            bool broadcast = (cr == nullptr) && !pr.broadcast_done && !g_manual_dispatch_enabled;
            if (cr || broadcast) {
                work.push_back({handle, pr.callback_id, pr.data, pr.io_failure, cr, broadcast});
                pr.broadcast_done = pr.broadcast_done || broadcast;
            }
        }
    }

    for (auto& w : work) {
        void* pData = w.data.empty() ? nullptr : w.data.data();
        if (w.cr) {
            w.cr->Run(pData, w.io_fail, w.handle);
        } else if (w.broadcast) {
            STAR_DispatchCallback(w.cb_id, pData, w.data.size());
        }
    }

    {
        std::lock_guard<std::mutex> lock(g_callbacks_mutex);
        for (auto& w : work) {
            if (w.cr) {
                g_pending_results.erase(w.handle);
                g_callresult_regs.erase(w.handle);
            } else if (w.broadcast) {
                g_pending_results.erase(w.handle);
            }
        }
    }
}

void STAR_DispatchCallback(int cb_id, const void* data, size_t size)
{
    STAR_UNREFERENCED(size);
    std::vector<CCallbackBase*> cbs;
    {
        std::lock_guard<std::mutex> lock(g_callbacks_mutex);
        auto it = g_callbacks.find(cb_id);
        if (it != g_callbacks.end()) {
            cbs = it->second;
        }
    }
    for (auto* cb : cbs) {
        if (cb) {
            cb->Run(const_cast<void*>(data));
        }
    }
}
