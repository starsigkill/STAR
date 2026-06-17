#include "steam/steam_game_server_stats.h"
#include "core/callbacks.h"
#include "steam/isteamgameserverstats.h"

StarSteamGameServerStats& StarSteamGameServerStats::get() { static StarSteamGameServerStats i; return i; }
SteamAPICall_t StarSteamGameServerStats::RequestUserStats(CSteamID s) { GSStatsReceived_t r{}; r.m_eResult=k_EResultOK; r.m_steamIDUser=s; return STAR_PostCallResult(GSStatsReceived_t::k_iCallback, &r, sizeof(r)); }
bool StarSteamGameServerStats::GetUserStat(CSteamID s, const char* n, int32* d) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(n); if(d) *d=0; return false; }
bool StarSteamGameServerStats::GetUserStat(CSteamID s, const char* n, float* d) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(n); if(d) *d=0.0f; return false; }
bool StarSteamGameServerStats::GetUserAchievement(CSteamID s, const char* n, bool* a) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(n); if(a) *a=false; return false; }
bool StarSteamGameServerStats::SetUserStat(CSteamID s, const char* n, int32 d) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(n); STAR_UNREFERENCED(d); return false; }
bool StarSteamGameServerStats::SetUserStat(CSteamID s, const char* n, float d) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(n); STAR_UNREFERENCED(d); return false; }
bool StarSteamGameServerStats::UpdateUserAvgRateStat(CSteamID s, const char* n, float c, double l) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(n); STAR_UNREFERENCED(c); STAR_UNREFERENCED(l); return false; }
bool StarSteamGameServerStats::SetUserAchievement(CSteamID s, const char* n) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(n); return false; }
bool StarSteamGameServerStats::ClearUserAchievement(CSteamID s, const char* n) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(n); return false; }
SteamAPICall_t StarSteamGameServerStats::StoreUserStats(CSteamID s) { GSStatsStored_t r{}; r.m_eResult=k_EResultOK; r.m_steamIDUser=s; return STAR_PostCallResult(GSStatsStored_t::k_iCallback, &r, sizeof(r)); }
