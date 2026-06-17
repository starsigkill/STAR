#pragma once
#include "core/star_common.h"
#include "steam/steamnetworkingtypes.h"

class ISteamNetworkingConnectionCustomSignaling;
class ISteamNetworkingCustomSignalingRecvContext;

#include "steam/isteamnetworkingsockets008.h"

class StarSteamNetworkingSockets : public ISteamNetworkingSockets008
{
public:
    static StarSteamNetworkingSockets& get() { static StarSteamNetworkingSockets s; return s; }

    HSteamListenSocket CreateListenSocketIP(const SteamNetworkingIPAddr&, int, const SteamNetworkingConfigValue_t*) override { return 0; }
    HSteamNetConnection ConnectByIPAddress(const SteamNetworkingIPAddr&, int, const SteamNetworkingConfigValue_t*) override { return 0; }
    HSteamListenSocket CreateListenSocketP2P(int, int, const SteamNetworkingConfigValue_t*) override { return 0; }
    HSteamNetConnection ConnectP2P(const SteamNetworkingIdentity&, int, int, const SteamNetworkingConfigValue_t*) override { return 0; }
    EResult AcceptConnection(HSteamNetConnection) override { return k_EResultFail; }
    bool CloseConnection(HSteamNetConnection, int, const char*, bool) override { return true; }
    bool CloseListenSocket(HSteamListenSocket) override { return true; }
    bool SetConnectionUserData(HSteamNetConnection, int64) override { return false; }
    int64 GetConnectionUserData(HSteamNetConnection) override { return -1; }
    void SetConnectionName(HSteamNetConnection, const char*) override {}
    bool GetConnectionName(HSteamNetConnection, char* pszName, int nMaxLen) override { if (pszName && nMaxLen > 0) pszName[0] = 0; return false; }
    EResult SendMessageToConnection(HSteamNetConnection, const void*, uint32, int, int64*) override { return k_EResultFail; }
    void SendMessages(int nMessages, SteamNetworkingMessage_t* const* pMessages, int64* pOutNumberOrResult) override
    {
        if (pOutNumberOrResult)
            for (int i = 0; i < nMessages; ++i) pOutNumberOrResult[i] = -static_cast<int64>(k_EResultFail);
    }
    EResult FlushMessagesOnConnection(HSteamNetConnection) override { return k_EResultFail; }
    int ReceiveMessagesOnConnection(HSteamNetConnection, SteamNetworkingMessage_t**, int) override { return 0; }
    bool GetConnectionInfo(HSteamNetConnection, SteamNetConnectionInfo_t*) override { return false; }
    bool GetQuickConnectionStatus(HSteamNetConnection, SteamNetworkingQuickConnectionStatus*) override { return false; }
    int GetDetailedConnectionStatus(HSteamNetConnection, char*, int) override { return -1; }
    bool GetListenSocketAddress(HSteamListenSocket, SteamNetworkingIPAddr*) override { return false; }
    bool CreateSocketPair(HSteamNetConnection*, HSteamNetConnection*, bool, const SteamNetworkingIdentity*, const SteamNetworkingIdentity*) override { return false; }
    bool GetIdentity(SteamNetworkingIdentity*) override { return false; }
    ESteamNetworkingAvailability InitAuthentication() override { return k_ESteamNetworkingAvailability_CannotTry; }
    ESteamNetworkingAvailability GetAuthenticationStatus(SteamNetAuthenticationStatus_t*) override { return k_ESteamNetworkingAvailability_CannotTry; }
    HSteamNetPollGroup CreatePollGroup() override { return 0; }
    bool DestroyPollGroup(HSteamNetPollGroup) override { return false; }
    bool SetConnectionPollGroup(HSteamNetConnection, HSteamNetPollGroup) override { return false; }
    int ReceiveMessagesOnPollGroup(HSteamNetPollGroup, SteamNetworkingMessage_t**, int) override { return 0; }
    bool ReceivedRelayAuthTicket(const void*, int, SteamDatagramRelayAuthTicket*) override { return false; }
    int FindRelayAuthTicketForServer(const SteamNetworkingIdentity&, int, SteamDatagramRelayAuthTicket*) override { return 0; }
    HSteamNetConnection ConnectToHostedDedicatedServer(const SteamNetworkingIdentity&, int, int, const SteamNetworkingConfigValue_t*) override { return 0; }
    uint16 GetHostedDedicatedServerPort() override { return 0; }
    SteamNetworkingPOPID GetHostedDedicatedServerPOPID() override { return 0; }
    EResult GetHostedDedicatedServerAddress(SteamDatagramHostedAddress*) override { return k_EResultFail; }
    HSteamListenSocket CreateHostedDedicatedServerListenSocket(int, int, const SteamNetworkingConfigValue_t*) override { return 0; }
    EResult GetGameCoordinatorServerLogin(SteamDatagramGameCoordinatorServerLogin*, int*, void*) override { return k_EResultFail; }
    HSteamNetConnection ConnectP2PCustomSignaling(ISteamNetworkingConnectionCustomSignaling*, const SteamNetworkingIdentity*, int, const SteamNetworkingConfigValue_t*) override { return 0; }
    bool ReceivedP2PCustomSignal(const void*, int, ISteamNetworkingCustomSignalingRecvContext*) override { return false; }
    bool GetCertificateRequest(int*, void*, SteamNetworkingErrMsg&) override { return false; }
    bool SetCertificate(const void*, int, SteamNetworkingErrMsg&) override { return false; }
};
