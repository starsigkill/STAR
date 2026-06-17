#include "overlay.h"
#include "core/settings.h"
#include "steam/steam_user_stats.h"
#include "steam/steam_utils.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_dx12.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_vulkan.h"
#include <MinHook.h>
#include <d3d9.h>
#include <d3d12.h>
#include <vulkan/vulkan.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

static StarOverlay* g_overlay = nullptr;
#ifdef _WIN64
void* StarOverlay::g_dx12_captured_queue_ = nullptr;
#endif

static float clamp01(float v) { return v < 0.f ? 0.f : v > 1.f ? 1.f : v; }
static float easeOut(float t) { float f = 1.f - t; return 1.f - f * f * f; }

static ImU32 col(uint8_t r, uint8_t g, uint8_t b, float a = 1.f) {
    return IM_COL32(r, g, b, (int)(a * 255.f + .5f));
}
static ImVec4 v4(uint8_t r, uint8_t g, uint8_t b, float a = 1.f) {
    return { r / 255.f, g / 255.f, b / 255.f, a };
}

#define P_BG0    0x1a,0x1a,0x1a
#define P_BG1    0x22,0x22,0x22
#define P_BG2    0x2a,0x2a,0x2a
#define P_SEP    0x35,0x35,0x35
#define P_TXT    0xf2,0xf2,0xf2
#define P_MUT    0x80,0x80,0x80
#define P_DIM    0x4a,0x4a,0x4a
#define P_ACC    0x4f,0xa3,0xff
#define P_GRN    0x4c,0xb8,0x4c

LRESULT CALLBACK StarOverlay::star_wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    if (!g_overlay) goto passthrough;

    if (msg == WM_KEYDOWN && wp == VK_TAB && (GetKeyState(VK_SHIFT) & 0x8000)) {
        g_overlay->open_ = !g_overlay->open_;
        if (g_overlay->open_) {
            if (g_overlay->orig_clip_cursor_) g_overlay->orig_clip_cursor_(nullptr); else ClipCursor(nullptr);

            int current = g_overlay->orig_show_cursor_ ? g_overlay->orig_show_cursor_(TRUE) : ShowCursor(TRUE);
            if (g_overlay->orig_show_cursor_) g_overlay->orig_show_cursor_(FALSE); else ShowCursor(FALSE);
            current--;

            g_overlay->cursor_show_count_offset_ = 0;
            if (current < 0) {
                while (current < 0) {
                    if (g_overlay->orig_show_cursor_) g_overlay->orig_show_cursor_(TRUE); else ShowCursor(TRUE);
                    g_overlay->cursor_show_count_offset_++;
                    current++;
                }
            }
            HCURSOR arrow = LoadCursor(nullptr, IDC_ARROW);
            if (g_overlay->orig_set_cursor_) g_overlay->orig_set_cursor_(arrow); else SetCursor(arrow);
        } else {
            while (g_overlay->cursor_show_count_offset_ > 0) {
                if (g_overlay->orig_show_cursor_) g_overlay->orig_show_cursor_(FALSE); else ShowCursor(FALSE);
                g_overlay->cursor_show_count_offset_--;
            }
        }
        return 0;
    }

    if (g_overlay->open_ && msg == WM_SETCURSOR) {
        HCURSOR arrow = LoadCursor(nullptr, IDC_ARROW);
        if (g_overlay->orig_set_cursor_) g_overlay->orig_set_cursor_(arrow); else SetCursor(arrow);
        return TRUE;
    }

    if (g_overlay->open_) {
        if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wp, lp))
            return TRUE;
        switch (msg) {
        case WM_LBUTTONDOWN: case WM_LBUTTONUP:
        case WM_RBUTTONDOWN: case WM_RBUTTONUP:
        case WM_MOUSEMOVE:   case WM_MOUSEWHEEL:
        case WM_KEYDOWN:     case WM_KEYUP:    case WM_CHAR:
            return 0;
        }
    }

passthrough:
    return g_overlay
        ? (IsWindowUnicode(hwnd)
            ? CallWindowProcW(g_overlay->wnd_proc_orig_, hwnd, msg, wp, lp)
            : CallWindowProcA(g_overlay->wnd_proc_orig_, hwnd, msg, wp, lp))
        : (IsWindowUnicode(hwnd)
            ? DefWindowProcW(hwnd, msg, wp, lp)
            : DefWindowProcA(hwnd, msg, wp, lp));
}

StarOverlay& StarOverlay::get()
{
    static StarOverlay instance;
    return instance;
}

void StarOverlay::init()
{
    g_overlay = this;
    enabled_  = Settings::get().overlay_enabled;
    if (!enabled_) return;
    if (hooks_installed_) return;
    if (MH_Initialize() != MH_OK) STAR_LOG("MinHook init failed");

    HMODULE user32 = GetModuleHandleA("user32.dll");
    if (!user32) user32 = LoadLibraryA("user32.dll");
    if (user32) {
        void* pShowCursor = (void*)GetProcAddress(user32, "ShowCursor");
        if (MH_CreateHook(pShowCursor, &hooked_ShowCursor, (void**)&orig_show_cursor_) == MH_OK) {
            MH_EnableHook(pShowCursor);
            STAR_LOG("ShowCursor hooked");
        }
        void* pClipCursor = (void*)GetProcAddress(user32, "ClipCursor");
        if (MH_CreateHook(pClipCursor, &hooked_ClipCursor, (void**)&orig_clip_cursor_) == MH_OK) {
            MH_EnableHook(pClipCursor);
            STAR_LOG("ClipCursor hooked");
        }
        void* pSetCursor = (void*)GetProcAddress(user32, "SetCursor");
        if (MH_CreateHook(pSetCursor, &hooked_SetCursor, (void**)&orig_set_cursor_) == MH_OK) {
            MH_EnableHook(pSetCursor);
            STAR_LOG("SetCursor hooked");
        }
    }

    hook_dx9();
    hook_dx11();
    hook_opengl();
    hook_vulkan();
    hooks_installed_ = true;
}

void StarOverlay::hook_window()
{
    if (hwnd_ && !wnd_proc_orig_) {
        if (IsWindowUnicode(hwnd_)) {
            wnd_proc_orig_ = (WNDPROC)SetWindowLongPtrW(hwnd_, GWLP_WNDPROC, (LONG_PTR)star_wnd_proc);
        } else {
            wnd_proc_orig_ = (WNDPROC)SetWindowLongPtrA(hwnd_, GWLP_WNDPROC, (LONG_PTR)star_wnd_proc);
        }
    }
}

void StarOverlay::shutdown()
{
    if (!enabled_) return;
    std::lock_guard<std::mutex> lock(render_mutex_);
    GraphicsAPI api_snapshot = active_api_;

    while (cursor_show_count_offset_ > 0) {
        if (orig_show_cursor_) orig_show_cursor_(FALSE); else ShowCursor(FALSE);
        cursor_show_count_offset_--;
    }

    if (hwnd_ && wnd_proc_orig_) {
        if (IsWindowUnicode(hwnd_)) {
            SetWindowLongPtrW(hwnd_, GWLP_WNDPROC, (LONG_PTR)wnd_proc_orig_);
        } else {
            SetWindowLongPtrA(hwnd_, GWLP_WNDPROC, (LONG_PTR)wnd_proc_orig_);
        }
        wnd_proc_orig_ = nullptr;
    }

    if (imgui_initialized_) {
        if (active_api_ == GraphicsAPI::DX11) {
            ImGui_ImplDX11_Shutdown();
#ifdef _WIN64
        } else if (active_api_ == GraphicsAPI::DX12) {
            ImGui_ImplDX12_Shutdown();
#endif
        } else if (active_api_ == GraphicsAPI::DX9) {
            ImGui_ImplDX9_Shutdown();
        } else if (active_api_ == GraphicsAPI::OpenGL) {
            ImGui_ImplOpenGL3_Shutdown();
        } else if (active_api_ == GraphicsAPI::Vulkan) {
            ImGui_ImplVulkan_Shutdown();
        }
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        imgui_initialized_ = false;
        active_api_ = GraphicsAPI::None;
    }

    cleanup_rtv();
#ifdef _WIN64
    cleanup_dx12();
#endif
    cleanup_vulkan();

    if (api_snapshot == GraphicsAPI::DX11 || api_snapshot == GraphicsAPI::DX9) {
        for (auto& [k, v] : icon_textures_) if (v) ((ID3D11ShaderResourceView*)v)->Release();
    }
    icon_textures_.clear();
    if (context_) { context_->Release(); context_ = nullptr; }
    if (device_)  { device_->Release();  device_  = nullptr; }
    hook_attempted_ = false;
    hooks_installed_ = false;
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    g_overlay = nullptr;
}

void StarOverlay::hook_dx11()
{
    if (hook_attempted_) return;
    hook_attempted_ = true;

    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(wc); wc.lpfnWndProc = DefWindowProcA;
    wc.hInstance = GetModuleHandleA(nullptr); wc.lpszClassName = "STAR_Dummy";
    RegisterClassExA(&wc);
    HWND dummy = CreateWindowExA(0,"STAR_Dummy","",WS_OVERLAPPEDWINDOW,0,0,4,4,
                                 nullptr,nullptr,wc.hInstance,nullptr);
    if (!dummy) return;

    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferCount = 1; sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.Width = sd.BufferDesc.Height = 4;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = dummy; sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE; sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    ID3D11Device* ddev = nullptr; IDXGISwapChain* dsc = nullptr; D3D_FEATURE_LEVEL fl;
    HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr,D3D_DRIVER_TYPE_HARDWARE,nullptr,0,
        nullptr,0,D3D11_SDK_VERSION,&sd,&dsc,&ddev,&fl,nullptr);
    if (FAILED(hr)||!dsc) { DestroyWindow(dummy); return; }

    void** vt = *(void***)dsc;
    if (MH_CreateHook(vt[8],  &hooked_Present,       (void**)&orig_present_) == MH_OK) MH_EnableHook(vt[8]);
    if (MH_CreateHook(vt[13], &hooked_ResizeBuffers, (void**)&orig_resize_)  == MH_OK) MH_EnableHook(vt[13]);

    IDXGISwapChain1* dsc1 = nullptr;
    if (SUCCEEDED(dsc->QueryInterface(__uuidof(IDXGISwapChain1), (void**)&dsc1))) {
        void** vt1 = *(void***)dsc1;
        if (MH_CreateHook(vt1[22], &hooked_Present1, (void**)&orig_present1_) == MH_OK) {
            MH_EnableHook(vt1[22]);
            STAR_LOG("DX11 Present1 hooked");
        }
        dsc1->Release();
    }

    dsc->Release(); ddev->Release(); DestroyWindow(dummy);
    STAR_LOG("DX11 hooked");

#ifdef _WIN64
    hook_dx12_ecl();
#endif
}

#ifdef _WIN64
void StarOverlay::hook_dx12_ecl()
{
    if (orig_execute_command_lists_) return;

    typedef HRESULT(WINAPI* PFN_D3D12CreateDevice)(IUnknown*, D3D_FEATURE_LEVEL, REFIID, void**);
    HMODULE hD3D12 = GetModuleHandleA("d3d12.dll");
    if (!hD3D12) hD3D12 = LoadLibraryA("d3d12.dll");
    if (!hD3D12) { STAR_LOG("DX12 ECL: d3d12.dll not found"); return; }

    auto pfnCreate = (PFN_D3D12CreateDevice)GetProcAddress(hD3D12, "D3D12CreateDevice");
    if (!pfnCreate) { STAR_LOG("DX12 ECL: D3D12CreateDevice export not found"); return; }

    ID3D12Device* dummy_dev = nullptr;
    HRESULT hr = pfnCreate(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&dummy_dev));
    if (FAILED(hr)) { STAR_LOG("DX12 ECL: D3D12CreateDevice failed hr=0x%08x", (unsigned)hr); return; }

    D3D12_COMMAND_QUEUE_DESC cqdesc = {};
    cqdesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    ID3D12CommandQueue* dummy_queue = nullptr;
    if (SUCCEEDED(dummy_dev->CreateCommandQueue(&cqdesc, IID_PPV_ARGS(&dummy_queue)))) {
        void** vt12 = *(void***)dummy_queue;
        MH_STATUS mh = MH_CreateHook(vt12[10], &hooked_ExecuteCommandLists, (void**)&orig_execute_command_lists_);
        if (mh == MH_OK) {
            MH_EnableHook(vt12[10]);
            STAR_LOG("DX12 ExecuteCommandLists hooked");
        } else {
            STAR_LOG("DX12 ECL: MH_CreateHook failed status=%d", (int)mh);
        }
        dummy_queue->Release();
    } else {
        STAR_LOG("DX12 ECL: CreateCommandQueue failed");
    }
    dummy_dev->Release();
}
#endif

void StarOverlay::setup_imgui_style_and_fonts()
{
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    char windir[MAX_PATH]{}; GetWindowsDirectoryA(windir, MAX_PATH);
    std::string fd = std::string(windir) + "\\Fonts\\";
    const char* faces[] = { "segoeui.ttf","arial.ttf","tahoma.ttf",nullptr };

    ImFontConfig fc; fc.OversampleH = 4; fc.OversampleV = 4; fc.PixelSnapH = false;

    auto tryFont = [&](float sz) -> ImFont* {
        for (int i = 0; faces[i]; i++) {
            if (auto* f = io.Fonts->AddFontFromFileTTF((fd+faces[i]).c_str(), sz, &fc))
                return f;
        }
        return nullptr;
    };

    font_small_ = tryFont(12.f);
    font_title_ = tryFont(15.f);
    if (ImFont* fb = tryFont(13.f)) io.FontDefault = fb;
    else io.Fonts->AddFontDefault();

    ImGui::StyleColorsDark();
    ImGuiStyle& s = ImGui::GetStyle();
    s.WindowRounding   = 0.f;
    s.ChildRounding    = 4.f;
    s.FrameRounding    = 4.f;
    s.ScrollbarRounding= 4.f;
    s.GrabRounding     = 4.f;
    s.WindowBorderSize = 1.f;
    s.ChildBorderSize  = 0.f;
    s.FrameBorderSize  = 0.f;
    s.WindowPadding    = { 14.f, 12.f };
    s.FramePadding     = {  8.f,  5.f };
    s.ItemSpacing      = {  8.f,  8.f };
    s.ScrollbarSize    = 5.f;

    auto* C = s.Colors;
    C[ImGuiCol_WindowBg]           = v4(P_BG0, 0.97f);
    C[ImGuiCol_ChildBg]            = v4(P_BG1, 1.f);
    C[ImGuiCol_Border]             = v4(P_SEP, 0.6f);
    C[ImGuiCol_FrameBg]            = v4(P_BG2, 1.f);
    C[ImGuiCol_FrameBgHovered]     = v4(0x30,0x30,0x30, 1.f);
    C[ImGuiCol_Button]             = v4(P_BG2, 1.f);
    C[ImGuiCol_ButtonHovered]      = v4(0x32,0x32,0x32, 1.f);
    C[ImGuiCol_ButtonActive]       = v4(0x3a,0x3a,0x3a, 1.f);
    C[ImGuiCol_Header]             = v4(P_BG2, 1.f);
    C[ImGuiCol_HeaderHovered]      = v4(0x30,0x30,0x30, 1.f);
    C[ImGuiCol_ScrollbarBg]        = v4(P_BG0, 1.f);
    C[ImGuiCol_ScrollbarGrab]      = v4(P_SEP, 1.f);
    C[ImGuiCol_ScrollbarGrabHovered]= v4(0x45,0x45,0x45, 1.f);
    C[ImGuiCol_ScrollbarGrabActive] = v4(P_ACC, 1.f);
    C[ImGuiCol_Separator]          = v4(P_SEP, 0.5f);
    C[ImGuiCol_Text]               = v4(P_TXT, 1.f);
    C[ImGuiCol_TextDisabled]       = v4(P_MUT, 1.f);
    C[ImGuiCol_TitleBg]            = v4(P_BG0, 1.f);
    C[ImGuiCol_TitleBgActive]      = v4(P_BG0, 1.f);
    C[ImGuiCol_PopupBg]            = v4(P_BG1, 0.98f);
    C[ImGuiCol_CheckMark]          = v4(P_ACC, 1.f);
    C[ImGuiCol_SliderGrab]         = v4(P_ACC, 1.f);
}

void StarOverlay::init_imgui(IDXGISwapChain* chain)
{
    if (imgui_initialized_) return;
    if (FAILED(chain->GetDevice(__uuidof(ID3D11Device),(void**)&device_))) return;
    device_->GetImmediateContext(&context_);
    DXGI_SWAP_CHAIN_DESC sd{}; chain->GetDesc(&sd); hwnd_ = sd.OutputWindow;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    setup_imgui_style_and_fonts();

    ImGui_ImplWin32_Init(hwnd_);
    ImGui_ImplDX11_Init(device_, context_);
    hook_window();
    imgui_initialized_ = true;
    active_api_ = GraphicsAPI::DX11;
    STAR_LOG("ImGui ready");
}

void StarOverlay::cleanup_rtv()
{
    if (rtv_) { rtv_->Release(); rtv_ = nullptr; }
}

ImTextureID StarOverlay::get_or_create_icon(
    const std::string& key, const std::vector<uint8_t>& rgba, int w, int h)
{
    auto it = icon_textures_.find(key);
    if (it != icon_textures_.end()) return it->second;

    ImTextureID tex_id = nullptr;
    if (!rgba.empty() && w > 0 && h > 0) {
#ifdef _WIN64
        if (active_api_ == GraphicsAPI::DX12) {
            tex_id = upload_icon_dx12(rgba, w, h);
        } else
#endif
        if (active_api_ == GraphicsAPI::Vulkan) {
            tex_id = upload_icon_vulkan(rgba, w, h);
        } else if (device_) {
            D3D11_TEXTURE2D_DESC td{};
            td.Width = w; td.Height = h; td.MipLevels = 1; td.ArraySize = 1;
            td.Format = DXGI_FORMAT_R8G8B8A8_UNORM; td.SampleDesc.Count = 1;
            td.Usage = D3D11_USAGE_DEFAULT; td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            D3D11_SUBRESOURCE_DATA srd{ rgba.data(), (UINT)(w*4), 0 };
            ID3D11Texture2D* tex = nullptr;
            if (SUCCEEDED(device_->CreateTexture2D(&td, &srd, &tex))) {
                ID3D11ShaderResourceView* srv = nullptr;
                device_->CreateShaderResourceView(tex, nullptr, &srv);
                tex->Release();
                tex_id = (ImTextureID)(void*)srv;
            }
        }
    }
    icon_textures_[key] = tex_id;
    return tex_id;
}

void StarOverlay::render_frame(IDXGISwapChain* chain)
{

    std::unique_lock<std::mutex> lock(render_mutex_, std::try_to_lock);
    if (!lock.owns_lock()) return;
    if (!imgui_initialized_) return;

    if (!rtv_) {
        ID3D11Texture2D* bb = nullptr;
        if (SUCCEEDED(chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&bb))) {
            device_->CreateRenderTargetView(bb, nullptr, &rtv_);
            bb->Release();
        }
    }
    if (!rtv_) return;

    ID3D11RenderTargetView* prev_rtv = nullptr;
    ID3D11DepthStencilView* prev_dsv = nullptr;
    context_->OMGetRenderTargets(1, &prev_rtv, &prev_dsv);

    context_->OMSetRenderTargets(1, &rtv_, nullptr);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    float dt = ImGui::GetIO().DeltaTime;
    if (dt <= 0.f) dt = 0.0167f;

    float target = open_ ? 1.f : 0.f;
    panel_anim_ += (target - panel_anim_) * clamp01(12.f * dt);
    panel_anim_  = clamp01(panel_anim_);

    if (panel_anim_ > 0.001f) render_panel();
    render_notifications(dt);

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    context_->OMSetRenderTargets(1, &prev_rtv, prev_dsv);
    if (prev_rtv) prev_rtv->Release();
    if (prev_dsv) prev_dsv->Release();
}

void StarOverlay::render_notifications(float dt)
{
    std::vector<AchievementNotification> notifs;
    {
        std::lock_guard<std::mutex> lock(notif_mutex_);
        for (auto& n : notifications_) { n.time_remaining -= dt; n.age += dt; }
        notifications_.erase(
            std::remove_if(notifications_.begin(), notifications_.end(),
                [](const AchievementNotification& n){ return n.time_remaining <= 0.f; }),
            notifications_.end());
        notifs = notifications_;
    }
    if (notifs.empty()) return;

    ImDrawList* dl = ImGui::GetForegroundDrawList();
    ImGuiIO&    io = ImGui::GetIO();
    ImFont* fsmall = (ImFont*)font_small_;
    ImFont* ftitle = (ImFont*)font_title_;

    const float W   = 292.f;
    const float H   = 68.f;
    const float PAD = 14.f;
    const float GAP =  8.f;
    const float SLIDE_DUR = 0.3f;
    const float FADE_DUR  = 0.7f;

    float y = io.DisplaySize.y - PAD;

    for (size_t i = 0; i < notifs.size() && i < 4; i++) {
        auto& n = notifs[i];
        y -= H + GAP;

        float slide = easeOut(clamp01(n.age / SLIDE_DUR));
        float fade  = (n.time_remaining < FADE_DUR) ? (n.time_remaining / FADE_DUR) : 1.f;
        float a     = clamp01(slide * fade);

        float x = io.DisplaySize.x - PAD - W + (1.f - slide) * (W + PAD);

        dl->AddRectFilled({x, y}, {x+W, y+H}, col(P_BG0, a * 0.95f), 5.f);

        dl->AddRectFilled({x, y+3.f}, {x+3.f, y+H-3.f}, col(P_ACC, a), 2.f);

        float ix = x + 11.f, iy = y + (H - 44.f) * .5f, is = 44.f;
        ImTextureID notif_tex = get_or_create_icon(n.title, n.icon_rgba, n.icon_width, n.icon_height);
        if (notif_tex) {
            dl->AddImageRounded(notif_tex,
                {ix,iy},{ix+is,iy+is},{0,0},{1,1}, col(0xff,0xff,0xff,a), 4.f);
        } else {
            dl->AddRectFilled({ix,iy},{ix+is,iy+is}, col(P_BG2, a), 4.f);
        }

        float tx = ix + is + 10.f;
        float tw = W - (tx - x) - 10.f;

        float ly = y + 10.f;
        dl->PushClipRect({tx,ly},{tx+tw,ly+14.f},true);
        dl->AddText(fsmall, 11.f, {tx,ly}, col(P_ACC, a), "ACHIEVEMENT UNLOCKED");
        dl->PopClipRect();

        float ty2 = ly + 15.f;
        dl->PushClipRect({tx,ty2},{tx+tw,ty2+18.f},true);
        dl->AddText(ftitle, 14.f, {tx,ty2}, col(P_TXT, a), n.title.c_str());
        dl->PopClipRect();

        if (!n.description.empty()) {
            float dy = ty2 + 19.f;
            dl->PushClipRect({tx,dy},{tx+tw,dy+14.f},true);
            dl->AddText(fsmall, 11.f, {tx,dy}, col(P_MUT, a), n.description.c_str());
            dl->PopClipRect();
        }

        float prog = clamp01(n.time_remaining / 5.f);
        float bx   = x + 3.f, by = y + H - 2.f, bw = W - 6.f;
        dl->AddRectFilled({bx,by},{bx+bw,by+2.f},         col(P_SEP, a * 0.4f), 1.f);
        dl->AddRectFilled({bx,by},{bx+bw*prog, by+2.f},   col(P_ACC, a * 0.7f), 1.f);
    }
}

void StarOverlay::render_panel()
{
    ImGuiIO& io   = ImGui::GetIO();
    float sw      = io.DisplaySize.x;
    float sh      = io.DisplaySize.y;
    ImFont* fsmall = (ImFont*)font_small_;
    ImFont* ftitle = (ImFont*)font_title_;

    float slide   = easeOut(panel_anim_);
    float alpha   = panel_anim_;

    const float PW = 360.f;

    ImGui::GetBackgroundDrawList()->AddRectFilled(
        {0,0}, {sw,sh}, col(0,0,0, 0.35f * alpha));

    float px = sw - PW * slide;
    ImGui::GetForegroundDrawList()->AddRectFilled(
        {px-2.f, 0}, {px, sh}, col(0,0,0, 0.5f * alpha));

    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
    ImGui::SetNextWindowPos({px, 0.f});
    ImGui::SetNextWindowSize({PW, sh});
    ImGui::SetNextWindowBgAlpha(0.97f);

    ImGuiWindowFlags wf = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse;

    ImGui::Begin("##star_sidebar", nullptr, wf);
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2      wp = ImGui::GetWindowPos();

    ImGui::PushFont(ftitle);
    ImGui::PushStyleColor(ImGuiCol_Text, v4(P_TXT, 1.f));
    ImGui::Text("STAR");
    ImGui::PopStyleColor();
    ImGui::PopFont();

    {
        ImGui::PushFont(fsmall);
        const char* hint = "Shift+Tab";
        float hw = ImGui::CalcTextSize(hint).x;
        ImGui::SameLine(PW - hw - 14.f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3.f);
        ImGui::PushStyleColor(ImGuiCol_Text, v4(P_DIM, 1.f));
        ImGui::Text("%s", hint);
        ImGui::PopStyleColor();
        ImGui::PopFont();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    auto& s = Settings::get();
    ImGui::PushFont(fsmall);
    ImGui::PushStyleColor(ImGuiCol_Text, v4(P_MUT, 1.f));
    ImGui::Text("Account:  %s", s.account_name.c_str());
    char sid[24]; snprintf(sid, sizeof(sid), "%llu", (unsigned long long)s.steam_id);
    ImGui::Text("Steam ID: %s", sid);
    char aid[12]; snprintf(aid, sizeof(aid), "%u", s.app_id);
    ImGui::Text("App ID:   %s", aid);
    ImGui::PopStyleColor();
    ImGui::PopFont();

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    auto& stats = StarSteamUserStats::get();
    int total = (int)s.achievements.size();
    int done  = 0;
    for (auto& d : s.achievements) {
        bool got = false; stats.GetAchievement(d.name.c_str(), &got);
        if (got) done++;
    }

    ImGui::PushFont(fsmall);
    ImGui::PushStyleColor(ImGuiCol_Text, v4(P_MUT, 1.f));
    ImGui::Text("ACHIEVEMENTS");
    ImGui::SameLine(0.f, 8.f);
    ImGui::PopStyleColor();
    ImGui::PushStyleColor(ImGuiCol_Text, v4(P_TXT, 1.f));
    ImGui::Text("%d / %d", done, total);
    ImGui::PopStyleColor();

    {
        const char* lbl = "Test notify";
        float bw = ImGui::CalcTextSize(lbl).x + 14.f;
        ImGui::SameLine(PW - bw - 14.f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 2.f);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {6.f, 2.f});
        ImGui::PushStyleColor(ImGuiCol_Button,        v4(P_BG2,    1.f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, v4(0x30,0x30,0x30, 1.f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  v4(0x3a,0x3a,0x3a, 1.f));
        ImGui::PushStyleColor(ImGuiCol_Text,          v4(P_MUT,    1.f));
        if (ImGui::Button(lbl)) {
            push_achievement("Test Achievement",
                             "Opened the STAR overlay.",
                             {}, 0, 0);
        }
        ImGui::PopStyleColor(4);
        ImGui::PopStyleVar();
    }

    ImGui::PopFont();

    if (total > 0) {
        float pct = (float)done / (float)total;
        ImVec2 cur = ImGui::GetCursorScreenPos();
        float  bw  = PW - 28.f;
        dl->AddRectFilled(cur, {cur.x+bw, cur.y+3.f}, col(P_SEP, 0.6f), 2.f);
        dl->AddRectFilled(cur, {cur.x+bw*pct, cur.y+3.f}, col(P_ACC, 0.9f), 2.f);
        ImGui::Dummy({bw, 5.f});
    }

    ImGui::Spacing();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.f, 0.f});
    ImGui::BeginChild("##ach", {0, 0}, false, 0);
    {
        ImDrawList* dl = ImGui::GetWindowDrawList();

        float actual_scroll_y = ImGui::GetScrollY();
        if (scroll_target_y_ < 0.f) {
            scroll_target_y_ = actual_scroll_y;
            scroll_current_y_ = actual_scroll_y;
        }
        float diff_scroll = actual_scroll_y - scroll_current_y_;
        if (diff_scroll < 0.f) diff_scroll = -diff_scroll;
        if (diff_scroll > 2.f) {
            scroll_target_y_ = actual_scroll_y;
            scroll_current_y_ = actual_scroll_y;
        }
        float wheel = ImGui::GetIO().MouseWheel;
        if (wheel != 0.f && ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows)) {
            scroll_target_y_ -= wheel * 100.f;
            float max_scroll_y = ImGui::GetScrollMaxY();
            if (scroll_target_y_ < 0.f) scroll_target_y_ = 0.f;
            if (scroll_target_y_ > max_scroll_y) scroll_target_y_ = max_scroll_y;
        }
        float dt = ImGui::GetIO().DeltaTime;
        if (dt <= 0.f) dt = 0.0167f;
        scroll_current_y_ += (scroll_target_y_ - scroll_current_y_) * clamp01(12.f * dt);
        float diff_target = scroll_current_y_ - scroll_target_y_;
        if (diff_target < 0.f) diff_target = -diff_target;
        if (diff_target > 0.1f) {
            ImGui::SetScrollY(scroll_current_y_);
        } else {
            ImGui::SetScrollY(scroll_target_y_);
            scroll_current_y_ = scroll_target_y_;
        }

    const float ROW_H  = 52.f;
    const float ICON_S = 36.f;
    const float ICON_X = 12.f;

    for (auto& def : s.achievements) {
        bool got = false;
        stats.GetAchievement(def.name.c_str(), &got);

        ImVec2 rmin = ImGui::GetCursorScreenPos();
        float  rw   = ImGui::GetContentRegionAvail().x;

        ImGui::SetNextItemAllowOverlap();
        ImGui::InvisibleButton(("##r_"+def.name).c_str(), {rw, ROW_H});
        bool hovered = ImGui::IsItemHovered();

        if (hovered)
            dl->AddRectFilled(rmin, {rmin.x+rw, rmin.y+ROW_H}, col(P_BG2, 0.6f));

        float ix2 = rmin.x + ICON_X;
        float iy2 = rmin.y + (ROW_H - ICON_S) * .5f;

        std::string ikey = (got ? "p_" : "g_") + def.name;
        ImTextureID icon_tex = nullptr;
        auto icit = icon_textures_.find(ikey);
        if (icit != icon_textures_.end()) {
            icon_tex = icit->second;
        } else {
            std::vector<uint8_t> rgba; int iw = 0, ih = 0;
            const std::string& icon_path = got ? def.icon_path : def.icon_gray_path;
            if (!icon_path.empty()) {
                std::string full = Settings::get().settings_dir + "\\" + icon_path;
                for (char& c : full) if (c == '/') c = '\\';
                int h = StarSteamUtils::get().LoadImageFromFile(full);
                if (h > 0) {
                    uint32 uw = 0, uh = 0;
                    StarSteamUtils::get().GetImageSize(h, &uw, &uh);
                    iw = (int)uw; ih = (int)uh;
                    rgba.resize((size_t)uw * uh * 4);
                    StarSteamUtils::get().GetImageRGBA(h, rgba.data(), (int)rgba.size());
                }
            }
            icon_tex = get_or_create_icon(ikey, rgba, iw, ih);
        }
        if (icon_tex) {
            dl->AddImageRounded(icon_tex,
                {ix2,iy2},{ix2+ICON_S,iy2+ICON_S},{0,0},{1,1},
                IM_COL32(255,255,255, 255), 3.f);
        } else {
            dl->AddRectFilled({ix2,iy2},{ix2+ICON_S,iy2+ICON_S},
                col(P_BG2, 1.f), 3.f);
        }

        float dot_x = ix2 + ICON_S - 6.f, dot_y = iy2;
        dl->AddCircleFilled({dot_x, dot_y}, 5.f,
            got ? col(P_GRN, 1.f) : col(P_DIM, 0.f));

        float tx  = ix2 + ICON_S + 10.f;
        float ty0 = rmin.y + 10.f;
        float tw  = rw - (tx - rmin.x) - 80.f;

        const char* name = (!def.display_name.empty()) ? def.display_name.c_str() : def.name.c_str();
        if (def.hidden && !got) name = "(Hidden)";

        ImU32 name_col = got ? col(P_TXT, 1.f) : col(P_MUT, 1.f);
        dl->PushClipRect({tx,ty0},{tx+tw,ty0+18.f},true);
        dl->AddText(ftitle, 14.f, {tx,ty0}, name_col, name);
        dl->PopClipRect();

        const char* desc = (!def.description.empty()) ? def.description.c_str() : nullptr;
        if (desc && (!def.hidden || got)) {
            float dy = ty0 + 19.f;
            dl->PushClipRect({tx,dy},{tx+tw,dy+14.f},true);
            dl->AddText(fsmall, 11.f, {tx,dy}, col(P_DIM, 1.f), desc);
            dl->PopClipRect();
        }

        float btn_x = rmin.x + rw - 72.f;
        float btn_y = rmin.y + (ROW_H - 22.f) * .5f;

        ImGui::SetCursorScreenPos({btn_x, btn_y});
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {6.f, 3.f});

        if (got) {
            ImGui::PushStyleColor(ImGuiCol_Button,        v4(P_BG2,    1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, v4(0x38,0x1a,0x1a, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,  v4(0x44,0x20,0x20, 1.f));
            ImGui::PushStyleColor(ImGuiCol_Text,          v4(P_MUT, 1.f));
            if (ImGui::Button(("Reset##" + def.name).c_str(), {62.f, 22.f}))
                stats.ClearAchievement(def.name.c_str());
            ImGui::PopStyleColor(4);
        } else {
            ImGui::PushStyleColor(ImGuiCol_Button,        v4(P_BG2,       1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, v4(0x1a,0x2c,0x44, 1.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,  v4(0x1e,0x36,0x54, 1.f));
            ImGui::PushStyleColor(ImGuiCol_Text,          v4(P_ACC, 1.f));
            if (ImGui::Button(("Unlock##" + def.name).c_str(), {62.f, 22.f}))
                stats.SetAchievement(def.name.c_str());
            ImGui::PopStyleColor(4);
        }
        ImGui::PopStyleVar();

        ImGui::SetCursorScreenPos({rmin.x, rmin.y + ROW_H});
        ImVec2 sep_p = ImGui::GetCursorScreenPos();
        dl->AddLine({sep_p.x, sep_p.y}, {sep_p.x+rw, sep_p.y}, col(P_SEP, 0.3f));
    }

    if (s.achievements.empty()) {
        ImGui::PushFont(fsmall);
        ImGui::PushStyleColor(ImGuiCol_Text, v4(P_DIM, 1.f));
        ImGui::TextUnformatted("No achievements in STAR/achievements.json");
        ImGui::PopStyleColor();
        ImGui::PopFont();
    }

    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::End();
    ImGui::PopStyleVar();
}

void StarOverlay::push_achievement(const std::string& name, const std::string& desc,
                                   const std::vector<uint8_t>& rgba, int iw, int ih)
{
    if (!enabled_) return;
    std::lock_guard<std::mutex> lock(notif_mutex_);
    AchievementNotification n;
    n.title = name; n.description = desc;
    n.icon_rgba = rgba; n.icon_width = iw; n.icon_height = ih;
    n.time_remaining = 5.f; n.age = 0.f;
    notifications_.push_back(std::move(n));
}

#ifdef _WIN64
void STDMETHODCALLTYPE StarOverlay::hooked_ExecuteCommandLists(void* queue, UINT count, void* const* lists)
{
    if (!g_dx12_captured_queue_) {
        g_dx12_captured_queue_ = queue;
        STAR_LOG("DX12 command queue captured");
    }
    if (g_overlay && g_overlay->orig_execute_command_lists_)
        g_overlay->orig_execute_command_lists_(queue, count, lists);
}
#endif

HRESULT STDMETHODCALLTYPE StarOverlay::hooked_Present(IDXGISwapChain* sc, UINT si, UINT fl)
{
    if (g_overlay && !(fl & DXGI_PRESENT_TEST)) g_overlay->on_present(sc, si, fl);
    return g_overlay ? g_overlay->orig_present_(sc, si, fl) : S_OK;
}

HRESULT STDMETHODCALLTYPE StarOverlay::hooked_Present1(
    IDXGISwapChain1* sc, UINT si, UINT fl, const DXGI_PRESENT_PARAMETERS* pp)
{
    if (g_overlay && !(fl & DXGI_PRESENT_TEST)) g_overlay->on_present(sc, si, fl);
    return g_overlay ? g_overlay->orig_present1_(sc, si, fl, pp) : S_OK;
}

HRESULT STDMETHODCALLTYPE StarOverlay::hooked_ResizeBuffers(
    IDXGISwapChain* sc, UINT bc, UINT w, UINT h, DXGI_FORMAT fmt, UINT fl)
{
    if (g_overlay) g_overlay->on_resize_buffers(sc, bc, w, h, fmt, fl);
    return g_overlay ? g_overlay->orig_resize_(sc, bc, w, h, fmt, fl) : S_OK;
}

void StarOverlay::on_present(IDXGISwapChain* chain, UINT si, UINT fl)
{
    STAR_UNREFERENCED(si); STAR_UNREFERENCED(fl);
    if (!enabled_) return;

    if (!imgui_initialized_) {
        static bool logged_attempt = false;
        if (!logged_attempt) { logged_attempt = true; STAR_LOG("on_present: attempting imgui init"); }
        ID3D11Device* d3d11_device = nullptr;
        if (SUCCEEDED(chain->GetDevice(__uuidof(ID3D11Device), (void**)&d3d11_device))) {
            d3d11_device->Release();
            init_imgui(chain);
        } else {
            static bool logged_dx11_fail = false;
            if (!logged_dx11_fail) { logged_dx11_fail = true; STAR_LOG("on_present: DX11 device not found, using DX12 path"); }
#ifdef _WIN64
            if (!orig_execute_command_lists_) {
                hook_dx12_ecl();
                return;
            }
            if (g_dx12_captured_queue_) {
                ID3D12Device* d3d12_device = nullptr;
                auto* queue = (ID3D12CommandQueue*)g_dx12_captured_queue_;
                if (SUCCEEDED(queue->GetDevice(__uuidof(ID3D12Device), (void**)&d3d12_device))) {
                    init_imgui_dx12(chain, d3d12_device, g_dx12_captured_queue_);
                    d3d12_device->Release();
                } else {
                    static bool logged_queue_fail = false;
                    if (!logged_queue_fail) { logged_queue_fail = true; STAR_LOG("on_present: DX12 queue->GetDevice failed"); }
                }
            }
#endif
        }
    }

    if (imgui_initialized_) {
        if (active_api_ == GraphicsAPI::DX11) {
            render_frame(chain);
#ifdef _WIN64
        } else if (active_api_ == GraphicsAPI::DX12) {
            render_frame_dx12(chain);
#endif
        }
    }
}

void StarOverlay::on_resize_buffers(IDXGISwapChain* sc, UINT bc, UINT w, UINT h, DXGI_FORMAT fmt, UINT fl)
{
    STAR_UNREFERENCED(sc); STAR_UNREFERENCED(bc); STAR_UNREFERENCED(w);
    STAR_UNREFERENCED(h);  STAR_UNREFERENCED(fmt); STAR_UNREFERENCED(fl);
    std::lock_guard<std::mutex> lock(render_mutex_);
    if (active_api_ == GraphicsAPI::DX11) {
        cleanup_rtv();
#ifdef _WIN64
    } else if (active_api_ == GraphicsAPI::DX12) {
        cleanup_dx12();
        imgui_initialized_ = false;
#endif
    }
}

#ifdef _WIN64
void StarOverlay::init_imgui_dx12(IDXGISwapChain* chain, void* device, void* command_queue)
{
    auto* dev = (ID3D12Device*)device;
    auto* queue = (ID3D12CommandQueue*)command_queue;

    DXGI_SWAP_CHAIN_DESC sd{};
    chain->GetDesc(&sd);
    hwnd_ = sd.OutputWindow;
    STAR_LOG("init_imgui_dx12: buffers=%u fmt=%u hwnd=%p", sd.BufferCount, sd.BufferDesc.Format, hwnd_);

    D3D12_DESCRIPTOR_HEAP_DESC rtv_desc = {};
    rtv_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtv_desc.NumDescriptors = sd.BufferCount;
    rtv_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    ID3D12DescriptorHeap* rtv_heap = nullptr;
    if (FAILED(dev->CreateDescriptorHeap(&rtv_desc, IID_PPV_ARGS(&rtv_heap)))) { STAR_LOG("init_imgui_dx12: rtv_heap failed"); return; }

    D3D12_DESCRIPTOR_HEAP_DESC srv_desc = {};
    srv_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    srv_desc.NumDescriptors = 257;
    srv_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

    ID3D12DescriptorHeap* srv_heap = nullptr;
    if (FAILED(dev->CreateDescriptorHeap(&srv_desc, IID_PPV_ARGS(&srv_heap)))) {
        STAR_LOG("init_imgui_dx12: srv_heap failed");
        rtv_heap->Release();
        return;
    }

    std::vector<ID3D12Resource*> resources(sd.BufferCount);
    D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle = rtv_heap->GetCPUDescriptorHandleForHeapStart();
    UINT rtv_descriptor_size = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    for (UINT i = 0; i < sd.BufferCount; i++) {
        if (SUCCEEDED(chain->GetBuffer(i, IID_PPV_ARGS(&resources[i])))) {
            dev->CreateRenderTargetView(resources[i], nullptr, rtv_handle);
            rtv_handle.ptr += rtv_descriptor_size;
        }
    }

    std::vector<ID3D12CommandAllocator*> allocators(sd.BufferCount);
    for (UINT i = 0; i < sd.BufferCount; i++) {
        if (FAILED(dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocators[i])))) { STAR_LOG("init_imgui_dx12: allocator[%u] failed", i); return; }
    }

    ID3D12GraphicsCommandList* cmd_list = nullptr;
    if (FAILED(dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocators[0], nullptr, IID_PPV_ARGS(&cmd_list)))) { STAR_LOG("init_imgui_dx12: cmd_list failed"); return; }
    cmd_list->Close();

    ImGui::CreateContext();
    ImGui_ImplWin32_Init(hwnd_);
    hook_window();

    IMGUI_CHECKVERSION();
    STAR_LOG("init_imgui_dx12: calling ImGui_ImplDX12_Init");
    if (ImGui_ImplDX12_Init(dev, sd.BufferCount, sd.BufferDesc.Format, srv_heap,
                            srv_heap->GetCPUDescriptorHandleForHeapStart(),
                            srv_heap->GetGPUDescriptorHandleForHeapStart())) {
        setup_imgui_style_and_fonts();
        dev->AddRef();
        queue->AddRef();
        dx12_device_ = dev;
        dx12_command_queue_ = queue;
        dx12_rtv_heap_ = rtv_heap;
        dx12_srv_heap_ = srv_heap;
        dx12_command_list_ = cmd_list;
        dx12_buffer_count_ = sd.BufferCount;

        dx12_command_allocators_.resize(sd.BufferCount);
        for (UINT i = 0; i < sd.BufferCount; i++) dx12_command_allocators_[i] = allocators[i];

        dx12_resources_.resize(sd.BufferCount);
        for (UINT i = 0; i < sd.BufferCount; i++) dx12_resources_[i] = resources[i];

        dx12_srv_next_slot_ = 1;
        imgui_initialized_ = true;
        active_api_ = GraphicsAPI::DX12;
        STAR_LOG("ImGui ready (DX12)");
    } else {
        STAR_LOG("init_imgui_dx12: ImGui_ImplDX12_Init FAILED — BackendRendererUserData=%p",
                 ImGui::GetIO().BackendRendererUserData);
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
}

ImTextureID StarOverlay::upload_icon_dx12(const std::vector<uint8_t>& rgba, int w, int h)
{
    auto* dev   = (ID3D12Device*)dx12_device_;
    auto* queue = (ID3D12CommandQueue*)dx12_command_queue_;
    auto* heap  = (ID3D12DescriptorHeap*)dx12_srv_heap_;
    if (!dev || !queue || !heap || dx12_srv_next_slot_ >= 257) return nullptr;

    UINT row_pitch     = (UINT)(w * 4);
    UINT aligned_pitch = (row_pitch + D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1)
                         & ~(D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1);
    UINT64 upload_size = (UINT64)aligned_pitch * h;

    D3D12_HEAP_PROPERTIES upload_props = {};
    upload_props.Type = D3D12_HEAP_TYPE_UPLOAD;
    D3D12_RESOURCE_DESC buf_desc = {};
    buf_desc.Dimension  = D3D12_RESOURCE_DIMENSION_BUFFER;
    buf_desc.Width      = upload_size;
    buf_desc.Height     = buf_desc.DepthOrArraySize = buf_desc.MipLevels = 1;
    buf_desc.Format     = DXGI_FORMAT_UNKNOWN;
    buf_desc.SampleDesc.Count = 1;
    buf_desc.Layout     = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    ID3D12Resource* upload_buf = nullptr;
    if (FAILED(dev->CreateCommittedResource(&upload_props, D3D12_HEAP_FLAG_NONE,
                                            &buf_desc, D3D12_RESOURCE_STATE_GENERIC_READ,
                                            nullptr, IID_PPV_ARGS(&upload_buf))))
        return nullptr;

    void* mapped = nullptr;
    if (FAILED(upload_buf->Map(0, nullptr, &mapped))) { upload_buf->Release(); return nullptr; }
    for (int row = 0; row < h; row++)
        memcpy((uint8_t*)mapped + (size_t)row * aligned_pitch, rgba.data() + (size_t)row * row_pitch, row_pitch);
    upload_buf->Unmap(0, nullptr);

    D3D12_HEAP_PROPERTIES default_props = {};
    default_props.Type = D3D12_HEAP_TYPE_DEFAULT;
    D3D12_RESOURCE_DESC tex_desc = {};
    tex_desc.Dimension          = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    tex_desc.Width              = (UINT64)w;
    tex_desc.Height             = (UINT)h;
    tex_desc.DepthOrArraySize   = tex_desc.MipLevels = 1;
    tex_desc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
    tex_desc.SampleDesc.Count   = 1;
    tex_desc.Layout             = D3D12_TEXTURE_LAYOUT_UNKNOWN;

    ID3D12Resource* texture = nullptr;
    if (FAILED(dev->CreateCommittedResource(&default_props, D3D12_HEAP_FLAG_NONE,
                                            &tex_desc, D3D12_RESOURCE_STATE_COPY_DEST,
                                            nullptr, IID_PPV_ARGS(&texture)))) {
        upload_buf->Release(); return nullptr;
    }

    ID3D12CommandAllocator*    tmp_alloc = nullptr;
    ID3D12GraphicsCommandList* tmp_list  = nullptr;
    if (FAILED(dev->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&tmp_alloc))) ||
        FAILED(dev->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, tmp_alloc, nullptr, IID_PPV_ARGS(&tmp_list)))) {
        if (tmp_alloc) tmp_alloc->Release();
        texture->Release(); upload_buf->Release(); return nullptr;
    }

    D3D12_TEXTURE_COPY_LOCATION dst_loc = {};
    dst_loc.pResource        = texture;
    dst_loc.Type             = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    dst_loc.SubresourceIndex = 0;

    D3D12_TEXTURE_COPY_LOCATION src_loc = {};
    src_loc.pResource                            = upload_buf;
    src_loc.Type                                 = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
    src_loc.PlacedFootprint.Footprint.Format     = DXGI_FORMAT_R8G8B8A8_UNORM;
    src_loc.PlacedFootprint.Footprint.Width      = (UINT)w;
    src_loc.PlacedFootprint.Footprint.Height     = (UINT)h;
    src_loc.PlacedFootprint.Footprint.Depth      = 1;
    src_loc.PlacedFootprint.Footprint.RowPitch   = aligned_pitch;

    tmp_list->CopyTextureRegion(&dst_loc, 0, 0, 0, &src_loc, nullptr);

    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource   = texture;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
    barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    tmp_list->ResourceBarrier(1, &barrier);
    tmp_list->Close();

    ID3D12CommandList* lists[] = { tmp_list };
    queue->ExecuteCommandLists(1, lists);

    ID3D12Fence* fence = nullptr;
    if (FAILED(dev->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)))) {
        tmp_list->Release(); tmp_alloc->Release(); upload_buf->Release();
        texture->Release(); return nullptr;
    }
    if (FAILED(queue->Signal(fence, 1))) {
        fence->Release();
        tmp_list->Release(); tmp_alloc->Release(); upload_buf->Release();
        texture->Release(); return nullptr;
    }
    if (fence->GetCompletedValue() < 1) {
        HANDLE ev = CreateEventA(nullptr, FALSE, FALSE, nullptr);
        fence->SetEventOnCompletion(1, ev);
        WaitForSingleObject(ev, INFINITE);
        CloseHandle(ev);
    }
    fence->Release();
    tmp_list->Release();
    tmp_alloc->Release();
    upload_buf->Release();

    UINT desc_inc = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    D3D12_CPU_DESCRIPTOR_HANDLE cpu = heap->GetCPUDescriptorHandleForHeapStart();
    D3D12_GPU_DESCRIPTOR_HANDLE gpu = heap->GetGPUDescriptorHandleForHeapStart();
    cpu.ptr += (UINT64)dx12_srv_next_slot_ * desc_inc;
    gpu.ptr += (UINT64)dx12_srv_next_slot_ * desc_inc;
    dx12_srv_next_slot_++;

    D3D12_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
    srv_desc.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
    srv_desc.ViewDimension             = D3D12_SRV_DIMENSION_TEXTURE2D;
    srv_desc.Shader4ComponentMapping   = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srv_desc.Texture2D.MipLevels       = 1;
    dev->CreateShaderResourceView(texture, &srv_desc, cpu);

    dx12_icon_resources_.push_back(texture);
    return (ImTextureID)(void*)(UINT64)gpu.ptr;
}

void StarOverlay::render_frame_dx12(IDXGISwapChain* chain)
{
    std::unique_lock<std::mutex> lock(render_mutex_, std::try_to_lock);
    if (!lock.owns_lock()) return;
    if (!imgui_initialized_) return;

    IDXGISwapChain3* chain3 = nullptr;
    UINT backbuffer_index = 0;
    if (SUCCEEDED(chain->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&chain3))) {
        backbuffer_index = chain3->GetCurrentBackBufferIndex();
        chain3->Release();
    } else {
        return;
    }

    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    float dt = ImGui::GetIO().DeltaTime;
    if (dt <= 0.f) dt = 0.0167f;

    float target = open_ ? 1.f : 0.f;
    panel_anim_ += (target - panel_anim_) * clamp01(12.f * dt);
    panel_anim_  = clamp01(panel_anim_);

    if (panel_anim_ > 0.001f) render_panel();
    render_notifications(dt);

    ImGui::Render();

    auto* dev = (ID3D12Device*)dx12_device_;
    auto* queue = (ID3D12CommandQueue*)dx12_command_queue_;
    auto* cmd_list = (ID3D12GraphicsCommandList*)dx12_command_list_;
    auto* allocator = (ID3D12CommandAllocator*)dx12_command_allocators_[backbuffer_index];
    auto* resource = (ID3D12Resource*)dx12_resources_[backbuffer_index];
    auto* rtv_heap = (ID3D12DescriptorHeap*)dx12_rtv_heap_;
    auto* srv_heap = (ID3D12DescriptorHeap*)dx12_srv_heap_;

    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = resource;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    allocator->Reset();
    cmd_list->Reset(allocator, nullptr);
    cmd_list->ResourceBarrier(1, &barrier);

    D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle = rtv_heap->GetCPUDescriptorHandleForHeapStart();
    UINT rtv_descriptor_size = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    rtv_handle.ptr += backbuffer_index * rtv_descriptor_size;
    cmd_list->OMSetRenderTargets(1, &rtv_handle, FALSE, nullptr);

    cmd_list->SetDescriptorHeaps(1, &srv_heap);

    ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmd_list);

    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    cmd_list->ResourceBarrier(1, &barrier);

    cmd_list->Close();

    ID3D12CommandList* lists[] = { cmd_list };
    queue->ExecuteCommandLists(1, lists);
}

void StarOverlay::cleanup_dx12()
{
    for (auto* res : dx12_icon_resources_) if (res) ((ID3D12Resource*)res)->Release();
    dx12_icon_resources_.clear();
    dx12_srv_next_slot_ = 1;

    for (auto* res : dx12_resources_) if (res) ((ID3D12Resource*)res)->Release();
    dx12_resources_.clear();
    for (auto* alloc : dx12_command_allocators_) if (alloc) ((ID3D12CommandAllocator*)alloc)->Release();
    dx12_command_allocators_.clear();
    if (dx12_command_list_) { ((ID3D12GraphicsCommandList*)dx12_command_list_)->Release(); dx12_command_list_ = nullptr; }
    if (dx12_rtv_heap_) { ((ID3D12DescriptorHeap*)dx12_rtv_heap_)->Release(); dx12_rtv_heap_ = nullptr; }
    if (dx12_srv_heap_) { ((ID3D12DescriptorHeap*)dx12_srv_heap_)->Release(); dx12_srv_heap_ = nullptr; }
    if (dx12_command_queue_) { ((ID3D12CommandQueue*)dx12_command_queue_)->Release(); dx12_command_queue_ = nullptr; }
    if (dx12_device_) { ((ID3D12Device*)dx12_device_)->Release(); dx12_device_ = nullptr; }
}
#endif

HRESULT STDMETHODCALLTYPE StarOverlay::hooked_DX9Present(IDirect3DDevice9* device, const RECT* src, const RECT* dst, HWND window, const RGNDATA* rgn)
{
    if (g_overlay) g_overlay->on_present_dx9(device);
    return g_overlay ? g_overlay->orig_dx9_present_(device, src, dst, window, rgn) : S_OK;
}

HRESULT STDMETHODCALLTYPE StarOverlay::hooked_DX9Reset(IDirect3DDevice9* device, void* params)
{
    if (g_overlay) g_overlay->on_reset_dx9();
    typedef HRESULT(STDMETHODCALLTYPE* DX9ResetFn)(IDirect3DDevice9*, void*);
    auto orig = (DX9ResetFn)g_overlay->orig_dx9_reset_;
    HRESULT hr = orig(device, params);
    if (SUCCEEDED(hr) && g_overlay && g_overlay->active_api_ == GraphicsAPI::DX9) {
        ImGui_ImplDX9_CreateDeviceObjects();
    }
    return hr;
}

void StarOverlay::hook_dx9()
{
    HMODULE d3d9_dll = GetModuleHandleA("d3d9.dll");
    if (!d3d9_dll) d3d9_dll = LoadLibraryA("d3d9.dll");
    if (!d3d9_dll) return;

    typedef IDirect3D9* (WINAPI* Direct3DCreate9Fn)(UINT);
    auto pDirect3DCreate9 = (Direct3DCreate9Fn)GetProcAddress(d3d9_dll, "Direct3DCreate9");
    if (!pDirect3DCreate9) return;

    IDirect3D9* d3d = pDirect3DCreate9(D3D_SDK_VERSION);
    if (!d3d) return;

    HWND dummy = CreateWindowExA(0, "STAR_Dummy", "", WS_OVERLAPPEDWINDOW, 0, 0, 4, 4, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
    if (!dummy) { d3d->Release(); return; }

    D3DPRESENT_PARAMETERS d3dpp{};
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = dummy;

    IDirect3DDevice9* device = nullptr;
    HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, dummy, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device);
    if (FAILED(hr) || !device) {
        DestroyWindow(dummy);
        d3d->Release();
        return;
    }

    void** vt = *(void***)device;
    if (MH_CreateHook(vt[17], &hooked_DX9Present, (void**)&orig_dx9_present_) == MH_OK) MH_EnableHook(vt[17]);
    if (MH_CreateHook(vt[16], &hooked_DX9Reset,   (void**)&orig_dx9_reset_)   == MH_OK) MH_EnableHook(vt[16]);

    device->Release();
    DestroyWindow(dummy);
    d3d->Release();
    STAR_LOG("DX9 hooked");
}

void StarOverlay::on_present_dx9(IDirect3DDevice9* device)
{
    if (!enabled_) return;

    std::unique_lock<std::mutex> lock(render_mutex_, std::try_to_lock);
    if (!lock.owns_lock()) return;

    if (!imgui_initialized_) {
        D3DDEVICE_CREATION_PARAMETERS cp{};
        device->GetCreationParameters(&cp);
        hwnd_ = cp.hFocusWindow;
        if (!hwnd_) hwnd_ = GetActiveWindow();

        ImGui::CreateContext();
        ImGui_ImplWin32_Init(hwnd_);
        hook_window();

        if (ImGui_ImplDX9_Init(device)) {
            setup_imgui_style_and_fonts();
            imgui_initialized_ = true;
            active_api_ = GraphicsAPI::DX9;
        }
    }

    if (imgui_initialized_ && active_api_ == GraphicsAPI::DX9) {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        float dt = ImGui::GetIO().DeltaTime;
        if (dt <= 0.f) dt = 0.0167f;

        float target = open_ ? 1.f : 0.f;
        panel_anim_ += (target - panel_anim_) * clamp01(12.f * dt);
        panel_anim_  = clamp01(panel_anim_);

        if (panel_anim_ > 0.001f) render_panel();
        render_notifications(dt);

        ImGui::Render();

        IDirect3DStateBlock9* state_block = nullptr;
        if (SUCCEEDED(device->CreateStateBlock(D3DSBT_ALL, &state_block))) {
            state_block->Capture();
        }

        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

        if (state_block) {
            state_block->Apply();
            state_block->Release();
        }
    }
}

void StarOverlay::on_reset_dx9()
{
    std::lock_guard<std::mutex> lock(render_mutex_);
    if (active_api_ == GraphicsAPI::DX9 && imgui_initialized_) {
        ImGui_ImplDX9_InvalidateDeviceObjects();
    }
}

BOOL WINAPI StarOverlay::hooked_wglSwapBuffers(HDC hdc)
{
    if (g_overlay) g_overlay->on_present_opengl(hdc);
    return g_overlay ? g_overlay->orig_wglSwapBuffers_(hdc) : FALSE;
}

void StarOverlay::hook_opengl()
{
    HMODULE opengl_dll = GetModuleHandleA("opengl32.dll");
    if (!opengl_dll) opengl_dll = LoadLibraryA("opengl32.dll");
    if (!opengl_dll) return;

    void* pSwapBuffers = (void*)GetProcAddress(opengl_dll, "wglSwapBuffers");
    if (pSwapBuffers) {
        if (MH_CreateHook(pSwapBuffers, &hooked_wglSwapBuffers, (void**)&orig_wglSwapBuffers_) == MH_OK) {
            MH_EnableHook(pSwapBuffers);
            STAR_LOG("OpenGL hooked");
        }
    }
}

void StarOverlay::on_present_opengl(HDC hdc)
{
    if (!enabled_) return;

    std::unique_lock<std::mutex> lock(render_mutex_, std::try_to_lock);
    if (!lock.owns_lock()) return;

    if (!imgui_initialized_) {
        hwnd_ = WindowFromDC(hdc);
        if (!hwnd_) hwnd_ = GetActiveWindow();

        ImGui::CreateContext();
        ImGui_ImplWin32_Init(hwnd_);
        hook_window();

        if (ImGui_ImplOpenGL3_Init()) {
            setup_imgui_style_and_fonts();
            imgui_initialized_ = true;
            active_api_ = GraphicsAPI::OpenGL;
        }
    }

    if (imgui_initialized_ && active_api_ == GraphicsAPI::OpenGL) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        float dt = ImGui::GetIO().DeltaTime;
        if (dt <= 0.f) dt = 0.0167f;

        float target = open_ ? 1.f : 0.f;
        panel_anim_ += (target - panel_anim_) * clamp01(12.f * dt);
        panel_anim_  = clamp01(panel_anim_);

        if (panel_anim_ > 0.001f) render_panel();
        render_notifications(dt);

        ImGui::Render();

        #ifndef GL_ALL_ATTRIB_BITS
        #define GL_ALL_ATTRIB_BITS 0x000fffff
        #define GL_CLIENT_ALL_ATTRIB_BITS 0xffffffff
        #endif
        typedef void(WINAPI* glPushAttribFn)(uint32_t);
        typedef void(WINAPI* glPopAttribFn)();
        typedef void(WINAPI* glPushClientAttribFn)(uint32_t);
        typedef void(WINAPI* glPopClientAttribFn)();

        HMODULE opengl_dll = GetModuleHandleA("opengl32.dll");
        auto glPushAttrib = (glPushAttribFn)GetProcAddress(opengl_dll, "glPushAttrib");
        auto glPopAttrib = (glPopAttribFn)GetProcAddress(opengl_dll, "glPopAttrib");
        auto glPushClientAttrib = (glPushClientAttribFn)GetProcAddress(opengl_dll, "glPushClientAttrib");
        auto glPopClientAttrib = (glPopClientAttribFn)GetProcAddress(opengl_dll, "glPopClientAttrib");

        if (glPushAttrib) glPushAttrib(GL_ALL_ATTRIB_BITS);
        if (glPushClientAttrib) glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (glPopClientAttrib) glPopClientAttrib();
        if (glPopAttrib) glPopAttrib();
    }
}

#define VULKAN_FUNCS \
    VK_FUNC(vkGetInstanceProcAddr) \
    VK_FUNC(vkGetDeviceProcAddr) \
    VK_FUNC(vkCreateInstance) \
    VK_FUNC(vkDestroyInstance) \
    VK_FUNC(vkCreateDevice) \
    VK_FUNC(vkDestroyDevice) \
    VK_FUNC(vkEnumeratePhysicalDevices) \
    VK_FUNC(vkGetPhysicalDeviceQueueFamilyProperties) \
    VK_FUNC(vkGetPhysicalDeviceMemoryProperties) \
    VK_FUNC(vkGetDeviceQueue) \
    VK_FUNC(vkCreateSwapchainKHR) \
    VK_FUNC(vkDestroySwapchainKHR) \
    VK_FUNC(vkGetSwapchainImagesKHR) \
    VK_FUNC(vkCreateRenderPass) \
    VK_FUNC(vkDestroyRenderPass) \
    VK_FUNC(vkCreateDescriptorPool) \
    VK_FUNC(vkDestroyDescriptorPool) \
    VK_FUNC(vkCreateCommandPool) \
    VK_FUNC(vkDestroyCommandPool) \
    VK_FUNC(vkAllocateCommandBuffers) \
    VK_FUNC(vkFreeCommandBuffers) \
    VK_FUNC(vkBeginCommandBuffer) \
    VK_FUNC(vkEndCommandBuffer) \
    VK_FUNC(vkCmdBeginRenderPass) \
    VK_FUNC(vkCmdEndRenderPass) \
    VK_FUNC(vkCmdPipelineBarrier) \
    VK_FUNC(vkCmdCopyBufferToImage) \
    VK_FUNC(vkCreateFramebuffer) \
    VK_FUNC(vkDestroyFramebuffer) \
    VK_FUNC(vkCreateImage) \
    VK_FUNC(vkDestroyImage) \
    VK_FUNC(vkCreateImageView) \
    VK_FUNC(vkDestroyImageView) \
    VK_FUNC(vkCreateBuffer) \
    VK_FUNC(vkDestroyBuffer) \
    VK_FUNC(vkAllocateMemory) \
    VK_FUNC(vkFreeMemory) \
    VK_FUNC(vkBindBufferMemory) \
    VK_FUNC(vkBindImageMemory) \
    VK_FUNC(vkMapMemory) \
    VK_FUNC(vkUnmapMemory) \
    VK_FUNC(vkGetBufferMemoryRequirements) \
    VK_FUNC(vkGetImageMemoryRequirements) \
    VK_FUNC(vkCreateSampler) \
    VK_FUNC(vkDestroySampler) \
    VK_FUNC(vkCreateFence) \
    VK_FUNC(vkWaitForFences) \
    VK_FUNC(vkDestroyFence) \
    VK_FUNC(vkQueuePresentKHR) \
    VK_FUNC(vkDeviceWaitIdle) \
    VK_FUNC(vkResetCommandBuffer) \
    VK_FUNC(vkQueueSubmit)

#define VK_FUNC(name) static PFN_##name name = nullptr;
VULKAN_FUNCS
#undef VK_FUNC

static bool resolve_vulkan_funcs(HMODULE vulkan) {
    #define VK_FUNC(name) \
        name = (PFN_##name)GetProcAddress(vulkan, #name); \
        if (!name) return false;
    VULKAN_FUNCS
    #undef VK_FUNC
    return true;
}

static VkInstance g_vk_instance = VK_NULL_HANDLE;

static PFN_vkVoidFunction ImGuiVulkanLoader(const char* function_name, void* user_data) {
    HMODULE vulkan = (HMODULE)user_data;
    if (vkGetInstanceProcAddr && g_vk_instance) {
        auto addr = vkGetInstanceProcAddr(g_vk_instance, function_name);
        if (addr) return addr;
    }
    return (PFN_vkVoidFunction)GetProcAddress(vulkan, function_name);
}

static uint32_t vk_find_memory_type(VkPhysicalDevice pdev, uint32_t type_filter, VkMemoryPropertyFlags props) {
    VkPhysicalDeviceMemoryProperties mem_props{};
    vkGetPhysicalDeviceMemoryProperties(pdev, &mem_props);
    for (uint32_t i = 0; i < mem_props.memoryTypeCount; i++)
        if ((type_filter & (1u << i)) && (mem_props.memoryTypes[i].propertyFlags & props) == props)
            return i;
    return UINT32_MAX;
}

struct VulkanOverlayData {
    HMODULE vulkan_dll = nullptr;
    VkInstance instance = VK_NULL_HANDLE;
    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    VkQueue queue = VK_NULL_HANDLE;
    uint32_t queue_family = 0;
    VkRenderPass render_pass = VK_NULL_HANDLE;
    VkDescriptorPool descriptor_pool = VK_NULL_HANDLE;
    VkCommandPool command_pool = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> command_buffers;
    std::vector<VkFramebuffer> framebuffers;
    std::vector<VkImageView> image_views;
    uint32_t image_count = 0;
    VkSampler icon_sampler = VK_NULL_HANDLE;
    std::vector<VkImage>        icon_images;
    std::vector<VkDeviceMemory> icon_memories;
    std::vector<VkImageView>    icon_views;

    void cleanup() {
        if (device) {
            if (vkDeviceWaitIdle) vkDeviceWaitIdle(device);
            for (auto v : icon_views)    if (v && vkDestroyImageView) vkDestroyImageView(device, v, nullptr);
            icon_views.clear();
            for (auto m : icon_memories) if (m && vkFreeMemory)       vkFreeMemory(device, m, nullptr);
            icon_memories.clear();
            for (auto i : icon_images)   if (i && vkDestroyImage)     vkDestroyImage(device, i, nullptr);
            icon_images.clear();
            if (icon_sampler && vkDestroySampler) vkDestroySampler(device, icon_sampler, nullptr);
            icon_sampler = VK_NULL_HANDLE;
            for (auto fb : framebuffers) if (fb && vkDestroyFramebuffer) vkDestroyFramebuffer(device, fb, nullptr);
            framebuffers.clear();
            for (auto iv : image_views) if (iv && vkDestroyImageView) vkDestroyImageView(device, iv, nullptr);
            image_views.clear();
            if (vkFreeCommandBuffers && command_pool) {
                vkFreeCommandBuffers(device, command_pool, (uint32_t)command_buffers.size(), command_buffers.data());
            }
            command_buffers.clear();
            if (vkDestroyCommandPool && command_pool) vkDestroyCommandPool(device, command_pool, nullptr);
            command_pool = VK_NULL_HANDLE;
            if (vkDestroyDescriptorPool && descriptor_pool) vkDestroyDescriptorPool(device, descriptor_pool, nullptr);
            descriptor_pool = VK_NULL_HANDLE;
            if (vkDestroyRenderPass && render_pass) vkDestroyRenderPass(device, render_pass, nullptr);
            render_pass = VK_NULL_HANDLE;
        }
        device = VK_NULL_HANDLE;
        physical_device = VK_NULL_HANDLE;
        instance = VK_NULL_HANDLE;
    }
};

int StarOverlay::hooked_vkCreateInstance(const void* pCreateInfo, const void* pAllocator, void** pInstance)
{
    typedef VkResult(VKAPI_PTR* PFN_vkCreateInstance)(const void*, const void*, void**);
    auto orig = (PFN_vkCreateInstance)g_overlay->orig_vkCreateInstance_;
    VkResult res = orig(pCreateInfo, pAllocator, pInstance);
    if (res == VK_SUCCESS && pInstance && g_overlay) {
        g_overlay->vk_instance_ = *pInstance;
        g_vk_instance = (VkInstance)*pInstance;
    }
    return res;
}

int StarOverlay::hooked_vkCreateDevice(void* physicalDevice, const void* pCreateInfo, const void* pAllocator, void** pDevice)
{
    typedef VkResult(VKAPI_PTR* PFN_vkCreateDevice)(void*, const void*, const void*, void**);
    auto orig = (PFN_vkCreateDevice)g_overlay->orig_vkCreateDevice_;
    VkResult res = orig(physicalDevice, pCreateInfo, pAllocator, pDevice);
    if (res == VK_SUCCESS && pDevice && g_overlay) {
        g_overlay->vk_physical_device_ = physicalDevice;
        g_overlay->vk_device_ = *pDevice;
        g_overlay->vk_queue_family_ = 0;

        struct FakeQueueCreateInfo {
            int sType;
            const void* pNext;
            int flags;
            uint32_t queueFamilyIndex;
        };
        struct FakeCreateInfo {
            int sType;
            const void* pNext;
            int flags;
            uint32_t queueCreateInfoCount;
            const FakeQueueCreateInfo* pQueueCreateInfos;
        };
        auto* ci = (const FakeCreateInfo*)pCreateInfo;
        if (ci && ci->queueCreateInfoCount > 0 && ci->pQueueCreateInfos) {
            g_overlay->vk_queue_family_ = ci->pQueueCreateInfos[0].queueFamilyIndex;
        }

        auto gdpa = (PFN_vkGetDeviceProcAddr)GetProcAddress(GetModuleHandleA("vulkan-1.dll"), "vkGetDeviceProcAddr");
        if (gdpa) {
            void* pCreateSwapchain = (void*)gdpa((VkDevice)*pDevice, "vkCreateSwapchainKHR");
            if (pCreateSwapchain && !g_overlay->orig_vkCreateSwapchainKHR_) {
                MH_CreateHook(pCreateSwapchain, &hooked_vkCreateSwapchainKHR, (void**)&g_overlay->orig_vkCreateSwapchainKHR_);
                MH_EnableHook(pCreateSwapchain);
            }
        }
    }
    return res;
}

int StarOverlay::hooked_vkCreateSwapchainKHR(void* device, const void* pCreateInfo, const void* pAllocator, uint64_t* pSwapchain)
{
    typedef VkResult(VKAPI_PTR* PFN_vkCreateSwapchainKHR)(void*, const void*, const void*, uint64_t*);
    auto orig = (PFN_vkCreateSwapchainKHR)g_overlay->orig_vkCreateSwapchainKHR_;
    VkResult res = orig(device, pCreateInfo, pAllocator, pSwapchain);
    if (res == VK_SUCCESS && pSwapchain && g_overlay) {
        struct FakeSwapchainCreateInfo {
            int sType;
            const void* pNext;
            int flags;
            void* surface;
            uint32_t minImageCount;
            int imageFormat;
        };
        auto* ci = (const FakeSwapchainCreateInfo*)pCreateInfo;
        if (ci) {
            g_overlay->vk_swapchain_format_ = ci->imageFormat;
            g_overlay->vk_min_image_count_ = ci->minImageCount;
        }
        g_overlay->vk_swapchain_recreated_ = true;
    }
    return res;
}

int StarOverlay::hooked_vkQueuePresentKHR(void* queue, const void* pPresentInfo)
{
    if (g_overlay) g_overlay->on_present_vulkan(queue, pPresentInfo);
    typedef VkResult(VKAPI_PTR* PFN_vkQueuePresentKHR)(void*, const void*);
    auto orig = (PFN_vkQueuePresentKHR)g_overlay->orig_vkQueuePresentKHR_;
    return orig(queue, pPresentInfo);
}

void StarOverlay::hook_vulkan()
{
    HMODULE vulkan = GetModuleHandleA("vulkan-1.dll");
    if (!vulkan) vulkan = LoadLibraryA("vulkan-1.dll");
    if (!vulkan) return;

    void* pCreateInstance = (void*)GetProcAddress(vulkan, "vkCreateInstance");
    void* pCreateDevice = (void*)GetProcAddress(vulkan, "vkCreateDevice");
    void* pQueuePresent = (void*)GetProcAddress(vulkan, "vkQueuePresentKHR");

    if (pCreateInstance) {
        MH_CreateHook(pCreateInstance, &hooked_vkCreateInstance, (void**)&orig_vkCreateInstance_);
        MH_EnableHook(pCreateInstance);
    }
    if (pCreateDevice) {
        MH_CreateHook(pCreateDevice, &hooked_vkCreateDevice, (void**)&orig_vkCreateDevice_);
        MH_EnableHook(pCreateDevice);
    }
    if (pQueuePresent) {
        MH_CreateHook(pQueuePresent, &hooked_vkQueuePresentKHR, (void**)&orig_vkQueuePresentKHR_);
        MH_EnableHook(pQueuePresent);
    }
}

void StarOverlay::on_present_vulkan(void* queue, const void* pPresentInfo)
{
    if (!enabled_ || !vk_device_ || !vk_instance_) return;

    std::unique_lock<std::mutex> lock(render_mutex_, std::try_to_lock);
    if (!lock.owns_lock()) return;

    struct FakePresentInfo {
        int sType;
        const void* pNext;
        uint32_t waitSemaphoreCount;
        const uint64_t* pWaitSemaphores;
        uint32_t swapchainCount;
        const uint64_t* pSwapchains;
        const uint32_t* pImageIndices;
    };
    auto* pi = (const FakePresentInfo*)pPresentInfo;
    if (!pi || pi->swapchainCount == 0 || !pi->pSwapchains || !pi->pImageIndices) return;

    uint32_t image_index = pi->pImageIndices[0];
    vk_queue_ = queue;

    if (vk_swapchain_recreated_ || !imgui_initialized_) {
        cleanup_vulkan();
        init_imgui_vulkan(queue, pPresentInfo);
        vk_swapchain_recreated_ = false;
    }

    if (imgui_initialized_ && active_api_ == GraphicsAPI::Vulkan) {
        render_frame_vulkan(queue, pPresentInfo);
    }
}

void StarOverlay::init_imgui_vulkan(void* queue, const void* pPresentInfo)
{
    HMODULE vulkan = GetModuleHandleA("vulkan-1.dll");
    if (!vulkan) return;

    if (!resolve_vulkan_funcs(vulkan)) return;

    VkAttachmentDescription attachment = {};
    attachment.format = (VkFormat)vk_swapchain_format_;
    attachment.samples = VK_SAMPLE_COUNT_1_BIT;
    attachment.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
    attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachment.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference color_attachment = {};
    color_attachment.attachment = 0;
    color_attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &color_attachment;

    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo rp_info = {};
    rp_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    rp_info.attachmentCount = 1;
    rp_info.pAttachments = &attachment;
    rp_info.subpassCount = 1;
    rp_info.pSubpasses = &subpass;
    rp_info.dependencyCount = 1;
    rp_info.pDependencies = &dependency;

    VkRenderPass rp = VK_NULL_HANDLE;
    if (vkCreateRenderPass((VkDevice)vk_device_, &rp_info, nullptr, &rp) != VK_SUCCESS) return;

    VkDescriptorPoolSize pool_sizes[] = {
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 257 }
    };
    VkDescriptorPoolCreateInfo pool_info = {};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    pool_info.maxSets = 257;
    pool_info.poolSizeCount = 1;
    pool_info.pPoolSizes = pool_sizes;

    VkDescriptorPool dp = VK_NULL_HANDLE;
    if (vkCreateDescriptorPool((VkDevice)vk_device_, &pool_info, nullptr, &dp) != VK_SUCCESS) {
        vkDestroyRenderPass((VkDevice)vk_device_, rp, nullptr);
        return;
    }

    struct FakePresentInfo {
        int sType;
        const void* pNext;
        uint32_t waitSemaphoreCount;
        const uint64_t* pWaitSemaphores;
        uint32_t swapchainCount;
        const uint64_t* pSwapchains;
        const uint32_t* pImageIndices;
    };
    auto* pi = (const FakePresentInfo*)pPresentInfo;
    uint64_t swapchain = pi->pSwapchains[0];

    uint32_t count = 0;
    vkGetSwapchainImagesKHR((VkDevice)vk_device_, (VkSwapchainKHR)swapchain, &count, nullptr);
    std::vector<VkImage> images(count);
    vkGetSwapchainImagesKHR((VkDevice)vk_device_, (VkSwapchainKHR)swapchain, &count, images.data());

    std::vector<VkImageView> views(count);
    std::vector<VkFramebuffer> fbs(count);

    if (!hwnd_) hwnd_ = GetActiveWindow();
    RECT rect{};
    if (hwnd_) GetClientRect(hwnd_, &rect);
    uint32_t w = rect.right - rect.left;
    uint32_t h = rect.bottom - rect.top;
    if (w == 0) w = 1280;
    if (h == 0) h = 720;

    for (uint32_t i = 0; i < count; i++) {
        VkImageViewCreateInfo view_info = {};
        view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        view_info.image = images[i];
        view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        view_info.format = (VkFormat)vk_swapchain_format_;
        view_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        view_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        view_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        view_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        view_info.subresourceRange.baseMipLevel = 0;
        view_info.subresourceRange.levelCount = 1;
        view_info.subresourceRange.baseArrayLayer = 0;
        view_info.subresourceRange.layerCount = 1;

        if (vkCreateImageView((VkDevice)vk_device_, &view_info, nullptr, &views[i]) != VK_SUCCESS) return;

        VkFramebufferCreateInfo fb_info = {};
        fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        fb_info.renderPass = rp;
        fb_info.attachmentCount = 1;
        fb_info.pAttachments = &views[i];
        fb_info.width = w;
        fb_info.height = h;
        fb_info.layers = 1;

        if (vkCreateFramebuffer((VkDevice)vk_device_, &fb_info, nullptr, &fbs[i]) != VK_SUCCESS) return;
    }

    VkCommandPoolCreateInfo cp_info = {};
    cp_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cp_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    cp_info.queueFamilyIndex = vk_queue_family_;

    VkCommandPool cp = VK_NULL_HANDLE;
    if (vkCreateCommandPool((VkDevice)vk_device_, &cp_info, nullptr, &cp) != VK_SUCCESS) return;

    std::vector<VkCommandBuffer> cbs(count);
    VkCommandBufferAllocateInfo cb_info = {};
    cb_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cb_info.commandPool = cp;
    cb_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cb_info.commandBufferCount = count;
    if (vkAllocateCommandBuffers((VkDevice)vk_device_, &cb_info, cbs.data()) != VK_SUCCESS) return;

    ImGui::CreateContext();
    ImGui_ImplWin32_Init(hwnd_);
    hook_window();

    ImGui_ImplVulkan_LoadFunctions(&ImGuiVulkanLoader, vulkan);

    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = (VkInstance)vk_instance_;
    init_info.PhysicalDevice = (VkPhysicalDevice)vk_physical_device_;
    init_info.Device = (VkDevice)vk_device_;
    init_info.QueueFamily = vk_queue_family_;
    init_info.Queue = (VkQueue)queue;
    init_info.DescriptorPool = dp;
    init_info.RenderPass = rp;
    init_info.MinImageCount = vk_min_image_count_;
    init_info.ImageCount = count;
    init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

    if (ImGui_ImplVulkan_Init(&init_info)) {
        setup_imgui_style_and_fonts();
        imgui_initialized_ = true;
        active_api_ = GraphicsAPI::Vulkan;

        auto* data = new VulkanOverlayData();
        data->vulkan_dll = vulkan;
        data->instance = (VkInstance)vk_instance_;
        data->physical_device = (VkPhysicalDevice)vk_physical_device_;
        data->device = (VkDevice)vk_device_;
        data->queue = (VkQueue)queue;
        data->queue_family = vk_queue_family_;
        data->render_pass = rp;
        data->descriptor_pool = dp;
        data->command_pool = cp;
        data->command_buffers = cbs;
        data->framebuffers = fbs;
        data->image_views = views;
        data->image_count = count;

        VkSamplerCreateInfo samp_info = {};
        samp_info.sType        = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samp_info.magFilter    = VK_FILTER_LINEAR;
        samp_info.minFilter    = VK_FILTER_LINEAR;
        samp_info.mipmapMode   = VK_SAMPLER_MIPMAP_MODE_NEAREST;
        samp_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samp_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samp_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        samp_info.maxLod       = 1.f;
        if (vkCreateSampler((VkDevice)vk_device_, &samp_info, nullptr, &data->icon_sampler) != VK_SUCCESS)
            data->icon_sampler = VK_NULL_HANDLE;

        context_ = (ID3D11DeviceContext*)data;
    }
}

void StarOverlay::render_frame_vulkan(void* queue, const void* pPresentInfo)
{
    auto* data = (VulkanOverlayData*)context_;
    if (!data) return;

    struct FakePresentInfo {
        int sType;
        const void* pNext;
        uint32_t waitSemaphoreCount;
        const uint64_t* pWaitSemaphores;
        uint32_t swapchainCount;
        const uint64_t* pSwapchains;
        const uint32_t* pImageIndices;
    };
    auto* pi = (const FakePresentInfo*)pPresentInfo;
    uint32_t image_index = pi->pImageIndices[0];
    if (image_index >= data->image_count) return;

    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    float dt = ImGui::GetIO().DeltaTime;
    if (dt <= 0.f) dt = 0.0167f;

    float target = open_ ? 1.f : 0.f;
    panel_anim_ += (target - panel_anim_) * clamp01(12.f * dt);
    panel_anim_  = clamp01(panel_anim_);

    if (panel_anim_ > 0.001f) render_panel();
    render_notifications(dt);

    ImGui::Render();

    VkCommandBufferBeginInfo begin_info = {};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    VkCommandBuffer cb = data->command_buffers[image_index];
    vkResetCommandBuffer(cb, 0);
    vkBeginCommandBuffer(cb, &begin_info);

    RECT rect{};
    if (hwnd_) GetClientRect(hwnd_, &rect);
    uint32_t w = rect.right - rect.left;
    uint32_t h = rect.bottom - rect.top;
    if (w == 0) w = 1280;
    if (h == 0) h = 720;

    VkRenderPassBeginInfo rp_begin = {};
    rp_begin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rp_begin.renderPass = data->render_pass;
    rp_begin.framebuffer = data->framebuffers[image_index];
    rp_begin.renderArea.extent.width = w;
    rp_begin.renderArea.extent.height = h;

    vkCmdBeginRenderPass(cb, &rp_begin, VK_SUBPASS_CONTENTS_INLINE);
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cb);
    vkCmdEndRenderPass(cb);
    vkEndCommandBuffer(cb);

    VkSubmitInfo submit = {};
    submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit.commandBufferCount = 1;
    submit.pCommandBuffers = &cb;

    if (vkQueueSubmit) {
        vkQueueSubmit((VkQueue)queue, 1, &submit, VK_NULL_HANDLE);
    }
}

ImTextureID StarOverlay::upload_icon_vulkan(const std::vector<uint8_t>& rgba, int w, int h)
{
    auto* data = (VulkanOverlayData*)context_;
    if (!data || !data->device || !data->icon_sampler || !data->command_pool) return nullptr;

    VkDevice dev  = data->device;
    VkQueue  que  = data->queue;
    VkCommandPool pool = data->command_pool;

    VkBufferCreateInfo buf_info = {};
    buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buf_info.size  = (VkDeviceSize)w * h * 4;
    buf_info.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
    buf_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    VkBuffer staging = VK_NULL_HANDLE;
    if (vkCreateBuffer(dev, &buf_info, nullptr, &staging) != VK_SUCCESS) return nullptr;

    VkMemoryRequirements buf_req{};
    vkGetBufferMemoryRequirements(dev, staging, &buf_req);
    uint32_t buf_mtype = vk_find_memory_type((VkPhysicalDevice)vk_physical_device_, buf_req.memoryTypeBits,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    if (buf_mtype == UINT32_MAX) { vkDestroyBuffer(dev, staging, nullptr); return nullptr; }

    VkMemoryAllocateInfo buf_alloc = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
    buf_alloc.allocationSize  = buf_req.size;
    buf_alloc.memoryTypeIndex = buf_mtype;
    VkDeviceMemory staging_mem = VK_NULL_HANDLE;
    if (vkAllocateMemory(dev, &buf_alloc, nullptr, &staging_mem) != VK_SUCCESS) {
        vkDestroyBuffer(dev, staging, nullptr); return nullptr;
    }
    vkBindBufferMemory(dev, staging, staging_mem, 0);

    void* mapped = nullptr;
    vkMapMemory(dev, staging_mem, 0, buf_req.size, 0, &mapped);
    memcpy(mapped, rgba.data(), (size_t)w * h * 4);
    vkUnmapMemory(dev, staging_mem);

    VkImageCreateInfo img_info = {};
    img_info.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    img_info.imageType     = VK_IMAGE_TYPE_2D;
    img_info.format        = VK_FORMAT_R8G8B8A8_UNORM;
    img_info.extent        = { (uint32_t)w, (uint32_t)h, 1 };
    img_info.mipLevels     = 1;
    img_info.arrayLayers   = 1;
    img_info.samples       = VK_SAMPLE_COUNT_1_BIT;
    img_info.tiling        = VK_IMAGE_TILING_OPTIMAL;
    img_info.usage         = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    img_info.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;
    img_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    VkImage image = VK_NULL_HANDLE;
    if (vkCreateImage(dev, &img_info, nullptr, &image) != VK_SUCCESS) {
        vkFreeMemory(dev, staging_mem, nullptr); vkDestroyBuffer(dev, staging, nullptr); return nullptr;
    }

    VkMemoryRequirements img_req{};
    vkGetImageMemoryRequirements(dev, image, &img_req);
    uint32_t img_mtype = vk_find_memory_type((VkPhysicalDevice)vk_physical_device_, img_req.memoryTypeBits,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (img_mtype == UINT32_MAX) {
        vkDestroyImage(dev, image, nullptr);
        vkFreeMemory(dev, staging_mem, nullptr); vkDestroyBuffer(dev, staging, nullptr); return nullptr;
    }
    VkMemoryAllocateInfo img_alloc = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
    img_alloc.allocationSize  = img_req.size;
    img_alloc.memoryTypeIndex = img_mtype;
    VkDeviceMemory img_mem = VK_NULL_HANDLE;
    if (vkAllocateMemory(dev, &img_alloc, nullptr, &img_mem) != VK_SUCCESS) {
        vkDestroyImage(dev, image, nullptr);
        vkFreeMemory(dev, staging_mem, nullptr);
        vkDestroyBuffer(dev, staging, nullptr);
        return nullptr;
    }
    vkBindImageMemory(dev, image, img_mem, 0);

    VkCommandBufferAllocateInfo cb_alloc = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
    cb_alloc.commandPool        = pool;
    cb_alloc.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cb_alloc.commandBufferCount = 1;
    VkCommandBuffer cb = VK_NULL_HANDLE;
    if (vkAllocateCommandBuffers(dev, &cb_alloc, &cb) != VK_SUCCESS) {
        vkFreeMemory(dev, img_mem, nullptr);
        vkDestroyImage(dev, image, nullptr);
        vkFreeMemory(dev, staging_mem, nullptr);
        vkDestroyBuffer(dev, staging, nullptr);
        return nullptr;
    }

    VkCommandBufferBeginInfo begin = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
    begin.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(cb, &begin);

    auto transition = [&](VkImageLayout from, VkImageLayout to,
                          VkPipelineStageFlags src_stage, VkPipelineStageFlags dst_stage,
                          VkAccessFlags src_access, VkAccessFlags dst_access) {
        VkImageMemoryBarrier barrier = { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
        barrier.oldLayout           = from;
        barrier.newLayout           = to;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image               = image;
        barrier.subresourceRange    = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
        barrier.srcAccessMask       = src_access;
        barrier.dstAccessMask       = dst_access;
        vkCmdPipelineBarrier(cb, src_stage, dst_stage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
    };

    transition(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
               VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
               0, VK_ACCESS_TRANSFER_WRITE_BIT);

    VkBufferImageCopy copy = {};
    copy.imageSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
    copy.imageExtent      = { (uint32_t)w, (uint32_t)h, 1 };
    vkCmdCopyBufferToImage(cb, staging, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy);

    transition(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
               VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
               VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT);

    vkEndCommandBuffer(cb);

    VkFenceCreateInfo fence_info = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
    VkFence fence = VK_NULL_HANDLE;
    if (vkCreateFence(dev, &fence_info, nullptr, &fence) != VK_SUCCESS) {
        vkFreeCommandBuffers(dev, pool, 1, &cb);
        vkFreeMemory(dev, img_mem, nullptr);
        vkDestroyImage(dev, image, nullptr);
        vkFreeMemory(dev, staging_mem, nullptr);
        vkDestroyBuffer(dev, staging, nullptr);
        return nullptr;
    }

    VkSubmitInfo submit = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
    submit.commandBufferCount = 1;
    submit.pCommandBuffers    = &cb;
    if (vkQueueSubmit(que, 1, &submit, fence) != VK_SUCCESS) {
        vkDestroyFence(dev, fence, nullptr);
        vkFreeCommandBuffers(dev, pool, 1, &cb);
        vkFreeMemory(dev, img_mem, nullptr);
        vkDestroyImage(dev, image, nullptr);
        vkFreeMemory(dev, staging_mem, nullptr);
        vkDestroyBuffer(dev, staging, nullptr);
        return nullptr;
    }
    vkWaitForFences(dev, 1, &fence, VK_TRUE, UINT64_MAX);
    vkDestroyFence(dev, fence, nullptr);
    vkFreeCommandBuffers(dev, pool, 1, &cb);
    vkFreeMemory(dev, staging_mem, nullptr);
    vkDestroyBuffer(dev, staging, nullptr);

    VkImageViewCreateInfo view_info = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
    view_info.image            = image;
    view_info.viewType         = VK_IMAGE_VIEW_TYPE_2D;
    view_info.format           = VK_FORMAT_R8G8B8A8_UNORM;
    view_info.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
    VkImageView view = VK_NULL_HANDLE;
    if (vkCreateImageView(dev, &view_info, nullptr, &view) != VK_SUCCESS) {
        vkFreeMemory(dev, img_mem, nullptr);
        vkDestroyImage(dev, image, nullptr);
        return nullptr;
    }

    data->icon_images.push_back(image);
    data->icon_memories.push_back(img_mem);
    data->icon_views.push_back(view);

    return ImGui_ImplVulkan_AddTexture(data->icon_sampler, view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
}

void StarOverlay::cleanup_vulkan()
{
    if (active_api_ == GraphicsAPI::Vulkan && context_) {
        auto* data = (VulkanOverlayData*)context_;
        data->cleanup();
        delete data;
        context_ = nullptr;
    }
}

int WINAPI StarOverlay::hooked_ShowCursor(BOOL bShow)
{
    if (g_overlay && g_overlay->orig_show_cursor_) {
        if (g_overlay->open_) {
            int current = g_overlay->orig_show_cursor_(TRUE);
            g_overlay->orig_show_cursor_(FALSE);
            current--;

            if (!bShow) {
                if (current <= 0) {
                    return 0;
                }
            }
        }
        return g_overlay->orig_show_cursor_(bShow);
    }
    return bShow ? 0 : -1;
}

BOOL WINAPI StarOverlay::hooked_ClipCursor(const RECT* lpRect)
{
    if (g_overlay && g_overlay->orig_clip_cursor_) {
        if (g_overlay->open_) {
            return g_overlay->orig_clip_cursor_(nullptr);
        }
        return g_overlay->orig_clip_cursor_(lpRect);
    }
    return TRUE;
}

HCURSOR WINAPI StarOverlay::hooked_SetCursor(HCURSOR hCursor)
{
    if (g_overlay && g_overlay->orig_set_cursor_) {
        if (g_overlay->open_) {
            HCURSOR arrow = LoadCursor(nullptr, IDC_ARROW);
            return g_overlay->orig_set_cursor_(arrow);
        }
        return g_overlay->orig_set_cursor_(hCursor);
    }
    return nullptr;
}
