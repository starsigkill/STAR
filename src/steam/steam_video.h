#pragma once
#include "core/star_common.h"
#include "steam/isteamvideo.h"

class StarSteamVideo : public ISteamVideo {
public:
    static StarSteamVideo& get();
    void GetVideoURL(AppId_t unVideoAppID) override;
    bool IsBroadcasting(int* pnNumViewers) override;
    void GetOPFSettings(AppId_t unVideoAppID) override;
    bool GetOPFStringForApp(AppId_t unVideoAppID, char* pchBuffer, int32* pnBufferSize) override;
private:
    StarSteamVideo() = default;
};
