#pragma once
#include "core/star_common.h"
#include "steam/steamnetworkingtypes.h"
#include "steam/isteamnetworkingutils003.h"

class StarSteamNetworkingUtils : public ISteamNetworkingUtils003
{
public:
    static StarSteamNetworkingUtils& get() { static StarSteamNetworkingUtils s; return s; }

    SteamNetworkingMessage_t* AllocateMessage(int) override { return nullptr; }
    ESteamNetworkingAvailability GetRelayNetworkStatus(SteamRelayNetworkStatus_t*) override { return k_ESteamNetworkingAvailability_CannotTry; }
    float GetLocalPingLocation(SteamNetworkPingLocation_t&) override { return -1.0f; }
    int EstimatePingTimeBetweenTwoLocations(const SteamNetworkPingLocation_t&, const SteamNetworkPingLocation_t&) override { return -1; }
    int EstimatePingTimeFromLocalHost(const SteamNetworkPingLocation_t&) override { return -1; }
    void ConvertPingLocationToString(const SteamNetworkPingLocation_t&, char* pszBuf, int cchBufSize) override { if (pszBuf && cchBufSize > 0) pszBuf[0] = 0; }
    bool ParsePingLocationString(const char*, SteamNetworkPingLocation_t&) override { return false; }
    bool CheckPingDataUpToDate(float) override { return false; }
    int GetPingToDataCenter(SteamNetworkingPOPID, SteamNetworkingPOPID*) override { return -1; }
    int GetDirectPingToPOP(SteamNetworkingPOPID) override { return -1; }
    int GetPOPCount() override { return 0; }
    int GetPOPList(SteamNetworkingPOPID*, int) override { return 0; }
    SteamNetworkingMicroseconds GetLocalTimestamp() override { return 0; }
    void SetDebugOutputFunction(ESteamNetworkingSocketsDebugOutputType, FSteamNetworkingSocketsDebugOutput) override {}
    bool SetConfigValue(ESteamNetworkingConfigValue, ESteamNetworkingConfigScope, intptr_t, ESteamNetworkingConfigDataType, const void*) override { return false; }
    ESteamNetworkingGetConfigValueResult GetConfigValue(ESteamNetworkingConfigValue, ESteamNetworkingConfigScope, intptr_t, ESteamNetworkingConfigDataType*, void*, size_t*) override { return k_ESteamNetworkingGetConfigValue_BadValue; }
    bool GetConfigValueInfo(ESteamNetworkingConfigValue, const char**, ESteamNetworkingConfigDataType*, ESteamNetworkingConfigScope*, ESteamNetworkingConfigValue*) override { return false; }
    ESteamNetworkingConfigValue GetFirstConfigValue() override { return k_ESteamNetworkingConfig_Invalid; }
    void SteamNetworkingIPAddr_ToString(const SteamNetworkingIPAddr&, char* buf, size_t cbBuf, bool) override { if (buf && cbBuf > 0) buf[0] = 0; }
    bool SteamNetworkingIPAddr_ParseString(SteamNetworkingIPAddr*, const char*) override { return false; }
    void SteamNetworkingIdentity_ToString(const SteamNetworkingIdentity&, char* buf, size_t cbBuf) override { if (buf && cbBuf > 0) buf[0] = 0; }
    bool SteamNetworkingIdentity_ParseString(SteamNetworkingIdentity*, const char*) override { return false; }
};
