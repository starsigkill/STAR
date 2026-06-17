#pragma once
#include "core/star_common.h"
#include "steam/isteammatchmaking.h"

class StarSteamMatchmaking : public ISteamMatchmaking {
public:
    static StarSteamMatchmaking& get();
    int GetFavoriteGameCount() override;
    bool GetFavoriteGame(int iGame, AppId_t* pnAppID, uint32* pnIP, uint16* pnConnPort, uint16* pnQueryPort, uint32* punFlags, uint32* pRTime32LastPlayedOnServer) override;
    int AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer) override;
    bool RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags) override;
    CSteamID GetLobbyByIndex(int iLobby) override;
    SteamAPICall_t RequestLobbyList() override;
    void AddRequestLobbyListStringFilter(const char* pchKeyToMatch, const char* pchValueToMatch, ELobbyComparison eComparisonType) override;
    void AddRequestLobbyListNumericalFilter(const char* pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType) override;
    void AddRequestLobbyListNearValueFilter(const char* pchKeyToMatch, int nValueToBeCloseTo) override;
    void AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable) override;
    void AddRequestLobbyListDistanceFilter(ELobbyDistanceFilter eLobbyDistanceFilter) override;
    void AddRequestLobbyListResultCountFilter(int cMaxResults) override;
    void AddRequestLobbyListCompatibleMembersFilter(CSteamID steamIDLobby) override;
    SteamAPICall_t CreateLobby(ELobbyType eLobbyType, int cMaxMembers) override;
    SteamAPICall_t JoinLobby(CSteamID steamIDLobby) override;
    void LeaveLobby(CSteamID steamIDLobby) override;
    bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee) override;
    int GetNumLobbyMembers(CSteamID steamIDLobby) override;
    CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember) override;
    const char* GetLobbyData(CSteamID steamIDLobby, const char* pchKey) override;
    bool SetLobbyData(CSteamID steamIDLobby, const char* pchKey, const char* pchValue) override;
    int GetLobbyDataCount(CSteamID steamIDLobby) override;
    bool GetLobbyDataByIndex(CSteamID steamIDLobby, int iLobbyData, char* pchKey, int cchKeyBufferSize, char* pchValue, int cchValueBufferSize) override;
    bool DeleteLobbyData(CSteamID steamIDLobby, const char* pchKey) override;
    const char* GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char* pchKey) override;
    void SetLobbyMemberData(CSteamID steamIDLobby, const char* pchKey, const char* pchValue) override;
    bool SendLobbyChatMsg(CSteamID steamIDLobby, const void* pvMsgBody, int cubMsgBody) override;
    int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID* pSteamIDUser, void* pvData, int cubData, EChatEntryType* peChatEntryType) override;
    bool RequestLobbyData(CSteamID steamIDLobby) override;
    void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer) override;
    bool GetLobbyGameServer(CSteamID steamIDLobby, uint32* punGameServerIP, uint16* punGameServerPort, CSteamID* psteamIDGameServer) override;
    bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers) override;
    int GetLobbyMemberLimit(CSteamID steamIDLobby) override;
    bool SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType) override;
    bool SetLobbyJoinable(CSteamID steamIDLobby, bool bLobbyJoinable) override;
    CSteamID GetLobbyOwner(CSteamID steamIDLobby) override;
    bool SetLobbyOwner(CSteamID steamIDLobby, CSteamID steamIDNewOwner) override;
    bool SetLinkedLobby(CSteamID steamIDLobby, CSteamID steamIDLobbyDependent) override;
private:
    StarSteamMatchmaking() = default;
};
