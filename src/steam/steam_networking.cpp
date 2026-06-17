#include "steam/steam_networking.h"

StarSteamNetworking& StarSteamNetworking::get() { static StarSteamNetworking i; return i; }
bool StarSteamNetworking::SendP2PPacket(CSteamID s, const void* d, uint32 c, EP2PSend t, int ch) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(d); STAR_UNREFERENCED(c); STAR_UNREFERENCED(t); STAR_UNREFERENCED(ch); return false; }
bool StarSteamNetworking::IsP2PPacketAvailable(uint32* p, int ch) { STAR_UNREFERENCED(ch); if(p) *p=0; return false; }
bool StarSteamNetworking::ReadP2PPacket(void* d, uint32 c, uint32* s, CSteamID* r, int ch) { STAR_UNREFERENCED(d); STAR_UNREFERENCED(c); STAR_UNREFERENCED(ch); if(s) *s=0; if(r) *r=k_steamIDNil; return false; }
bool StarSteamNetworking::AcceptP2PSessionWithUser(CSteamID s) { STAR_UNREFERENCED(s); return false; }
bool StarSteamNetworking::CloseP2PSessionWithUser(CSteamID s) { STAR_UNREFERENCED(s); return false; }
bool StarSteamNetworking::CloseP2PChannelWithUser(CSteamID s, int ch) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(ch); return false; }
bool StarSteamNetworking::GetP2PSessionState(CSteamID s, P2PSessionState_t* p) { STAR_UNREFERENCED(s); if(p) memset(p,0,sizeof(*p)); return false; }
bool StarSteamNetworking::AllowP2PPacketRelay(bool b) { STAR_UNREFERENCED(b); return false; }
SNetListenSocket_t StarSteamNetworking::CreateListenSocket(int v, SteamIPAddress_t ip, uint16 port, bool b) { STAR_UNREFERENCED(v); STAR_UNREFERENCED(ip); STAR_UNREFERENCED(port); STAR_UNREFERENCED(b); return 0; }
SNetSocket_t StarSteamNetworking::CreateP2PConnectionSocket(CSteamID s, int v, int t, bool b) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(v); STAR_UNREFERENCED(t); STAR_UNREFERENCED(b); return 0; }
SNetSocket_t StarSteamNetworking::CreateConnectionSocket(SteamIPAddress_t ip, uint16 port, int t) { STAR_UNREFERENCED(ip); STAR_UNREFERENCED(port); STAR_UNREFERENCED(t); return 0; }
bool StarSteamNetworking::DestroySocket(SNetSocket_t h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); return false; }
bool StarSteamNetworking::DestroyListenSocket(SNetListenSocket_t h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); return false; }
bool StarSteamNetworking::SendDataOnSocket(SNetSocket_t h, void* d, uint32 c, bool r) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(d); STAR_UNREFERENCED(c); STAR_UNREFERENCED(r); return false; }
bool StarSteamNetworking::IsDataAvailableOnSocket(SNetSocket_t h, uint32* s) { STAR_UNREFERENCED(h); if(s) *s=0; return false; }
bool StarSteamNetworking::RetrieveDataFromSocket(SNetSocket_t h, void* d, uint32 c, uint32* s) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(d); STAR_UNREFERENCED(c); if(s) *s=0; return false; }
bool StarSteamNetworking::IsDataAvailable(SNetListenSocket_t h, uint32* s, SNetSocket_t* p) { STAR_UNREFERENCED(h); if(s) *s=0; if(p) *p=0; return false; }
bool StarSteamNetworking::RetrieveData(SNetListenSocket_t h, void* d, uint32 c, uint32* s, SNetSocket_t* p) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(d); STAR_UNREFERENCED(c); if(s) *s=0; if(p) *p=0; return false; }
bool StarSteamNetworking::GetSocketInfo(SNetSocket_t h, CSteamID* r, int* st, SteamIPAddress_t* ip, uint16* port) { STAR_UNREFERENCED(h); if(r) *r=k_steamIDNil; if(st) *st=0; if(ip) memset(ip,0,sizeof(*ip)); if(port) *port=0; return false; }
bool StarSteamNetworking::GetListenSocketInfo(SNetListenSocket_t h, SteamIPAddress_t* ip, uint16* port) { STAR_UNREFERENCED(h); if(ip) memset(ip,0,sizeof(*ip)); if(port) *port=0; return false; }
ESNetSocketConnectionType StarSteamNetworking::GetSocketConnectionType(SNetSocket_t h) { STAR_UNREFERENCED(h); return k_ESNetSocketConnectionTypeNotConnected; }
int StarSteamNetworking::GetMaxPacketSize(SNetSocket_t h) { STAR_UNREFERENCED(h); return 0; }
