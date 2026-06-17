#include "steam/steam_unified_messages.h"
StarSteamUnifiedMessages& StarSteamUnifiedMessages::get() { static StarSteamUnifiedMessages i; return i; }
ClientUnifiedMessageHandle StarSteamUnifiedMessages::SendMethod(const char* m, const void* b, uint32 s, uint64 c) { STAR_UNREFERENCED(m); STAR_UNREFERENCED(b); STAR_UNREFERENCED(s); STAR_UNREFERENCED(c); return k_InvalidUnifiedMessageHandle; }
bool StarSteamUnifiedMessages::GetMethodResponseInfo(ClientUnifiedMessageHandle h, uint32* s, EResult* r) { STAR_UNREFERENCED(h); if(s) *s=0; if(r) *r=k_EResultFail; return false; }
bool StarSteamUnifiedMessages::GetMethodResponseData(ClientUnifiedMessageHandle h, void* b, uint32 s, bool a) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); STAR_UNREFERENCED(s); STAR_UNREFERENCED(a); return false; }
bool StarSteamUnifiedMessages::ReleaseMethod(ClientUnifiedMessageHandle h) { STAR_UNREFERENCED(h); return false; }
bool StarSteamUnifiedMessages::SendNotification(const char* n, const void* b, uint32 s) { STAR_UNREFERENCED(n); STAR_UNREFERENCED(b); STAR_UNREFERENCED(s); return false; }
