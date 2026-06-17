#include "steam/steam_screenshots.h"
StarSteamScreenshots& StarSteamScreenshots::get() { static StarSteamScreenshots i; return i; }
ScreenshotHandle StarSteamScreenshots::WriteScreenshot(void* p, uint32 c, int w, int h) { STAR_UNREFERENCED(p); STAR_UNREFERENCED(c); STAR_UNREFERENCED(w); STAR_UNREFERENCED(h); return INVALID_SCREENSHOT_HANDLE; }
ScreenshotHandle StarSteamScreenshots::AddScreenshotToLibrary(const char* f, const char* t, int w, int h) { STAR_UNREFERENCED(f); STAR_UNREFERENCED(t); STAR_UNREFERENCED(w); STAR_UNREFERENCED(h); return INVALID_SCREENSHOT_HANDLE; }
void StarSteamScreenshots::TriggerScreenshot() {}
void StarSteamScreenshots::HookScreenshots(bool b) { STAR_UNREFERENCED(b); }
bool StarSteamScreenshots::SetLocation(ScreenshotHandle h, const char* l) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(l); return false; }
bool StarSteamScreenshots::TagUser(ScreenshotHandle h, CSteamID s) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(s); return false; }
bool StarSteamScreenshots::TagPublishedFile(ScreenshotHandle h, PublishedFileId_t f) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(f); return false; }
bool StarSteamScreenshots::IsScreenshotsHooked() { return false; }
ScreenshotHandle StarSteamScreenshots::AddVRScreenshotToLibrary(EVRScreenshotType e, const char* f, const char* v) { STAR_UNREFERENCED(e); STAR_UNREFERENCED(f); STAR_UNREFERENCED(v); return INVALID_SCREENSHOT_HANDLE; }
