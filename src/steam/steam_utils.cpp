#include "steam/steam_utils.h"
#include "core/callbacks.h"
#include "core/settings.h"
#include "steam/isteamutils.h"
#include <wincodec.h>
#pragma comment(lib, "WindowsCodecs.lib")

StarSteamUtils::StarSteamUtils()
    : start_time_(std::chrono::steady_clock::now())
{
}

StarSteamUtils& StarSteamUtils::get()
{
    static StarSteamUtils instance;
    return instance;
}

uint32 StarSteamUtils::GetSecondsSinceAppActive()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time_).count();
    return (uint32)elapsed;
}

uint32 StarSteamUtils::GetSecondsSinceComputerActive()
{

    LASTINPUTINFO lii{};
    lii.cbSize = sizeof(lii);
    GetLastInputInfo(&lii);
    DWORD tick = GetTickCount();
    DWORD idle_ms = tick - lii.dwTime;
    return idle_ms / 1000u;
}

EUniverse StarSteamUtils::GetConnectedUniverse()
{
    return k_EUniversePublic;
}

uint32 StarSteamUtils::GetServerRealTime()
{
    return (uint32)time(nullptr);
}

const char* StarSteamUtils::GetIPCountry()
{
    return "US";
}

bool StarSteamUtils::GetImageSize(int iImage, uint32* pnWidth, uint32* pnHeight)
{
    if (iImage <= 0) return false;
    std::lock_guard<std::mutex> lock(images_mutex_);
    int idx = iImage - 1;
    if (idx < 0 || idx >= (int)images_.size()) return false;
    if (pnWidth)  *pnWidth  = images_[idx].width;
    if (pnHeight) *pnHeight = images_[idx].height;
    return true;
}

bool StarSteamUtils::GetImageRGBA(int iImage, uint8* pubDest, int nDestBufferSize)
{
    if (iImage <= 0 || !pubDest) return false;
    std::lock_guard<std::mutex> lock(images_mutex_);
    int idx = iImage - 1;
    if (idx < 0 || idx >= (int)images_.size()) return false;
    const auto& img = images_[idx];
    int needed = (int)(img.width * img.height * 4);
    if (nDestBufferSize < needed) return false;
    memcpy(pubDest, img.rgba.data(), needed);
    return true;
}

bool StarSteamUtils::GetCSERIPPort(uint32* unIP, uint16* usPort)
{
    STAR_UNREFERENCED(unIP); STAR_UNREFERENCED(usPort);
    return false;
}

uint8 StarSteamUtils::GetCurrentBatteryPower()
{
    SYSTEM_POWER_STATUS sps{};
    GetSystemPowerStatus(&sps);
    if (sps.ACLineStatus == 1) return 255;
    return sps.BatteryLifePercent;
}

uint32 StarSteamUtils::GetAppID()
{
    return Settings::get().app_id;
}

void StarSteamUtils::SetOverlayNotificationPosition(ENotificationPosition eNotificationPosition)
{
    STAR_UNREFERENCED(eNotificationPosition);
}

bool StarSteamUtils::IsAPICallCompleted(SteamAPICall_t hSteamAPICall, bool* pbFailed)
{
    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    auto it = g_pending_results.find(hSteamAPICall);
    bool found = (it != g_pending_results.end());
    if (pbFailed) *pbFailed = found ? it->second.io_failure : false;
    return found;
}

ESteamAPICallFailure StarSteamUtils::GetAPICallFailureReason(SteamAPICall_t hSteamAPICall)
{
    STAR_UNREFERENCED(hSteamAPICall);
    return k_ESteamAPICallFailureNone;
}

bool StarSteamUtils::GetAPICallResult(SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed)
{
    std::lock_guard<std::mutex> lock(g_callbacks_mutex);
    auto it = g_pending_results.find(hSteamAPICall);
    if (it == g_pending_results.end()) return false;
    if (it->second.callback_id != iCallbackExpected) return false;
    if (pbFailed) *pbFailed = it->second.io_failure;
    if (pCallback && cubCallback > 0 && !it->second.data.empty()) {
        int bytes = std::min(cubCallback, (int)it->second.data.size());
        memcpy(pCallback, it->second.data.data(), bytes);
    }
    g_pending_results.erase(it);
    return true;
}

void StarSteamUtils::RunFrame()
{
    STAR_RunCallbacks();
}

uint32 StarSteamUtils::GetIPCCallCount()
{
    return 1;
}

void StarSteamUtils::SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction)
{
    STAR_UNREFERENCED(pFunction);
}

bool StarSteamUtils::IsOverlayEnabled()
{
    return Settings::get().overlay_enabled;
}

bool StarSteamUtils::BOverlayNeedsPresent()
{
    return false;
}

SteamAPICall_t StarSteamUtils::CheckFileSignature(const char* szFileName)
{
    STAR_UNREFERENCED(szFileName);
    CheckFileSignature_t result{};
    result.m_eCheckFileSignature = k_ECheckFileSignatureNoSignaturesFoundForThisApp;
    return STAR_PostCallResult(CheckFileSignature_t::k_iCallback, &result, sizeof(result));
}

bool StarSteamUtils::ShowGamepadTextInput(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32 unCharMax, const char* pchExistingText)
{
    STAR_UNREFERENCED(eInputMode); STAR_UNREFERENCED(eLineInputMode);
    STAR_UNREFERENCED(pchDescription); STAR_UNREFERENCED(unCharMax); STAR_UNREFERENCED(pchExistingText);
    return false;
}

uint32 StarSteamUtils::GetEnteredGamepadTextLength() { return 0; }

bool StarSteamUtils::GetEnteredGamepadTextInput(char* pchText, uint32 cchText)
{
    STAR_UNREFERENCED(cchText);
    if (pchText) pchText[0] = 0;
    return false;
}

const char* StarSteamUtils::GetSteamUILanguage()
{
    return Settings::get().language.c_str();
}

bool StarSteamUtils::IsSteamRunningInVR() { return false; }

void StarSteamUtils::SetOverlayNotificationInset(int nHorizontalInset, int nVerticalInset)
{
    STAR_UNREFERENCED(nHorizontalInset); STAR_UNREFERENCED(nVerticalInset);
}

int StarSteamUtils::StoreImage(uint32_t w, uint32_t h, const std::vector<uint8_t>& rgba)
{
    std::lock_guard<std::mutex> lock(images_mutex_);
    StarImage img;
    img.width = w;
    img.height = h;
    img.rgba = rgba;
    images_.push_back(std::move(img));
    return (int)images_.size();
}

int StarSteamUtils::LoadImageFromFile(const std::string& path)
{
    if (path.empty()) return 0;

    IWICImagingFactory* factory = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory, (void**)&factory);
    if (FAILED(hr) || !factory) return 0;

    int wlen = MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, nullptr, 0);
    std::wstring wpath(wlen, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, wpath.data(), wlen);

    IWICBitmapDecoder* decoder = nullptr;
    hr = factory->CreateDecoderFromFilename(wpath.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
    if (FAILED(hr) || !decoder) { factory->Release(); return 0; }

    IWICBitmapFrameDecode* frame = nullptr;
    hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr) || !frame) { decoder->Release(); factory->Release(); return 0; }

    IWICFormatConverter* converter = nullptr;
    factory->CreateFormatConverter(&converter);
    if (!converter) { frame->Release(); decoder->Release(); factory->Release(); return 0; }

    converter->Initialize(frame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone,
        nullptr, 0.0, WICBitmapPaletteTypeCustom);

    UINT w = 0, h = 0;
    converter->GetSize(&w, &h);

    std::vector<uint8_t> rgba(w * h * 4);
    UINT stride = w * 4;
    converter->CopyPixels(nullptr, stride, (UINT)rgba.size(), rgba.data());

    converter->Release();
    frame->Release();
    decoder->Release();
    factory->Release();

    return StoreImage(w, h, rgba);
}

bool StarSteamUtils::ShowGamepadTextInput(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32 unCharMax)
{
    return ShowGamepadTextInput(eInputMode, eLineInputMode, pchDescription, unCharMax, nullptr);
}

bool StarSteamUtils::IsSteamInBigPictureMode() { return false; }
void StarSteamUtils::StartVRDashboard() {}
bool StarSteamUtils::IsVRHeadsetStreamingEnabled() { return false; }
void StarSteamUtils::SetVRHeadsetStreamingEnabled(bool bEnabled) { STAR_UNREFERENCED(bEnabled); }
bool StarSteamUtils::IsSteamChinaLauncher() { return false; }

ESteamIPv6ConnectivityState StarSteamUtils::GetIPv6ConnectivityState(ESteamIPv6ConnectivityProtocol eProtocol)
{
    STAR_UNREFERENCED(eProtocol);
    return k_ESteamIPv6ConnectivityState_Unknown;
}

bool StarSteamUtils::InitFilterText() { return false; }

int StarSteamUtils::FilterText(char* pchOutFilteredText, uint32 nByteSizeOutFilteredText, const char* pchInputMessage, bool bLegalOnly)
{
    STAR_UNREFERENCED(bLegalOnly);

    if (pchOutFilteredText && nByteSizeOutFilteredText > 0) {
        if (pchInputMessage) strncpy_s(pchOutFilteredText, nByteSizeOutFilteredText, pchInputMessage, _TRUNCATE);
        else pchOutFilteredText[0] = 0;
    }
    return pchInputMessage ? (int)strlen(pchInputMessage) : 0;
}

bool StarSteamUtils::InitFilterText(uint32 unFilterOptions) { STAR_UNREFERENCED(unFilterOptions); return false; }

int StarSteamUtils::FilterText(ETextFilteringContext eContext, CSteamID sourceSteamID, const char* pchInputMessage, char* pchOutFilteredText, uint32 nByteSizeOutFilteredText)
{
    STAR_UNREFERENCED(eContext); STAR_UNREFERENCED(sourceSteamID);
    if (pchOutFilteredText && nByteSizeOutFilteredText > 0) {
        if (pchInputMessage) strncpy_s(pchOutFilteredText, nByteSizeOutFilteredText, pchInputMessage, _TRUNCATE);
        else pchOutFilteredText[0] = 0;
    }
    return pchInputMessage ? (int)strlen(pchInputMessage) : 0;
}

bool StarSteamUtils::IsSteamRunningOnSteamDeck() { return false; }

bool StarSteamUtils::ShowFloatingGamepadTextInput(EFloatingGamepadTextInputMode eKeyboardMode, int x, int y, int w, int h)
{
    STAR_UNREFERENCED(eKeyboardMode); STAR_UNREFERENCED(x); STAR_UNREFERENCED(y);
    STAR_UNREFERENCED(w); STAR_UNREFERENCED(h);
    return false;
}

void StarSteamUtils::SetGameLauncherMode(bool bLauncherMode) { STAR_UNREFERENCED(bLauncherMode); }
bool StarSteamUtils::DismissFloatingGamepadTextInput() { return false; }
bool StarSteamUtils::DismissGamepadTextInput() { return false; }
