#pragma once
#include "core/star_common.h"
#include "steam/steam_api_common.h"

extern std::unordered_map<int, std::vector<CCallbackBase*>> g_callbacks;

struct PendingResult {
    int callback_id = 0;
    std::vector<uint8_t> data;
    bool io_failure = false;
    bool broadcast_done = false;
};
extern std::map<uint64_t, PendingResult> g_pending_results;
extern std::map<uint64_t, CCallbackBase*> g_callresult_regs;
extern uint64_t g_next_api_call;
extern std::mutex g_callbacks_mutex;

struct QueuedCallback {
    int callback_id = 0;
    std::vector<uint8_t> data;
};
extern std::vector<QueuedCallback> g_callback_queue;

struct QueuedManualCallback {
    HSteamUser hSteamUser;
    int iCallback;
    std::vector<uint8_t> data;
};
extern bool g_manual_dispatch_enabled;
extern std::deque<QueuedManualCallback> g_manual_callback_queue;
extern std::vector<uint8_t> g_last_callback_data;


void STAR_RegisterCallback(CCallbackBase* cb, int id);
void STAR_UnregisterCallback(CCallbackBase* cb);
void STAR_RegisterCallResult(CCallbackBase* cb, uint64_t handle);
void STAR_UnregisterCallResult(CCallbackBase* cb, uint64_t handle);

uint64_t STAR_ReserveCallHandle();
uint64_t STAR_PostCallResult(int cb_id, const void* data, size_t size, bool io_fail = false, uint64_t reserved_handle = 0);

void STAR_PostCallback(int cb_id, const void* data, size_t size);
void STAR_RunCallbacks();
void STAR_DispatchCallback(int cb_id, const void* data, size_t size);
