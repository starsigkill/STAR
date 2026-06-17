#pragma once
#include "core/star_common.h"
#include "steam/isteammatchmaking.h"

class StarSteamMatchmakingServers : public ISteamMatchmakingServers {
public:
    static StarSteamMatchmakingServers& get();
    HServerListRequest RequestInternetServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse) override;
    HServerListRequest RequestLANServerList(AppId_t iApp, ISteamMatchmakingServerListResponse* pRequestServersResponse) override;
    HServerListRequest RequestFriendsServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse) override;
    HServerListRequest RequestFavoritesServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse) override;
    HServerListRequest RequestHistoryServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse) override;
    HServerListRequest RequestSpectatorServerList(AppId_t iApp, MatchMakingKeyValuePair_t** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse* pRequestServersResponse) override;
    void ReleaseRequest(HServerListRequest hServerListRequest) override;
    gameserveritem_t* GetServerDetails(HServerListRequest hRequest, int iServer) override;
    void CancelQuery(HServerListRequest hRequest) override;
    void RefreshQuery(HServerListRequest hRequest) override;
    bool IsRefreshing(HServerListRequest hRequest) override;
    int GetServerCount(HServerListRequest hRequest) override;
    void RefreshServer(HServerListRequest hRequest, int iServer) override;
    HServerQuery PingServer(uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse* pRequestServersResponse) override;
    HServerQuery PlayerDetails(uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse* pRequestServersResponse) override;
    HServerQuery ServerRules(uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse* pRequestServersResponse) override;
    void CancelServerQuery(HServerQuery hServerQuery) override;
private:
    StarSteamMatchmakingServers() = default;
};
