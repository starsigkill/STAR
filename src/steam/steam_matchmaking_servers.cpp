#include "steam/steam_matchmaking_servers.h"

StarSteamMatchmakingServers& StarSteamMatchmakingServers::get() { static StarSteamMatchmakingServers i; return i; }
HServerListRequest StarSteamMatchmakingServers::RequestInternetServerList(AppId_t a, MatchMakingKeyValuePair_t** f, uint32 n, ISteamMatchmakingServerListResponse* r) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(f); STAR_UNREFERENCED(n); STAR_UNREFERENCED(r); return nullptr; }
HServerListRequest StarSteamMatchmakingServers::RequestLANServerList(AppId_t a, ISteamMatchmakingServerListResponse* r) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(r); return nullptr; }
HServerListRequest StarSteamMatchmakingServers::RequestFriendsServerList(AppId_t a, MatchMakingKeyValuePair_t** f, uint32 n, ISteamMatchmakingServerListResponse* r) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(f); STAR_UNREFERENCED(n); STAR_UNREFERENCED(r); return nullptr; }
HServerListRequest StarSteamMatchmakingServers::RequestFavoritesServerList(AppId_t a, MatchMakingKeyValuePair_t** f, uint32 n, ISteamMatchmakingServerListResponse* r) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(f); STAR_UNREFERENCED(n); STAR_UNREFERENCED(r); return nullptr; }
HServerListRequest StarSteamMatchmakingServers::RequestHistoryServerList(AppId_t a, MatchMakingKeyValuePair_t** f, uint32 n, ISteamMatchmakingServerListResponse* r) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(f); STAR_UNREFERENCED(n); STAR_UNREFERENCED(r); return nullptr; }
HServerListRequest StarSteamMatchmakingServers::RequestSpectatorServerList(AppId_t a, MatchMakingKeyValuePair_t** f, uint32 n, ISteamMatchmakingServerListResponse* r) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(f); STAR_UNREFERENCED(n); STAR_UNREFERENCED(r); return nullptr; }
void StarSteamMatchmakingServers::ReleaseRequest(HServerListRequest h) { STAR_UNREFERENCED(h); }
gameserveritem_t* StarSteamMatchmakingServers::GetServerDetails(HServerListRequest h, int i) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); return nullptr; }
void StarSteamMatchmakingServers::CancelQuery(HServerListRequest h) { STAR_UNREFERENCED(h); }
void StarSteamMatchmakingServers::RefreshQuery(HServerListRequest h) { STAR_UNREFERENCED(h); }
bool StarSteamMatchmakingServers::IsRefreshing(HServerListRequest h) { STAR_UNREFERENCED(h); return false; }
int StarSteamMatchmakingServers::GetServerCount(HServerListRequest h) { STAR_UNREFERENCED(h); return 0; }
void StarSteamMatchmakingServers::RefreshServer(HServerListRequest h, int i) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); }
HServerQuery StarSteamMatchmakingServers::PingServer(uint32 ip, uint16 port, ISteamMatchmakingPingResponse* r) { STAR_UNREFERENCED(ip); STAR_UNREFERENCED(port); STAR_UNREFERENCED(r); return HSERVERQUERY_INVALID; }
HServerQuery StarSteamMatchmakingServers::PlayerDetails(uint32 ip, uint16 port, ISteamMatchmakingPlayersResponse* r) { STAR_UNREFERENCED(ip); STAR_UNREFERENCED(port); STAR_UNREFERENCED(r); return HSERVERQUERY_INVALID; }
HServerQuery StarSteamMatchmakingServers::ServerRules(uint32 ip, uint16 port, ISteamMatchmakingRulesResponse* r) { STAR_UNREFERENCED(ip); STAR_UNREFERENCED(port); STAR_UNREFERENCED(r); return HSERVERQUERY_INVALID; }
void StarSteamMatchmakingServers::CancelServerQuery(HServerQuery h) { STAR_UNREFERENCED(h); }
