#include "steam/steam_html_surface.h"
#include "core/callbacks.h"
#include "steam/isteamhtmlsurface.h"

StarSteamHTMLSurface& StarSteamHTMLSurface::get() { static StarSteamHTMLSurface i; return i; }
bool StarSteamHTMLSurface::Init() { return true; }
bool StarSteamHTMLSurface::Shutdown() { return true; }
SteamAPICall_t StarSteamHTMLSurface::CreateBrowser(const char* u, const char* c) { STAR_UNREFERENCED(u); STAR_UNREFERENCED(c); HTML_BrowserReady_t r{}; r.unBrowserHandle=INVALID_HTMLBROWSER; return STAR_PostCallResult(HTML_BrowserReady_t::k_iCallback, &r, sizeof(r)); }
void StarSteamHTMLSurface::RemoveBrowser(HHTMLBrowser h) { STAR_UNREFERENCED(h); }
void StarSteamHTMLSurface::LoadURL(HHTMLBrowser h, const char* u, const char* p) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(u); STAR_UNREFERENCED(p); }
void StarSteamHTMLSurface::SetSize(HHTMLBrowser h, uint32 w, uint32 ht) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(w); STAR_UNREFERENCED(ht); }
void StarSteamHTMLSurface::StopLoad(HHTMLBrowser h) { STAR_UNREFERENCED(h); }
void StarSteamHTMLSurface::Reload(HHTMLBrowser h) { STAR_UNREFERENCED(h); }
void StarSteamHTMLSurface::GoBack(HHTMLBrowser h) { STAR_UNREFERENCED(h); }
void StarSteamHTMLSurface::GoForward(HHTMLBrowser h) { STAR_UNREFERENCED(h); }
void StarSteamHTMLSurface::AddHeader(HHTMLBrowser h, const char* k, const char* v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(k); STAR_UNREFERENCED(v); }
void StarSteamHTMLSurface::ExecuteJavascript(HHTMLBrowser h, const char* s) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(s); }
void StarSteamHTMLSurface::MouseUp(HHTMLBrowser h, EHTMLMouseButton b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); }
void StarSteamHTMLSurface::MouseDown(HHTMLBrowser h, EHTMLMouseButton b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); }
void StarSteamHTMLSurface::MouseDoubleClick(HHTMLBrowser h, EHTMLMouseButton b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); }
void StarSteamHTMLSurface::MouseMove(HHTMLBrowser h, int x, int y) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(x); STAR_UNREFERENCED(y); }
void StarSteamHTMLSurface::MouseWheel(HHTMLBrowser h, int32 d) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(d); }
void StarSteamHTMLSurface::KeyDown(HHTMLBrowser h, uint32 k, EHTMLKeyModifiers m, bool s) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(k); STAR_UNREFERENCED(m); STAR_UNREFERENCED(s); }
void StarSteamHTMLSurface::KeyUp(HHTMLBrowser h, uint32 k, EHTMLKeyModifiers m) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(k); STAR_UNREFERENCED(m); }
void StarSteamHTMLSurface::KeyChar(HHTMLBrowser h, uint32 c, EHTMLKeyModifiers m) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(c); STAR_UNREFERENCED(m); }
void StarSteamHTMLSurface::SetHorizontalScroll(HHTMLBrowser h, uint32 s) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(s); }
void StarSteamHTMLSurface::SetVerticalScroll(HHTMLBrowser h, uint32 s) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(s); }
void StarSteamHTMLSurface::SetKeyFocus(HHTMLBrowser h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); }
void StarSteamHTMLSurface::ViewSource(HHTMLBrowser h) { STAR_UNREFERENCED(h); }
void StarSteamHTMLSurface::CopyToClipboard(HHTMLBrowser h) { STAR_UNREFERENCED(h); }
void StarSteamHTMLSurface::PasteFromClipboard(HHTMLBrowser h) { STAR_UNREFERENCED(h); }
void StarSteamHTMLSurface::Find(HHTMLBrowser h, const char* s, bool c, bool r) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(s); STAR_UNREFERENCED(c); STAR_UNREFERENCED(r); }
void StarSteamHTMLSurface::StopFind(HHTMLBrowser h) { STAR_UNREFERENCED(h); }
void StarSteamHTMLSurface::GetLinkAtPosition(HHTMLBrowser h, int x, int y) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(x); STAR_UNREFERENCED(y); }
void StarSteamHTMLSurface::SetCookie(const char* host, const char* k, const char* v, const char* p, RTime32 e, bool s, bool http) { STAR_UNREFERENCED(host); STAR_UNREFERENCED(k); STAR_UNREFERENCED(v); STAR_UNREFERENCED(p); STAR_UNREFERENCED(e); STAR_UNREFERENCED(s); STAR_UNREFERENCED(http); }
void StarSteamHTMLSurface::SetPageScaleFactor(HHTMLBrowser h, float z, int x, int y) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(z); STAR_UNREFERENCED(x); STAR_UNREFERENCED(y); }
void StarSteamHTMLSurface::SetBackgroundMode(HHTMLBrowser h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); }
void StarSteamHTMLSurface::SetDPIScalingFactor(HHTMLBrowser h, float f) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(f); }
void StarSteamHTMLSurface::OpenDeveloperTools(HHTMLBrowser h) { STAR_UNREFERENCED(h); }
void StarSteamHTMLSurface::AllowStartRequest(HHTMLBrowser h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); }
void StarSteamHTMLSurface::JSDialogResponse(HHTMLBrowser h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); }
void StarSteamHTMLSurface::FileLoadDialogResponse(HHTMLBrowser h, const char** f) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(f); }
