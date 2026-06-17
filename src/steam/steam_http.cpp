#include "steam/steam_http.h"
StarSteamHTTP& StarSteamHTTP::get() { static StarSteamHTTP i; return i; }
HTTPRequestHandle StarSteamHTTP::CreateHTTPRequest(EHTTPMethod m, const char* u) { STAR_UNREFERENCED(m); STAR_UNREFERENCED(u); return INVALID_HTTPREQUEST_HANDLE; }
bool StarSteamHTTP::SetHTTPRequestContextValue(HTTPRequestHandle h, uint64 v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(v); return false; }
bool StarSteamHTTP::SetHTTPRequestNetworkActivityTimeout(HTTPRequestHandle h, uint32 t) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(t); return false; }
bool StarSteamHTTP::SetHTTPRequestHeaderValue(HTTPRequestHandle h, const char* n, const char* v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(n); STAR_UNREFERENCED(v); return false; }
bool StarSteamHTTP::SetHTTPRequestGetOrPostParameter(HTTPRequestHandle h, const char* n, const char* v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(n); STAR_UNREFERENCED(v); return false; }
bool StarSteamHTTP::SendHTTPRequest(HTTPRequestHandle h, SteamAPICall_t* c) { STAR_UNREFERENCED(h); if(c) *c=k_uAPICallInvalid; return false; }
bool StarSteamHTTP::SendHTTPRequestAndStreamResponse(HTTPRequestHandle h, SteamAPICall_t* c) { STAR_UNREFERENCED(h); if(c) *c=k_uAPICallInvalid; return false; }
bool StarSteamHTTP::DeferHTTPRequest(HTTPRequestHandle h) { STAR_UNREFERENCED(h); return false; }
bool StarSteamHTTP::PrioritizeHTTPRequest(HTTPRequestHandle h) { STAR_UNREFERENCED(h); return false; }
bool StarSteamHTTP::GetHTTPResponseHeaderSize(HTTPRequestHandle h, const char* n, uint32* s) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(n); if(s) *s=0; return false; }
bool StarSteamHTTP::GetHTTPResponseHeaderValue(HTTPRequestHandle h, const char* n, uint8* b, uint32 s) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(n); STAR_UNREFERENCED(b); STAR_UNREFERENCED(s); return false; }
bool StarSteamHTTP::GetHTTPResponseBodySize(HTTPRequestHandle h, uint32* s) { STAR_UNREFERENCED(h); if(s) *s=0; return false; }
bool StarSteamHTTP::GetHTTPResponseBodyData(HTTPRequestHandle h, uint8* b, uint32 s) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); STAR_UNREFERENCED(s); return false; }
bool StarSteamHTTP::GetHTTPStreamingResponseBodyData(HTTPRequestHandle h, uint32 o, uint8* b, uint32 s) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(o); STAR_UNREFERENCED(b); STAR_UNREFERENCED(s); return false; }
bool StarSteamHTTP::ReleaseHTTPRequest(HTTPRequestHandle h) { STAR_UNREFERENCED(h); return false; }
bool StarSteamHTTP::GetHTTPDownloadProgressPct(HTTPRequestHandle h, float* p) { STAR_UNREFERENCED(h); if(p) *p=0.0f; return false; }
bool StarSteamHTTP::SetHTTPRequestRawPostBody(HTTPRequestHandle h, const char* ct, uint8* b, uint32 l) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(ct); STAR_UNREFERENCED(b); STAR_UNREFERENCED(l); return false; }
HTTPCookieContainerHandle StarSteamHTTP::CreateCookieContainer(bool b) { STAR_UNREFERENCED(b); return INVALID_HTTPCOOKIE_HANDLE; }
bool StarSteamHTTP::ReleaseCookieContainer(HTTPCookieContainerHandle h) { STAR_UNREFERENCED(h); return false; }
bool StarSteamHTTP::SetCookie(HTTPCookieContainerHandle h, const char* host, const char* url, const char* c) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(host); STAR_UNREFERENCED(url); STAR_UNREFERENCED(c); return false; }
bool StarSteamHTTP::SetHTTPRequestCookieContainer(HTTPRequestHandle h, HTTPCookieContainerHandle c) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(c); return false; }
bool StarSteamHTTP::SetHTTPRequestUserAgentInfo(HTTPRequestHandle h, const char* i) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); return false; }
bool StarSteamHTTP::SetHTTPRequestRequiresVerifiedCertificate(HTTPRequestHandle h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); return false; }
bool StarSteamHTTP::SetHTTPRequestAbsoluteTimeoutMS(HTTPRequestHandle h, uint32 ms) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(ms); return false; }
bool StarSteamHTTP::GetHTTPRequestWasTimedOut(HTTPRequestHandle h, bool* t) { STAR_UNREFERENCED(h); if(t) *t=false; return false; }
