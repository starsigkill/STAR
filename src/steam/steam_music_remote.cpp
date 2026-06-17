#include "steam/steam_music_remote.h"
StarSteamMusicRemote& StarSteamMusicRemote::get() { static StarSteamMusicRemote i; return i; }
bool StarSteamMusicRemote::RegisterSteamMusicRemote(const char* n) { STAR_UNREFERENCED(n); return false; }
bool StarSteamMusicRemote::DeregisterSteamMusicRemote() { return false; }
bool StarSteamMusicRemote::BIsCurrentMusicRemote() { return false; }
bool StarSteamMusicRemote::BActivationSuccess(bool b) { STAR_UNREFERENCED(b); return false; }
bool StarSteamMusicRemote::SetDisplayName(const char* n) { STAR_UNREFERENCED(n); return false; }
bool StarSteamMusicRemote::SetPNGIcon_64x64(void* b, uint32 l) { STAR_UNREFERENCED(b); STAR_UNREFERENCED(l); return false; }
bool StarSteamMusicRemote::EnablePlayPrevious(bool b) { STAR_UNREFERENCED(b); return false; }
bool StarSteamMusicRemote::EnablePlayNext(bool b) { STAR_UNREFERENCED(b); return false; }
bool StarSteamMusicRemote::EnableShuffled(bool b) { STAR_UNREFERENCED(b); return false; }
bool StarSteamMusicRemote::EnableLooped(bool b) { STAR_UNREFERENCED(b); return false; }
bool StarSteamMusicRemote::EnableQueue(bool b) { STAR_UNREFERENCED(b); return false; }
bool StarSteamMusicRemote::EnablePlaylists(bool b) { STAR_UNREFERENCED(b); return false; }
bool StarSteamMusicRemote::UpdatePlaybackStatus(AudioPlayback_Status n) { STAR_UNREFERENCED(n); return false; }
bool StarSteamMusicRemote::UpdateShuffled(bool b) { STAR_UNREFERENCED(b); return false; }
bool StarSteamMusicRemote::UpdateLooped(bool b) { STAR_UNREFERENCED(b); return false; }
bool StarSteamMusicRemote::UpdateVolume(float f) { STAR_UNREFERENCED(f); return false; }
bool StarSteamMusicRemote::CurrentEntryWillChange() { return false; }
bool StarSteamMusicRemote::CurrentEntryIsAvailable(bool b) { STAR_UNREFERENCED(b); return false; }
bool StarSteamMusicRemote::UpdateCurrentEntryText(const char* t) { STAR_UNREFERENCED(t); return false; }
bool StarSteamMusicRemote::UpdateCurrentEntryElapsedSeconds(int n) { STAR_UNREFERENCED(n); return false; }
bool StarSteamMusicRemote::UpdateCurrentEntryCoverArt(void* b, uint32 l) { STAR_UNREFERENCED(b); STAR_UNREFERENCED(l); return false; }
bool StarSteamMusicRemote::CurrentEntryDidChange() { return false; }
bool StarSteamMusicRemote::QueueWillChange() { return false; }
bool StarSteamMusicRemote::ResetQueueEntries() { return false; }
bool StarSteamMusicRemote::SetQueueEntry(int i, int p, const char* t) { STAR_UNREFERENCED(i); STAR_UNREFERENCED(p); STAR_UNREFERENCED(t); return false; }
bool StarSteamMusicRemote::SetCurrentQueueEntry(int i) { STAR_UNREFERENCED(i); return false; }
bool StarSteamMusicRemote::QueueDidChange() { return false; }
bool StarSteamMusicRemote::PlaylistWillChange() { return false; }
bool StarSteamMusicRemote::ResetPlaylistEntries() { return false; }
bool StarSteamMusicRemote::SetPlaylistEntry(int i, int p, const char* t) { STAR_UNREFERENCED(i); STAR_UNREFERENCED(p); STAR_UNREFERENCED(t); return false; }
bool StarSteamMusicRemote::SetCurrentPlaylistEntry(int i) { STAR_UNREFERENCED(i); return false; }
bool StarSteamMusicRemote::PlaylistDidChange() { return false; }
