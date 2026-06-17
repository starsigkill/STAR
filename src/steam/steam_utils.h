#pragma once
#include "core/star_common.h"
#include "steam/isteamutils001.h"
#include "steam/isteamutils002.h"
#include "steam/isteamutils003.h"
#include "steam/isteamutils004.h"
#include "steam/isteamutils005.h"
#include "steam/isteamutils006.h"
#include "steam/isteamutils007.h"
#include "steam/isteamutils008.h"
#include "steam/isteamutils009.h"

struct StarImage {
    std::vector<uint8_t> rgba;
    uint32_t width = 0;
    uint32_t height = 0;
};

class StarSteamUtils :
    public ISteamUtils001,
    public ISteamUtils002,
    public ISteamUtils003,
    public ISteamUtils004,
    public ISteamUtils005,
    public ISteamUtils006,
    public ISteamUtils007,
    public ISteamUtils008,
    public ISteamUtils009,
    public ISteamUtils {
public:
    static StarSteamUtils& get();

    uint32 GetSecondsSinceAppActive() override;
    uint32 GetSecondsSinceComputerActive() override;
    EUniverse GetConnectedUniverse() override;
    uint32 GetServerRealTime() override;
    const char* GetIPCountry() override;
    bool GetImageSize(int iImage, uint32* pnWidth, uint32* pnHeight) override;
    bool GetImageRGBA(int iImage, uint8* pubDest, int nDestBufferSize) override;
    bool GetCSERIPPort(uint32* unIP, uint16* usPort) override;
    uint8 GetCurrentBatteryPower() override;
    uint32 GetAppID() override;
    void SetOverlayNotificationPosition(ENotificationPosition eNotificationPosition) override;
    bool IsAPICallCompleted(SteamAPICall_t hSteamAPICall, bool* pbFailed) override;
    ESteamAPICallFailure GetAPICallFailureReason(SteamAPICall_t hSteamAPICall) override;
    bool GetAPICallResult(SteamAPICall_t hSteamAPICall, void* pCallback, int cubCallback, int iCallbackExpected, bool* pbFailed) override;
    void RunFrame() override;
    uint32 GetIPCCallCount() override;
    void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction) override;
    bool IsOverlayEnabled() override;
    bool BOverlayNeedsPresent() override;
    SteamAPICall_t CheckFileSignature(const char* szFileName) override;
    bool ShowGamepadTextInput(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32 unCharMax, const char* pchExistingText) override;
    uint32 GetEnteredGamepadTextLength() override;
    bool GetEnteredGamepadTextInput(char* pchText, uint32 cchText) override;
    const char* GetSteamUILanguage() override;
    bool IsSteamRunningInVR() override;
    void SetOverlayNotificationInset(int nHorizontalInset, int nVerticalInset) override;

    bool ShowGamepadTextInput(EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char* pchDescription, uint32 unCharMax) override;

    bool IsSteamInBigPictureMode() override;
    void StartVRDashboard() override;

    bool IsVRHeadsetStreamingEnabled() override;
    void SetVRHeadsetStreamingEnabled(bool bEnabled) override;
    bool IsSteamChinaLauncher() override;
    ESteamIPv6ConnectivityState GetIPv6ConnectivityState(ESteamIPv6ConnectivityProtocol eProtocol) override;

    bool InitFilterText() override;
    int FilterText(char* pchOutFilteredText, uint32 nByteSizeOutFilteredText, const char* pchInputMessage, bool bLegalOnly) override;

    bool InitFilterText(uint32 unFilterOptions) override;
    int FilterText(ETextFilteringContext eContext, CSteamID sourceSteamID, const char* pchInputMessage, char* pchOutFilteredText, uint32 nByteSizeOutFilteredText) override;

    bool IsSteamRunningOnSteamDeck() override;
    bool ShowFloatingGamepadTextInput(EFloatingGamepadTextInputMode eKeyboardMode, int nTextFieldXPosition, int nTextFieldYPosition, int nTextFieldWidth, int nTextFieldHeight) override;
    void SetGameLauncherMode(bool bLauncherMode) override;
    bool DismissFloatingGamepadTextInput() override;
    bool DismissGamepadTextInput() override;

    int StoreImage(uint32_t w, uint32_t h, const std::vector<uint8_t>& rgba);
    int LoadImageFromFile(const std::string& path);

private:
    StarSteamUtils();
    std::chrono::steady_clock::time_point start_time_;
    std::vector<StarImage> images_;
    std::mutex images_mutex_;
};
