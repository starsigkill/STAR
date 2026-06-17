#pragma once
#include "core/star_common.h"
#include <dxgi1_4.h>
#include "imgui.h"

struct AchievementNotification {
    std::string title;
    std::string description;
    std::vector<uint8_t> icon_rgba;
    int   icon_width  = 0;
    int   icon_height = 0;
    float time_remaining = 5.0f;
    float age = 0.0f;
};

class StarOverlay {
public:
    static StarOverlay& get();

    void init();
    void shutdown();

    void push_achievement(const std::string& name, const std::string& desc,
                          const std::vector<uint8_t>& icon_rgba, int iw, int ih);

    bool is_enabled() const { return enabled_; }
    bool is_open()    const { return open_; }

private:
    StarOverlay() = default;

    enum class GraphicsAPI { None, DX9, DX11, DX12, OpenGL, Vulkan };
    GraphicsAPI active_api_ = GraphicsAPI::None;

    void hook_dx11();
    void on_present(IDXGISwapChain* chain, UINT sync_interval, UINT flags);
    void on_resize_buffers(IDXGISwapChain* chain, UINT bc, UINT w, UINT h, DXGI_FORMAT fmt, UINT fl);
    void render_frame(IDXGISwapChain* chain);
    void init_imgui(IDXGISwapChain* chain);
    void cleanup_rtv();
    ImTextureID get_or_create_icon(const std::string& key,
                                   const std::vector<uint8_t>& rgba, int w, int h);

#ifdef _WIN64
    void on_present_dx12(IDXGISwapChain* chain);
    void init_imgui_dx12(IDXGISwapChain* chain, void* device, void* command_queue);
    void render_frame_dx12(IDXGISwapChain* chain);
    void cleanup_dx12();
    void hook_dx12_ecl();
    ImTextureID upload_icon_dx12(const std::vector<uint8_t>& rgba, int w, int h);
#endif

    using DX9PresentFn = HRESULT(STDMETHODCALLTYPE*)(struct IDirect3DDevice9*, const RECT*, const RECT*, HWND, const struct RGNDATA*);
    using DX9ResetFn   = HRESULT(STDMETHODCALLTYPE*)(struct IDirect3DDevice9*, void*);
    DX9PresentFn orig_dx9_present_ = nullptr;
    DX9ResetFn   orig_dx9_reset_   = nullptr;
    static HRESULT STDMETHODCALLTYPE hooked_DX9Present(struct IDirect3DDevice9*, const RECT*, const RECT*, HWND, const struct RGNDATA*);
    static HRESULT STDMETHODCALLTYPE hooked_DX9Reset(struct IDirect3DDevice9*, void*);
    void hook_dx9();
    void on_present_dx9(struct IDirect3DDevice9* device);
    void on_reset_dx9();

    using wglSwapBuffersFn = BOOL(WINAPI*)(HDC);
    wglSwapBuffersFn orig_wglSwapBuffers_ = nullptr;
    static BOOL WINAPI hooked_wglSwapBuffers(HDC);
    void hook_opengl();
    void on_present_opengl(HDC hdc);

    void* vk_instance_ = nullptr;
    void* vk_physical_device_ = nullptr;
    void* vk_device_ = nullptr;
    void* vk_queue_ = nullptr;
    uint32_t vk_queue_family_ = 0;
    int vk_swapchain_format_ = 0;
    uint32_t vk_min_image_count_ = 2;
    bool vk_swapchain_recreated_ = false;
    void* orig_vkCreateInstance_ = nullptr;
    void* orig_vkCreateDevice_ = nullptr;
    void* orig_vkCreateSwapchainKHR_ = nullptr;
    void* orig_vkQueuePresentKHR_ = nullptr;
    static int hooked_vkCreateInstance(const void*, const void*, void**);
    static int hooked_vkCreateDevice(void*, const void*, const void*, void**);
    static int hooked_vkCreateSwapchainKHR(void*, const void*, const void*, uint64_t*);
    static int hooked_vkQueuePresentKHR(void*, const void*);
    void hook_vulkan();
    void on_present_vulkan(void* queue, const void* pPresentInfo);
    void init_imgui_vulkan(void* queue, const void* pPresentInfo);
    void render_frame_vulkan(void* queue, const void* pPresentInfo);
    void cleanup_vulkan();
    ImTextureID upload_icon_vulkan(const std::vector<uint8_t>& rgba, int w, int h);

    void render_notifications(float dt);
    void render_panel();
    void setup_imgui_style_and_fonts();
    void hook_window();

    bool  enabled_           = true;
    bool  imgui_initialized_ = false;
    bool  hook_attempted_    = false;
    bool  hooks_installed_   = false;
    bool  open_              = false;
    float panel_anim_        = 0.0f;
    float scroll_target_y_   = -1.0f;
    float scroll_current_y_  = 0.0f;
    int   cursor_show_count_offset_ = 0;

    ID3D11Device*           device_        = nullptr;
    ID3D11DeviceContext*    context_       = nullptr;
    ID3D11RenderTargetView* rtv_           = nullptr;
    HWND                    hwnd_          = nullptr;
    WNDPROC                 wnd_proc_orig_ = nullptr;

#ifdef _WIN64
    void* dx12_device_ = nullptr;
    void* dx12_command_queue_ = nullptr;
    void* dx12_rtv_heap_ = nullptr;
    void* dx12_srv_heap_ = nullptr;
    void* dx12_command_list_ = nullptr;
    std::vector<void*> dx12_command_allocators_;
    std::vector<void*> dx12_resources_;
    UINT dx12_buffer_count_ = 0;
    UINT dx12_srv_next_slot_ = 1;
    std::vector<void*> dx12_icon_resources_;

    using ExecuteCommandListsFn = void(STDMETHODCALLTYPE*)(void*, UINT, void* const*);
    ExecuteCommandListsFn orig_execute_command_lists_ = nullptr;
    static void STDMETHODCALLTYPE hooked_ExecuteCommandLists(void* queue, UINT count, void* const* lists);
    static void* g_dx12_captured_queue_;
#endif

    void* font_small_ = nullptr;
    void* font_title_ = nullptr;

    std::mutex                        render_mutex_;
    std::mutex                        notif_mutex_;
    std::vector<AchievementNotification> notifications_;
    std::unordered_map<std::string, ImTextureID> icon_textures_;

    using PresentFn       = HRESULT (STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
    using Present1Fn      = HRESULT (STDMETHODCALLTYPE*)(IDXGISwapChain1*, UINT, UINT, const DXGI_PRESENT_PARAMETERS*);
    using ResizeBuffersFn = HRESULT (STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
    PresentFn       orig_present_  = nullptr;
    Present1Fn      orig_present1_ = nullptr;
    ResizeBuffersFn orig_resize_   = nullptr;

    using ShowCursorFn = int(WINAPI*)(BOOL);
    using ClipCursorFn = BOOL(WINAPI*)(const RECT*);
    using SetCursorFn  = HCURSOR(WINAPI*)(HCURSOR);
    ShowCursorFn    orig_show_cursor_ = nullptr;
    ClipCursorFn    orig_clip_cursor_ = nullptr;
    SetCursorFn     orig_set_cursor_  = nullptr;

    static HRESULT STDMETHODCALLTYPE hooked_Present(IDXGISwapChain*, UINT, UINT);
    static HRESULT STDMETHODCALLTYPE hooked_Present1(IDXGISwapChain1*, UINT, UINT, const DXGI_PRESENT_PARAMETERS*);
    static HRESULT STDMETHODCALLTYPE hooked_ResizeBuffers(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
    static LRESULT CALLBACK          star_wnd_proc(HWND, UINT, WPARAM, LPARAM);

    static int WINAPI hooked_ShowCursor(BOOL bShow);
    static BOOL WINAPI hooked_ClipCursor(const RECT* lpRect);
    static HCURSOR WINAPI hooked_SetCursor(HCURSOR hCursor);
};
