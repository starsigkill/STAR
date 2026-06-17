#pragma once
#include "core/star_common.h"
#include "steam/isteamscreenshots.h"

class StarSteamScreenshots : public ISteamScreenshots {
public:
    static StarSteamScreenshots& get();
    ScreenshotHandle WriteScreenshot(void* pubRGB, uint32 cubRGB, int nWidth, int nHeight) override;
    ScreenshotHandle AddScreenshotToLibrary(const char* pchFilename, const char* pchThumbnailFilename, int nWidth, int nHeight) override;
    void TriggerScreenshot() override;
    void HookScreenshots(bool bHook) override;
    bool SetLocation(ScreenshotHandle hScreenshot, const char* pchLocation) override;
    bool TagUser(ScreenshotHandle hScreenshot, CSteamID steamID) override;
    bool TagPublishedFile(ScreenshotHandle hScreenshot, PublishedFileId_t unPublishedFileId) override;
    bool IsScreenshotsHooked() override;
    ScreenshotHandle AddVRScreenshotToLibrary(EVRScreenshotType eType, const char* pchFilename, const char* pchVRFilename) override;
private:
    StarSteamScreenshots() = default;
};
