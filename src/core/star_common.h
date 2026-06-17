#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <wincrypt.h>

#include <cstdint>
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <unordered_map>
#include <mutex>
#include <functional>
#include <chrono>
#include <filesystem>
#include <memory>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "steam/steam_api_common.h"

#include "steam/isteamclient.h"
#include "steam/isteamuser.h"
#include "steam/isteamfriends.h"
#include "steam/isteamutils.h"
#include "steam/isteammatchmaking.h"
#include "steam/isteamuserstats.h"
#include "steam/isteamapps.h"
#include "steam/isteamnetworking.h"
#include "steam/isteamremotestorage.h"
#include "steam/isteamscreenshots.h"
#include "steam/isteamhttp.h"
#include "steam/isteamcontroller.h"
#include "steam/isteamugc.h"
#include "steam/isteamapplist.h"
#include "steam/isteammusic.h"
#include "steam/isteammusicremote.h"
#include "steam/isteamhtmlsurface.h"
#include "steam/isteaminventory.h"
#include "steam/isteamvideo.h"
#include "steam/isteamunifiedmessages.h"
struct SteamNetworkingIdentity;
#include "steam/isteamgameserver.h"
#include "steam/isteamgameserverstats.h"
#include "steam/isteamgamestats.h"

class StarSteamClient;
class StarSteamUser;
class StarSteamFriends;
class StarSteamUtils;
class StarSteamMatchmaking;
class StarSteamMatchmakingServers;
class StarSteamUserStats;
class StarSteamApps;
class StarSteamNetworking;
class StarSteamRemoteStorage;
class StarSteamScreenshots;
class StarSteamHTTP;
class StarSteamController;
class StarSteamUGC;
class StarSteamAppList;
class StarSteamMusic;
class StarSteamMusicRemote;
class StarSteamHTMLSurface;
class StarSteamInventory;
class StarSteamVideo;
class StarSteamUnifiedMessages;
class StarSteamGameServer;
class StarSteamGameServerStats;

#include <cstdarg>
void STAR_WriteLog(const char* fmt, ...);
#define STAR_LOG(fmt, ...) STAR_WriteLog(fmt, ##__VA_ARGS__)

#define STAR_UNREFERENCED(x) (void)(x)
