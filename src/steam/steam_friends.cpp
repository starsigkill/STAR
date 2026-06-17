#include "steam/steam_friends.h"
#include "core/callbacks.h"
#include "core/settings.h"
#include "steam/isteamfriends.h"

StarSteamFriends& StarSteamFriends::get()
{
    static StarSteamFriends instance;
    return instance;
}

const char* StarSteamFriends::GetPersonaName()
{
    return Settings::get().account_name.c_str();
}

SteamAPICall_t StarSteamFriends::SetPersonaName(const char* pchPersonaName)
{
    if (pchPersonaName) Settings::get().account_name = pchPersonaName;
    SetPersonaNameResponse_t result{};
    result.m_bSuccess = true;
    result.m_bLocalSuccess = true;
    result.m_result = k_EResultOK;
    return STAR_PostCallResult(SetPersonaNameResponse_t::k_iCallback, &result, sizeof(result));
}

EPersonaState StarSteamFriends::GetPersonaState() { return k_EPersonaStateOnline; }
int StarSteamFriends::GetFriendCount(int iFriendFlags) { STAR_UNREFERENCED(iFriendFlags); return 0; }
CSteamID StarSteamFriends::GetFriendByIndex(int iFriend, int iFriendFlags) { STAR_UNREFERENCED(iFriend); STAR_UNREFERENCED(iFriendFlags); return k_steamIDNil; }
EFriendRelationship StarSteamFriends::GetFriendRelationship(CSteamID steamIDFriend) { STAR_UNREFERENCED(steamIDFriend); return k_EFriendRelationshipNone; }
EPersonaState StarSteamFriends::GetFriendPersonaState(CSteamID steamIDFriend) { STAR_UNREFERENCED(steamIDFriend); return k_EPersonaStateOffline; }
const char* StarSteamFriends::GetFriendPersonaName(CSteamID steamIDFriend) { STAR_UNREFERENCED(steamIDFriend); return ""; }
bool StarSteamFriends::GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t* pFriendGameInfo) { STAR_UNREFERENCED(steamIDFriend); if (pFriendGameInfo) memset(pFriendGameInfo, 0, sizeof(*pFriendGameInfo)); return false; }
const char* StarSteamFriends::GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName) { STAR_UNREFERENCED(steamIDFriend); STAR_UNREFERENCED(iPersonaName); return ""; }
int StarSteamFriends::GetFriendSteamLevel(CSteamID steamIDFriend) { STAR_UNREFERENCED(steamIDFriend); return 0; }
const char* StarSteamFriends::GetPlayerNickname(CSteamID steamIDPlayer) { STAR_UNREFERENCED(steamIDPlayer); return nullptr; }
int StarSteamFriends::GetFriendsGroupCount() { return 0; }
FriendsGroupID_t StarSteamFriends::GetFriendsGroupIDByIndex(int iFG) { STAR_UNREFERENCED(iFG); return k_FriendsGroupID_Invalid; }
const char* StarSteamFriends::GetFriendsGroupName(FriendsGroupID_t friendsGroupID) { STAR_UNREFERENCED(friendsGroupID); return nullptr; }
int StarSteamFriends::GetFriendsGroupMembersCount(FriendsGroupID_t friendsGroupID) { STAR_UNREFERENCED(friendsGroupID); return 0; }
void StarSteamFriends::GetFriendsGroupMembersList(FriendsGroupID_t friendsGroupID, CSteamID* pOutSteamIDMembers, int nMembersCount) { STAR_UNREFERENCED(friendsGroupID); STAR_UNREFERENCED(pOutSteamIDMembers); STAR_UNREFERENCED(nMembersCount); }
bool StarSteamFriends::HasFriend(CSteamID steamIDFriend, int iFriendFlags) { STAR_UNREFERENCED(steamIDFriend); STAR_UNREFERENCED(iFriendFlags); return false; }
int StarSteamFriends::GetClanCount() { return 0; }
CSteamID StarSteamFriends::GetClanByIndex(int iClan) { STAR_UNREFERENCED(iClan); return k_steamIDNil; }
const char* StarSteamFriends::GetClanName(CSteamID steamIDClan) { STAR_UNREFERENCED(steamIDClan); return ""; }
const char* StarSteamFriends::GetClanTag(CSteamID steamIDClan) { STAR_UNREFERENCED(steamIDClan); return ""; }
bool StarSteamFriends::GetClanActivityCounts(CSteamID steamIDClan, int* pnOnline, int* pnInGame, int* pnChatting) { STAR_UNREFERENCED(steamIDClan); if (pnOnline) *pnOnline=0; if (pnInGame) *pnInGame=0; if (pnChatting) *pnChatting=0; return false; }
SteamAPICall_t StarSteamFriends::DownloadClanActivityCounts(CSteamID* psteamIDClans, int cClansToRequest) { STAR_UNREFERENCED(psteamIDClans); STAR_UNREFERENCED(cClansToRequest); return k_uAPICallInvalid; }
int StarSteamFriends::GetFriendCountFromSource(CSteamID steamIDSource) { STAR_UNREFERENCED(steamIDSource); return 0; }
CSteamID StarSteamFriends::GetFriendFromSourceByIndex(CSteamID steamIDSource, int iFriend) { STAR_UNREFERENCED(steamIDSource); STAR_UNREFERENCED(iFriend); return k_steamIDNil; }
bool StarSteamFriends::IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource) { STAR_UNREFERENCED(steamIDUser); STAR_UNREFERENCED(steamIDSource); return false; }
void StarSteamFriends::SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking) { STAR_UNREFERENCED(steamIDUser); STAR_UNREFERENCED(bSpeaking); }
void StarSteamFriends::ActivateGameOverlay(const char* pchDialog) { STAR_UNREFERENCED(pchDialog); }
void StarSteamFriends::ActivateGameOverlayToUser(const char* pchDialog, CSteamID steamID) { STAR_UNREFERENCED(pchDialog); STAR_UNREFERENCED(steamID); }
void StarSteamFriends::ActivateGameOverlayToWebPage(const char* pchURL) { STAR_UNREFERENCED(pchURL); }
void StarSteamFriends::ActivateGameOverlayToStore(AppId_t nAppID, EOverlayToStoreFlag eFlag) { STAR_UNREFERENCED(nAppID); STAR_UNREFERENCED(eFlag); }
void StarSteamFriends::SetPlayedWith(CSteamID steamIDUserPlayedWith) { STAR_UNREFERENCED(steamIDUserPlayedWith); }
void StarSteamFriends::ActivateGameOverlayInviteDialog(CSteamID steamIDLobby) { STAR_UNREFERENCED(steamIDLobby); }
int StarSteamFriends::GetSmallFriendAvatar(CSteamID steamIDFriend) { STAR_UNREFERENCED(steamIDFriend); return 0; }
int StarSteamFriends::GetMediumFriendAvatar(CSteamID steamIDFriend) { STAR_UNREFERENCED(steamIDFriend); return 0; }
int StarSteamFriends::GetLargeFriendAvatar(CSteamID steamIDFriend) { STAR_UNREFERENCED(steamIDFriend); return 0; }
bool StarSteamFriends::RequestUserInformation(CSteamID steamIDUser, bool bRequireNameOnly) { STAR_UNREFERENCED(steamIDUser); STAR_UNREFERENCED(bRequireNameOnly); return false; }
SteamAPICall_t StarSteamFriends::RequestClanOfficerList(CSteamID steamIDClan) { STAR_UNREFERENCED(steamIDClan); return k_uAPICallInvalid; }
CSteamID StarSteamFriends::GetClanOwner(CSteamID steamIDClan) { STAR_UNREFERENCED(steamIDClan); return k_steamIDNil; }
int StarSteamFriends::GetClanOfficerCount(CSteamID steamIDClan) { STAR_UNREFERENCED(steamIDClan); return 0; }
CSteamID StarSteamFriends::GetClanOfficerByIndex(CSteamID steamIDClan, int iOfficer) { STAR_UNREFERENCED(steamIDClan); STAR_UNREFERENCED(iOfficer); return k_steamIDNil; }
uint32 StarSteamFriends::GetUserRestrictions() { return 0; }
bool StarSteamFriends::SetRichPresence(const char* pchKey, const char* pchValue) { STAR_UNREFERENCED(pchKey); STAR_UNREFERENCED(pchValue); return true; }
void StarSteamFriends::ClearRichPresence() {}
const char* StarSteamFriends::GetFriendRichPresence(CSteamID steamIDFriend, const char* pchKey) { STAR_UNREFERENCED(steamIDFriend); STAR_UNREFERENCED(pchKey); return ""; }
int StarSteamFriends::GetFriendRichPresenceKeyCount(CSteamID steamIDFriend) { STAR_UNREFERENCED(steamIDFriend); return 0; }
const char* StarSteamFriends::GetFriendRichPresenceKeyByIndex(CSteamID steamIDFriend, int iKey) { STAR_UNREFERENCED(steamIDFriend); STAR_UNREFERENCED(iKey); return ""; }
void StarSteamFriends::RequestFriendRichPresence(CSteamID steamIDFriend) { STAR_UNREFERENCED(steamIDFriend); }
bool StarSteamFriends::InviteUserToGame(CSteamID steamIDFriend, const char* pchConnectString) { STAR_UNREFERENCED(steamIDFriend); STAR_UNREFERENCED(pchConnectString); return false; }
int StarSteamFriends::GetCoplayFriendCount() { return 0; }
CSteamID StarSteamFriends::GetCoplayFriend(int iCoplayFriend) { STAR_UNREFERENCED(iCoplayFriend); return k_steamIDNil; }
int StarSteamFriends::GetFriendCoplayTime(CSteamID steamIDFriend) { STAR_UNREFERENCED(steamIDFriend); return 0; }
AppId_t StarSteamFriends::GetFriendCoplayGame(CSteamID steamIDFriend) { STAR_UNREFERENCED(steamIDFriend); return 0; }
SteamAPICall_t StarSteamFriends::JoinClanChatRoom(CSteamID steamIDClan) { STAR_UNREFERENCED(steamIDClan); return k_uAPICallInvalid; }
bool StarSteamFriends::LeaveClanChatRoom(CSteamID steamIDClan) { STAR_UNREFERENCED(steamIDClan); return false; }
int StarSteamFriends::GetClanChatMemberCount(CSteamID steamIDClan) { STAR_UNREFERENCED(steamIDClan); return 0; }
CSteamID StarSteamFriends::GetChatMemberByIndex(CSteamID steamIDClan, int iUser) { STAR_UNREFERENCED(steamIDClan); STAR_UNREFERENCED(iUser); return k_steamIDNil; }
bool StarSteamFriends::SendClanChatMessage(CSteamID steamIDClanChat, const char* pchText) { STAR_UNREFERENCED(steamIDClanChat); STAR_UNREFERENCED(pchText); return false; }
int StarSteamFriends::GetClanChatMessage(CSteamID steamIDClanChat, int iMessage, void* prgchText, int cchTextMax, EChatEntryType* peChatEntryType, CSteamID* psteamidChatter) { STAR_UNREFERENCED(steamIDClanChat); STAR_UNREFERENCED(iMessage); STAR_UNREFERENCED(prgchText); STAR_UNREFERENCED(cchTextMax); if (peChatEntryType) *peChatEntryType = k_EChatEntryTypeInvalid; if (psteamidChatter) *psteamidChatter = k_steamIDNil; return 0; }
bool StarSteamFriends::IsClanChatAdmin(CSteamID steamIDClanChat, CSteamID steamIDUser) { STAR_UNREFERENCED(steamIDClanChat); STAR_UNREFERENCED(steamIDUser); return false; }
bool StarSteamFriends::IsClanChatWindowOpenInSteam(CSteamID steamIDClanChat) { STAR_UNREFERENCED(steamIDClanChat); return false; }
bool StarSteamFriends::OpenClanChatWindowInSteam(CSteamID steamIDClanChat) { STAR_UNREFERENCED(steamIDClanChat); return false; }
bool StarSteamFriends::CloseClanChatWindowInSteam(CSteamID steamIDClanChat) { STAR_UNREFERENCED(steamIDClanChat); return false; }
bool StarSteamFriends::SetListenForFriendsMessages(bool bInterceptEnabled) { STAR_UNREFERENCED(bInterceptEnabled); return false; }
bool StarSteamFriends::ReplyToFriendMessage(CSteamID steamIDFriend, const char* pchMsgToSend) { STAR_UNREFERENCED(steamIDFriend); STAR_UNREFERENCED(pchMsgToSend); return false; }
int StarSteamFriends::GetFriendMessage(CSteamID steamIDFriend, int iMessageID, void* pvData, int cubData, EChatEntryType* peChatEntryType) { STAR_UNREFERENCED(steamIDFriend); STAR_UNREFERENCED(iMessageID); STAR_UNREFERENCED(pvData); STAR_UNREFERENCED(cubData); if (peChatEntryType) *peChatEntryType = k_EChatEntryTypeInvalid; return 0; }

SteamAPICall_t StarSteamFriends::GetFollowerCount(CSteamID steamID)
{
    FriendsGetFollowerCount_t result{};
    result.m_eResult = k_EResultOK;
    result.m_steamID = steamID;
    result.m_nCount = 0;
    return STAR_PostCallResult(FriendsGetFollowerCount_t::k_iCallback, &result, sizeof(result));
}

SteamAPICall_t StarSteamFriends::IsFollowing(CSteamID steamID)
{
    FriendsIsFollowing_t result{};
    result.m_eResult = k_EResultOK;
    result.m_steamID = steamID;
    result.m_bIsFollowing = false;
    return STAR_PostCallResult(FriendsIsFollowing_t::k_iCallback, &result, sizeof(result));
}

SteamAPICall_t StarSteamFriends::EnumerateFollowingList(uint32 unStartIndex)
{
    STAR_UNREFERENCED(unStartIndex);
    FriendsEnumerateFollowingList_t result{};
    result.m_eResult = k_EResultOK;
    result.m_nResultsReturned = 0;
    result.m_nTotalResultCount = 0;
    return STAR_PostCallResult(FriendsEnumerateFollowingList_t::k_iCallback, &result, sizeof(result));
}

bool StarSteamFriends::IsClanPublic(CSteamID steamIDClan) { STAR_UNREFERENCED(steamIDClan); return false; }
bool StarSteamFriends::IsClanOfficialGameGroup(CSteamID steamIDClan) { STAR_UNREFERENCED(steamIDClan); return false; }

int StarSteamFriends::GetNumChatsWithUnreadPriorityMessages() { return 0; }

void StarSteamFriends::ActivateGameOverlayToWebPage(const char* pchURL, EActivateGameOverlayToWebPageMode eMode)
{
    STAR_UNREFERENCED(eMode);
    ActivateGameOverlayToWebPage(pchURL);
}
void StarSteamFriends::ActivateGameOverlayRemotePlayTogetherInviteDialog(CSteamID steamIDLobby) { STAR_UNREFERENCED(steamIDLobby); }
bool StarSteamFriends::RegisterProtocolInOverlayBrowser(const char* pchProtocol) { STAR_UNREFERENCED(pchProtocol); return false; }
void StarSteamFriends::ActivateGameOverlayInviteDialogConnectString(const char* pchConnectString) { STAR_UNREFERENCED(pchConnectString); }

SteamAPICall_t StarSteamFriends::RequestEquippedProfileItems(CSteamID steamID)
{
    STAR_UNREFERENCED(steamID);
    EquippedProfileItems_t result{};
    result.m_eResult = k_EResultOK;
    return STAR_PostCallResult(EquippedProfileItems_t::k_iCallback, &result, sizeof(result));
}

bool StarSteamFriends::BHasEquippedProfileItem(CSteamID steamID, ECommunityProfileItemType itemType)
{
    STAR_UNREFERENCED(steamID); STAR_UNREFERENCED(itemType);
    return false;
}

const char* StarSteamFriends::GetProfileItemPropertyString(CSteamID steamID, ECommunityProfileItemType itemType, ECommunityProfileItemProperty prop)
{
    STAR_UNREFERENCED(steamID); STAR_UNREFERENCED(itemType); STAR_UNREFERENCED(prop);
    return "";
}

uint32 StarSteamFriends::GetProfileItemPropertyUint(CSteamID steamID, ECommunityProfileItemType itemType, ECommunityProfileItemProperty prop)
{
    STAR_UNREFERENCED(steamID); STAR_UNREFERENCED(itemType); STAR_UNREFERENCED(prop);
    return 0;
}
