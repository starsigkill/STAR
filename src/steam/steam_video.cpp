#include "steam/steam_video.h"
#include "core/callbacks.h"
#include "steam/isteamvideo.h"

StarSteamVideo& StarSteamVideo::get() { static StarSteamVideo i; return i; }
void StarSteamVideo::GetVideoURL(AppId_t a)
{
    GetVideoURLResult_t r{};
    r.m_eResult = k_EResultFail;
    r.m_unVideoAppID = a;
    STAR_DispatchCallback(GetVideoURLResult_t::k_iCallback, &r, sizeof(r));
}
bool StarSteamVideo::IsBroadcasting(int* n) { if(n) *n=0; return false; }
void StarSteamVideo::GetOPFSettings(AppId_t a)
{
    GetOPFSettingsResult_t r{};
    r.m_eResult = k_EResultFail;
    r.m_unVideoAppID = a;
    STAR_DispatchCallback(GetOPFSettingsResult_t::k_iCallback, &r, sizeof(r));
}
bool StarSteamVideo::GetOPFStringForApp(AppId_t a, char* b, int32* s) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(b); if(s) *s=0; return false; }
