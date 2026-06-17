#include "steam/steam_game_server.h"
#include "core/callbacks.h"
#include "core/settings.h"

StarSteamGameServer& StarSteamGameServer::get() { static StarSteamGameServer i; return i; }
bool StarSteamGameServer::InitGameServer(uint32 ip, uint16 gp, uint16 qp, uint32 flags, AppId_t app, const char* ver) { STAR_UNREFERENCED(ip); STAR_UNREFERENCED(gp); STAR_UNREFERENCED(qp); STAR_UNREFERENCED(flags); STAR_UNREFERENCED(app); STAR_UNREFERENCED(ver); return true; }
void StarSteamGameServer::SetProduct(const char* p) { STAR_UNREFERENCED(p); }
void StarSteamGameServer::SetGameDescription(const char* p) { STAR_UNREFERENCED(p); }
void StarSteamGameServer::SetModDir(const char* p) { STAR_UNREFERENCED(p); }
void StarSteamGameServer::SetDedicatedServer(bool b) { STAR_UNREFERENCED(b); }
void StarSteamGameServer::LogOn(const char* t) { STAR_UNREFERENCED(t); }
void StarSteamGameServer::LogOnAnonymous() {}
void StarSteamGameServer::LogOff() {}
bool StarSteamGameServer::BLoggedOn() { return false; }
bool StarSteamGameServer::BSecure() { return false; }
CSteamID StarSteamGameServer::GetSteamID() { return CSteamID(Settings::get().steam_id); }
bool StarSteamGameServer::WasRestartRequested() { return false; }
void StarSteamGameServer::SetMaxPlayerCount(int c) { STAR_UNREFERENCED(c); }
void StarSteamGameServer::SetBotPlayerCount(int c) { STAR_UNREFERENCED(c); }
void StarSteamGameServer::SetServerName(const char* n) { STAR_UNREFERENCED(n); }
void StarSteamGameServer::SetMapName(const char* n) { STAR_UNREFERENCED(n); }
void StarSteamGameServer::SetPasswordProtected(bool b) { STAR_UNREFERENCED(b); }
void StarSteamGameServer::SetSpectatorPort(uint16 p) { STAR_UNREFERENCED(p); }
void StarSteamGameServer::SetSpectatorServerName(const char* n) { STAR_UNREFERENCED(n); }
void StarSteamGameServer::ClearAllKeyValues() {}
void StarSteamGameServer::SetKeyValue(const char* k, const char* v) { STAR_UNREFERENCED(k); STAR_UNREFERENCED(v); }
void StarSteamGameServer::SetGameTags(const char* t) { STAR_UNREFERENCED(t); }
void StarSteamGameServer::SetGameData(const char* d) { STAR_UNREFERENCED(d); }
void StarSteamGameServer::SetRegion(const char* r) { STAR_UNREFERENCED(r); }
void StarSteamGameServer::SetAdvertiseServerActive(bool b) { STAR_UNREFERENCED(b); }
bool StarSteamGameServer::SendUserConnectAndAuthenticate(uint32 ip, const void* b, uint32 s, CSteamID* id) { STAR_UNREFERENCED(ip); STAR_UNREFERENCED(b); STAR_UNREFERENCED(s); if(id) *id=k_steamIDNil; return false; }
CSteamID StarSteamGameServer::CreateUnauthenticatedUserConnection() { return k_steamIDNil; }
void StarSteamGameServer::SendUserDisconnect(CSteamID s) { STAR_UNREFERENCED(s); }
bool StarSteamGameServer::BUpdateUserData(CSteamID s, const char* n, uint32 sc) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(n); STAR_UNREFERENCED(sc); return false; }
HAuthTicket StarSteamGameServer::GetAuthSessionTicket(void* t, int m, uint32* c, const SteamNetworkingIdentity* snid) { STAR_UNREFERENCED(t); STAR_UNREFERENCED(m); STAR_UNREFERENCED(snid); if(c) *c=0; return k_HAuthTicketInvalid; }
EBeginAuthSessionResult StarSteamGameServer::BeginAuthSession(const void* t, int s, CSteamID id) { STAR_UNREFERENCED(t); STAR_UNREFERENCED(s); STAR_UNREFERENCED(id); return k_EBeginAuthSessionResultOK; }
void StarSteamGameServer::EndAuthSession(CSteamID s) { STAR_UNREFERENCED(s); }
void StarSteamGameServer::CancelAuthTicket(HAuthTicket h) { STAR_UNREFERENCED(h); }
EUserHasLicenseForAppResult StarSteamGameServer::UserHasLicenseForApp(CSteamID s, AppId_t a) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(a); return k_EUserHasLicenseResultHasLicense; }
bool StarSteamGameServer::RequestUserGroupStatus(CSteamID u, CSteamID g) { STAR_UNREFERENCED(u); STAR_UNREFERENCED(g); return false; }
void StarSteamGameServer::GetGameplayStats() {}
SteamAPICall_t StarSteamGameServer::GetServerReputation() { return k_uAPICallInvalid; }
SteamIPAddress_t StarSteamGameServer::GetPublicIP() { SteamIPAddress_t r{}; return r; }
bool StarSteamGameServer::HandleIncomingPacket(const void* d, int s, uint32 ip, uint16 port) { STAR_UNREFERENCED(d); STAR_UNREFERENCED(s); STAR_UNREFERENCED(ip); STAR_UNREFERENCED(port); return false; }
int StarSteamGameServer::GetNextOutgoingPacket(void* o, int m, uint32* a, uint16* p) { STAR_UNREFERENCED(o); STAR_UNREFERENCED(m); STAR_UNREFERENCED(a); STAR_UNREFERENCED(p); return 0; }
SteamAPICall_t StarSteamGameServer::AssociateWithClan(CSteamID c) { STAR_UNREFERENCED(c); return k_uAPICallInvalid; }
SteamAPICall_t StarSteamGameServer::ComputeNewPlayerCompatibility(CSteamID p) { STAR_UNREFERENCED(p); return k_uAPICallInvalid; }
void StarSteamGameServer::SetMasterServerHeartbeatInterval_DEPRECATED(int i) { STAR_UNREFERENCED(i); }
void StarSteamGameServer::ForceMasterServerHeartbeat_DEPRECATED() {}
