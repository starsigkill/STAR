#include "steam/steam_matchmaking.h"
#include "core/callbacks.h"
#include "steam/isteammatchmaking.h"

StarSteamMatchmaking& StarSteamMatchmaking::get() { static StarSteamMatchmaking i; return i; }
CSteamID StarSteamMatchmaking::GetLobbyByIndex(int iLobby) { STAR_UNREFERENCED(iLobby); return k_steamIDNil; }
int StarSteamMatchmaking::GetFavoriteGameCount() { return 0; }
bool StarSteamMatchmaking::GetFavoriteGame(int iGame, AppId_t* pnAppID, uint32* pnIP, uint16* pnConnPort, uint16* pnQueryPort, uint32* punFlags, uint32* pRTime32LastPlayedOnServer) { STAR_UNREFERENCED(iGame); STAR_UNREFERENCED(pnAppID); STAR_UNREFERENCED(pnIP); STAR_UNREFERENCED(pnConnPort); STAR_UNREFERENCED(pnQueryPort); STAR_UNREFERENCED(punFlags); STAR_UNREFERENCED(pRTime32LastPlayedOnServer); return false; }
int StarSteamMatchmaking::AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer) { STAR_UNREFERENCED(nAppID); STAR_UNREFERENCED(nIP); STAR_UNREFERENCED(nConnPort); STAR_UNREFERENCED(nQueryPort); STAR_UNREFERENCED(unFlags); STAR_UNREFERENCED(rTime32LastPlayedOnServer); return 0; }
bool StarSteamMatchmaking::RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags) { STAR_UNREFERENCED(nAppID); STAR_UNREFERENCED(nIP); STAR_UNREFERENCED(nConnPort); STAR_UNREFERENCED(nQueryPort); STAR_UNREFERENCED(unFlags); return false; }
SteamAPICall_t StarSteamMatchmaking::RequestLobbyList() { LobbyMatchList_t r{}; r.m_nLobbiesMatching=0; return STAR_PostCallResult(LobbyMatchList_t::k_iCallback, &r, sizeof(r)); }
void StarSteamMatchmaking::AddRequestLobbyListStringFilter(const char* k, const char* v, ELobbyComparison c) { STAR_UNREFERENCED(k); STAR_UNREFERENCED(v); STAR_UNREFERENCED(c); }
void StarSteamMatchmaking::AddRequestLobbyListNumericalFilter(const char* k, int v, ELobbyComparison c) { STAR_UNREFERENCED(k); STAR_UNREFERENCED(v); STAR_UNREFERENCED(c); }
void StarSteamMatchmaking::AddRequestLobbyListNearValueFilter(const char* k, int v) { STAR_UNREFERENCED(k); STAR_UNREFERENCED(v); }
void StarSteamMatchmaking::AddRequestLobbyListFilterSlotsAvailable(int n) { STAR_UNREFERENCED(n); }
void StarSteamMatchmaking::AddRequestLobbyListDistanceFilter(ELobbyDistanceFilter f) { STAR_UNREFERENCED(f); }
void StarSteamMatchmaking::AddRequestLobbyListResultCountFilter(int c) { STAR_UNREFERENCED(c); }
void StarSteamMatchmaking::AddRequestLobbyListCompatibleMembersFilter(CSteamID s) { STAR_UNREFERENCED(s); }
SteamAPICall_t StarSteamMatchmaking::CreateLobby(ELobbyType eLobbyType, int cMaxMembers) { STAR_UNREFERENCED(eLobbyType); STAR_UNREFERENCED(cMaxMembers); LobbyCreated_t r{}; r.m_eResult=k_EResultOK; r.m_ulSteamIDLobby=0; return STAR_PostCallResult(LobbyCreated_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamMatchmaking::JoinLobby(CSteamID steamIDLobby) { STAR_UNREFERENCED(steamIDLobby); LobbyEnter_t r{}; r.m_ulSteamIDLobby=0; r.m_rgfChatPermissions=0; r.m_bLocked=false; r.m_EChatRoomEnterResponse=k_EChatRoomEnterResponseDoesntExist; return STAR_PostCallResult(LobbyEnter_t::k_iCallback, &r, sizeof(r)); }
void StarSteamMatchmaking::LeaveLobby(CSteamID s) { STAR_UNREFERENCED(s); }
bool StarSteamMatchmaking::InviteUserToLobby(CSteamID l, CSteamID u) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(u); return false; }
int StarSteamMatchmaking::GetNumLobbyMembers(CSteamID s) { STAR_UNREFERENCED(s); return 0; }
CSteamID StarSteamMatchmaking::GetLobbyMemberByIndex(CSteamID l, int i) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(i); return k_steamIDNil; }
const char* StarSteamMatchmaking::GetLobbyData(CSteamID l, const char* k) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(k); return ""; }
bool StarSteamMatchmaking::SetLobbyData(CSteamID l, const char* k, const char* v) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(k); STAR_UNREFERENCED(v); return false; }
int StarSteamMatchmaking::GetLobbyDataCount(CSteamID l) { STAR_UNREFERENCED(l); return 0; }
bool StarSteamMatchmaking::GetLobbyDataByIndex(CSteamID l, int i, char* k, int klen, char* v, int vlen) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(i); STAR_UNREFERENCED(k); STAR_UNREFERENCED(klen); STAR_UNREFERENCED(v); STAR_UNREFERENCED(vlen); return false; }
bool StarSteamMatchmaking::DeleteLobbyData(CSteamID l, const char* k) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(k); return false; }
const char* StarSteamMatchmaking::GetLobbyMemberData(CSteamID l, CSteamID u, const char* k) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(u); STAR_UNREFERENCED(k); return ""; }
void StarSteamMatchmaking::SetLobbyMemberData(CSteamID l, const char* k, const char* v) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(k); STAR_UNREFERENCED(v); }
bool StarSteamMatchmaking::SendLobbyChatMsg(CSteamID l, const void* m, int s) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(m); STAR_UNREFERENCED(s); return false; }
int StarSteamMatchmaking::GetLobbyChatEntry(CSteamID l, int i, CSteamID* u, void* d, int s, EChatEntryType* e) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(i); STAR_UNREFERENCED(u); STAR_UNREFERENCED(d); STAR_UNREFERENCED(s); if(e) *e=k_EChatEntryTypeInvalid; return 0; }
bool StarSteamMatchmaking::RequestLobbyData(CSteamID l) { STAR_UNREFERENCED(l); return false; }
void StarSteamMatchmaking::SetLobbyGameServer(CSteamID l, uint32 ip, uint16 port, CSteamID gs) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(ip); STAR_UNREFERENCED(port); STAR_UNREFERENCED(gs); }
bool StarSteamMatchmaking::GetLobbyGameServer(CSteamID l, uint32* ip, uint16* port, CSteamID* gs) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(ip); STAR_UNREFERENCED(port); STAR_UNREFERENCED(gs); return false; }
bool StarSteamMatchmaking::SetLobbyMemberLimit(CSteamID l, int m) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(m); return false; }
int StarSteamMatchmaking::GetLobbyMemberLimit(CSteamID l) { STAR_UNREFERENCED(l); return 0; }
bool StarSteamMatchmaking::SetLobbyType(CSteamID l, ELobbyType t) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(t); return false; }
bool StarSteamMatchmaking::SetLobbyJoinable(CSteamID l, bool j) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(j); return false; }
CSteamID StarSteamMatchmaking::GetLobbyOwner(CSteamID l) { STAR_UNREFERENCED(l); return k_steamIDNil; }
bool StarSteamMatchmaking::SetLobbyOwner(CSteamID l, CSteamID o) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(o); return false; }
bool StarSteamMatchmaking::SetLinkedLobby(CSteamID l, CSteamID d) { STAR_UNREFERENCED(l); STAR_UNREFERENCED(d); return false; }
