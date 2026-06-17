#include "steam/steam_music.h"
StarSteamMusic& StarSteamMusic::get() { static StarSteamMusic i; return i; }
bool StarSteamMusic::BIsEnabled() { return false; }
bool StarSteamMusic::BIsPlaying() { return false; }
AudioPlayback_Status StarSteamMusic::GetPlaybackStatus() { return AudioPlayback_Undefined; }
void StarSteamMusic::Play() {}
void StarSteamMusic::Pause() {}
void StarSteamMusic::PlayPrevious() {}
void StarSteamMusic::PlayNext() {}
void StarSteamMusic::SetVolume(float f) { STAR_UNREFERENCED(f); }
float StarSteamMusic::GetVolume() { return 0.0f; }
