// Auto-generated flat API stubs for complete Steamworks SDK coverage.
// This file ensures that any game using the Flat C API doesn't fail to load due to missing entry points.
#include "core/star_common.h"
#include "steam/steam_api.h"
#include "steam/steam_api_flat.h"

#pragma warning(push)
#pragma warning(disable: 4190) // C-linkage returning UDT warning

STAR_EXPORT HSteamUser SteamAPI_ISteamUser_GetHSteamUser(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamUser_InitiateGameConnection(ISteamUser* self, void * pAuthBlob, int cbMaxAuthBlob, uint64_steamid steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pAuthBlob);
    STAR_UNREFERENCED(cbMaxAuthBlob);
    STAR_UNREFERENCED(steamIDGameServer);
    STAR_UNREFERENCED(unIPServer);
    STAR_UNREFERENCED(usPortServer);
    STAR_UNREFERENCED(bSecure);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamUser_TerminateGameConnection(ISteamUser* self, uint32 unIPServer, uint16 usPortServer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unIPServer);
    STAR_UNREFERENCED(usPortServer);
}

STAR_EXPORT int SteamAPI_ISteamUser_InitiateGameConnection_DEPRECATED(ISteamUser* self, void * pAuthBlob, int cbMaxAuthBlob, uint64_steamid steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pAuthBlob);
    STAR_UNREFERENCED(cbMaxAuthBlob);
    STAR_UNREFERENCED(steamIDGameServer);
    STAR_UNREFERENCED(unIPServer);
    STAR_UNREFERENCED(usPortServer);
    STAR_UNREFERENCED(bSecure);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamUser_TerminateGameConnection_DEPRECATED(ISteamUser* self, uint32 unIPServer, uint16 usPortServer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unIPServer);
    STAR_UNREFERENCED(usPortServer);
}

STAR_EXPORT void SteamAPI_ISteamUser_TrackAppUsageEvent(ISteamUser* self, uint64_gameid gameID, int eAppUsageEvent, const char * pchExtraInfo)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(gameID);
    STAR_UNREFERENCED(eAppUsageEvent);
    STAR_UNREFERENCED(pchExtraInfo);
}

STAR_EXPORT steam_bool SteamAPI_ISteamUser_GetUserDataFolder(ISteamUser* self, char * pchBuffer, int cubBuffer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchBuffer);
    STAR_UNREFERENCED(cubBuffer);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamUser_StartVoiceRecording(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamUser_StopVoiceRecording(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT EVoiceResult SteamAPI_ISteamUser_GetAvailableVoice(ISteamUser* self, uint32 * pcbCompressed, uint32 * pcbUncompressed_Deprecated, uint32 nUncompressedVoiceDesiredSampleRate_Deprecated)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pcbCompressed);
    STAR_UNREFERENCED(pcbUncompressed_Deprecated);
    STAR_UNREFERENCED(nUncompressedVoiceDesiredSampleRate_Deprecated);
    return {};
}

STAR_EXPORT EVoiceResult SteamAPI_ISteamUser_GetVoice(ISteamUser* self, bool bWantCompressed, void * pDestBuffer, uint32 cbDestBufferSize, uint32 * nBytesWritten, bool bWantUncompressed_Deprecated, void * pUncompressedDestBuffer_Deprecated, uint32 cbUncompressedDestBufferSize_Deprecated, uint32 * nUncompressBytesWritten_Deprecated, uint32 nUncompressedVoiceDesiredSampleRate_Deprecated)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bWantCompressed);
    STAR_UNREFERENCED(pDestBuffer);
    STAR_UNREFERENCED(cbDestBufferSize);
    STAR_UNREFERENCED(nBytesWritten);
    STAR_UNREFERENCED(bWantUncompressed_Deprecated);
    STAR_UNREFERENCED(pUncompressedDestBuffer_Deprecated);
    STAR_UNREFERENCED(cbUncompressedDestBufferSize_Deprecated);
    STAR_UNREFERENCED(nUncompressBytesWritten_Deprecated);
    STAR_UNREFERENCED(nUncompressedVoiceDesiredSampleRate_Deprecated);
    return {};
}

STAR_EXPORT EVoiceResult SteamAPI_ISteamUser_DecompressVoice(ISteamUser* self, const void * pCompressed, uint32 cbCompressed, void * pDestBuffer, uint32 cbDestBufferSize, uint32 * nBytesWritten, uint32 nDesiredSampleRate)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pCompressed);
    STAR_UNREFERENCED(cbCompressed);
    STAR_UNREFERENCED(pDestBuffer);
    STAR_UNREFERENCED(cbDestBufferSize);
    STAR_UNREFERENCED(nBytesWritten);
    STAR_UNREFERENCED(nDesiredSampleRate);
    return {};
}

STAR_EXPORT HAuthTicket SteamAPI_ISteamUser_GetAuthSessionTicket(ISteamUser* self, void * pTicket, int cbMaxTicket, uint32 * pcbTicket, const SteamNetworkingIdentity * pSteamNetworkingIdentity)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pTicket);
    STAR_UNREFERENCED(cbMaxTicket);
    STAR_UNREFERENCED(pcbTicket);
    STAR_UNREFERENCED(pSteamNetworkingIdentity);
    return {};
}

STAR_EXPORT HAuthTicket SteamAPI_ISteamUser_GetAuthTicketForWebApi(ISteamUser* self, const char * pchIdentity)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchIdentity);
    return {};
}

STAR_EXPORT EBeginAuthSessionResult SteamAPI_ISteamUser_BeginAuthSession(ISteamUser* self, const void * pAuthTicket, int cbAuthTicket, uint64_steamid steamID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pAuthTicket);
    STAR_UNREFERENCED(cbAuthTicket);
    STAR_UNREFERENCED(steamID);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamUser_EndAuthSession(ISteamUser* self, uint64_steamid steamID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
}

STAR_EXPORT void SteamAPI_ISteamUser_CancelAuthTicket(ISteamUser* self, HAuthTicket hAuthTicket)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hAuthTicket);
}

STAR_EXPORT EUserHasLicenseForAppResult SteamAPI_ISteamUser_UserHasLicenseForApp(ISteamUser* self, uint64_steamid steamID, AppId_t appID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
    STAR_UNREFERENCED(appID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUser_BIsBehindNAT(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamUser_AdvertiseGame(ISteamUser* self, uint64_steamid steamIDGameServer, uint32 unIPServer, uint16 usPortServer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDGameServer);
    STAR_UNREFERENCED(unIPServer);
    STAR_UNREFERENCED(usPortServer);
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUser_RequestEncryptedAppTicket(ISteamUser* self, void * pDataToInclude, int cbDataToInclude)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pDataToInclude);
    STAR_UNREFERENCED(cbDataToInclude);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUser_GetEncryptedAppTicket(ISteamUser* self, void * pTicket, int cbMaxTicket, uint32 * pcbTicket)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pTicket);
    STAR_UNREFERENCED(cbMaxTicket);
    STAR_UNREFERENCED(pcbTicket);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamUser_GetGameBadgeLevel(ISteamUser* self, int nSeries, bool bFoil)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nSeries);
    STAR_UNREFERENCED(bFoil);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamUser_GetPlayerSteamLevel(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUser_RequestStoreAuthURL(ISteamUser* self, const char * pchRedirectURL)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchRedirectURL);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUser_BIsPhoneVerified(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUser_BIsTwoFactorEnabled(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUser_BIsPhoneIdentifying(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUser_BIsPhoneRequiringVerification(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUser_GetMarketEligibility(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUser_GetDurationControl(ISteamUser* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUser_BSetDurationControlOnlineState(ISteamUser* self, EDurationControlOnlineState eNewState)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eNewState);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamFriends_SetPersonaName(ISteamFriends* self, const char * pchPersonaName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchPersonaName);
    return {};
}

STAR_EXPORT EPersonaState SteamAPI_ISteamFriends_GetPersonaState(ISteamFriends* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetFriendCount(ISteamFriends* self, int iFriendFlags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iFriendFlags);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamFriends_GetFriendByIndex(ISteamFriends* self, int iFriend, int iFriendFlags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iFriend);
    STAR_UNREFERENCED(iFriendFlags);
    return {};
}

STAR_EXPORT EFriendRelationship SteamAPI_ISteamFriends_GetFriendRelationship(ISteamFriends* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    return {};
}

STAR_EXPORT EPersonaState SteamAPI_ISteamFriends_GetFriendPersonaState(ISteamFriends* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_GetFriendGamePlayed(ISteamFriends* self, uint64_steamid steamIDFriend, FriendGameInfo_t * pFriendGameInfo)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    STAR_UNREFERENCED(pFriendGameInfo);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamFriends_GetFriendPersonaNameHistory(ISteamFriends* self, uint64_steamid steamIDFriend, int iPersonaName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    STAR_UNREFERENCED(iPersonaName);
    return "";
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetFriendSteamLevel(ISteamFriends* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamFriends_GetPlayerNickname(ISteamFriends* self, uint64_steamid steamIDPlayer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDPlayer);
    return "";
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetFriendsGroupCount(ISteamFriends* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT FriendsGroupID_t SteamAPI_ISteamFriends_GetFriendsGroupIDByIndex(ISteamFriends* self, int iFG)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iFG);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamFriends_GetFriendsGroupName(ISteamFriends* self, FriendsGroupID_t friendsGroupID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(friendsGroupID);
    return "";
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetFriendsGroupMembersCount(ISteamFriends* self, FriendsGroupID_t friendsGroupID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(friendsGroupID);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamFriends_GetFriendsGroupMembersList(ISteamFriends* self, FriendsGroupID_t friendsGroupID, CSteamID * pOutSteamIDMembers, int nMembersCount)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(friendsGroupID);
    STAR_UNREFERENCED(pOutSteamIDMembers);
    STAR_UNREFERENCED(nMembersCount);
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetClanCount(ISteamFriends* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamFriends_GetClanByIndex(ISteamFriends* self, int iClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iClan);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamFriends_GetClanName(ISteamFriends* self, uint64_steamid steamIDClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    return "";
}

STAR_EXPORT const char * SteamAPI_ISteamFriends_GetClanTag(ISteamFriends* self, uint64_steamid steamIDClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    return "";
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_GetClanActivityCounts(ISteamFriends* self, uint64_steamid steamIDClan, int * pnOnline, int * pnInGame, int * pnChatting)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    STAR_UNREFERENCED(pnOnline);
    STAR_UNREFERENCED(pnInGame);
    STAR_UNREFERENCED(pnChatting);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamFriends_DownloadClanActivityCounts(ISteamFriends* self, CSteamID * psteamIDClans, int cClansToRequest)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(psteamIDClans);
    STAR_UNREFERENCED(cClansToRequest);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetFriendCountFromSource(ISteamFriends* self, uint64_steamid steamIDSource)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDSource);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamFriends_GetFriendFromSourceByIndex(ISteamFriends* self, uint64_steamid steamIDSource, int iFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDSource);
    STAR_UNREFERENCED(iFriend);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_IsUserInSource(ISteamFriends* self, uint64_steamid steamIDUser, uint64_steamid steamIDSource)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(steamIDSource);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamFriends_SetInGameVoiceSpeaking(ISteamFriends* self, uint64_steamid steamIDUser, bool bSpeaking)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(bSpeaking);
}

STAR_EXPORT void SteamAPI_ISteamFriends_ActivateGameOverlayToUser(ISteamFriends* self, const char * pchDialog, uint64_steamid steamID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchDialog);
    STAR_UNREFERENCED(steamID);
}

STAR_EXPORT void SteamAPI_ISteamFriends_ActivateGameOverlayToStore(ISteamFriends* self, AppId_t nAppID, EOverlayToStoreFlag eFlag)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
    STAR_UNREFERENCED(eFlag);
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetSmallFriendAvatar(ISteamFriends* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetMediumFriendAvatar(ISteamFriends* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetLargeFriendAvatar(ISteamFriends* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_RequestUserInformation(ISteamFriends* self, uint64_steamid steamIDUser, bool bRequireNameOnly)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(bRequireNameOnly);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamFriends_RequestClanOfficerList(ISteamFriends* self, uint64_steamid steamIDClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamFriends_GetClanOwner(ISteamFriends* self, uint64_steamid steamIDClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetClanOfficerCount(ISteamFriends* self, uint64_steamid steamIDClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamFriends_GetClanOfficerByIndex(ISteamFriends* self, uint64_steamid steamIDClan, int iOfficer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    STAR_UNREFERENCED(iOfficer);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamFriends_GetUserRestrictions(ISteamFriends* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamFriends_ClearRichPresence(ISteamFriends* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT const char * SteamAPI_ISteamFriends_GetFriendRichPresence(ISteamFriends* self, uint64_steamid steamIDFriend, const char * pchKey)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    STAR_UNREFERENCED(pchKey);
    return "";
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetFriendRichPresenceKeyCount(ISteamFriends* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamFriends_GetFriendRichPresenceKeyByIndex(ISteamFriends* self, uint64_steamid steamIDFriend, int iKey)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    STAR_UNREFERENCED(iKey);
    return "";
}

STAR_EXPORT void SteamAPI_ISteamFriends_RequestFriendRichPresence(ISteamFriends* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_InviteUserToGame(ISteamFriends* self, uint64_steamid steamIDFriend, const char * pchConnectString)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    STAR_UNREFERENCED(pchConnectString);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetCoplayFriendCount(ISteamFriends* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamFriends_GetCoplayFriend(ISteamFriends* self, int iCoplayFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iCoplayFriend);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetFriendCoplayTime(ISteamFriends* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    return {};
}

STAR_EXPORT AppId_t SteamAPI_ISteamFriends_GetFriendCoplayGame(ISteamFriends* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamFriends_JoinClanChatRoom(ISteamFriends* self, uint64_steamid steamIDClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_LeaveClanChatRoom(ISteamFriends* self, uint64_steamid steamIDClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetClanChatMemberCount(ISteamFriends* self, uint64_steamid steamIDClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamFriends_GetChatMemberByIndex(ISteamFriends* self, uint64_steamid steamIDClan, int iUser)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    STAR_UNREFERENCED(iUser);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_SendClanChatMessage(ISteamFriends* self, uint64_steamid steamIDClanChat, const char * pchText)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClanChat);
    STAR_UNREFERENCED(pchText);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetClanChatMessage(ISteamFriends* self, uint64_steamid steamIDClanChat, int iMessage, void * prgchText, int cchTextMax, EChatEntryType * peChatEntryType, CSteamID * psteamidChatter)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClanChat);
    STAR_UNREFERENCED(iMessage);
    STAR_UNREFERENCED(prgchText);
    STAR_UNREFERENCED(cchTextMax);
    STAR_UNREFERENCED(peChatEntryType);
    STAR_UNREFERENCED(psteamidChatter);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_IsClanChatAdmin(ISteamFriends* self, uint64_steamid steamIDClanChat, uint64_steamid steamIDUser)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClanChat);
    STAR_UNREFERENCED(steamIDUser);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_IsClanChatWindowOpenInSteam(ISteamFriends* self, uint64_steamid steamIDClanChat)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClanChat);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_OpenClanChatWindowInSteam(ISteamFriends* self, uint64_steamid steamIDClanChat)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClanChat);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_CloseClanChatWindowInSteam(ISteamFriends* self, uint64_steamid steamIDClanChat)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClanChat);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_SetListenForFriendsMessages(ISteamFriends* self, bool bInterceptEnabled)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bInterceptEnabled);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_ReplyToFriendMessage(ISteamFriends* self, uint64_steamid steamIDFriend, const char * pchMsgToSend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    STAR_UNREFERENCED(pchMsgToSend);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamFriends_GetFollowerCount(ISteamFriends* self, uint64_steamid steamID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamFriends_IsFollowing(ISteamFriends* self, uint64_steamid steamID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamFriends_EnumerateFollowingList(ISteamFriends* self, uint32 unStartIndex)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unStartIndex);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_IsClanPublic(ISteamFriends* self, uint64_steamid steamIDClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_IsClanOfficialGameGroup(ISteamFriends* self, uint64_steamid steamIDClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamFriends_GetNumChatsWithUnreadPriorityMessages(ISteamFriends* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamFriends_ActivateGameOverlayRemotePlayTogetherInviteDialog(ISteamFriends* self, uint64_steamid steamIDLobby)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_RegisterProtocolInOverlayBrowser(ISteamFriends* self, const char * pchProtocol)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchProtocol);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamFriends_RequestEquippedProfileItems(ISteamFriends* self, uint64_steamid steamID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamFriends_BHasEquippedProfileItem(ISteamFriends* self, uint64_steamid steamID, ECommunityProfileItemType itemType)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
    STAR_UNREFERENCED(itemType);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamFriends_GetProfileItemPropertyString(ISteamFriends* self, uint64_steamid steamID, ECommunityProfileItemType itemType, ECommunityProfileItemProperty prop)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
    STAR_UNREFERENCED(itemType);
    STAR_UNREFERENCED(prop);
    return "";
}

STAR_EXPORT uint32 SteamAPI_ISteamFriends_GetProfileItemPropertyUint(ISteamFriends* self, uint64_steamid steamID, ECommunityProfileItemType itemType, ECommunityProfileItemProperty prop)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
    STAR_UNREFERENCED(itemType);
    STAR_UNREFERENCED(prop);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamUtils_GetSecondsSinceAppActive(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamUtils_GetSecondsSinceComputerActive(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT EUniverse SteamAPI_ISteamUtils_GetConnectedUniverse(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamUtils_GetServerRealTime(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_GetImageSize(ISteamUtils* self, int iImage, uint32 * pnWidth, uint32 * pnHeight)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iImage);
    STAR_UNREFERENCED(pnWidth);
    STAR_UNREFERENCED(pnHeight);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_GetImageRGBA(ISteamUtils* self, int iImage, uint8 * pubDest, int nDestBufferSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iImage);
    STAR_UNREFERENCED(pubDest);
    STAR_UNREFERENCED(nDestBufferSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_GetCSERIPPort(ISteamUtils* self, uint32 * unIP, uint16 * usPort)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unIP);
    STAR_UNREFERENCED(usPort);
    return {};
}

STAR_EXPORT uint8 SteamAPI_ISteamUtils_GetCurrentBatteryPower(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamUtils_SetOverlayNotificationPosition(ISteamUtils* self, ENotificationPosition eNotificationPosition)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eNotificationPosition);
}

STAR_EXPORT uint32 SteamAPI_ISteamUtils_GetIPCCallCount(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_IsOverlayEnabled(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_BOverlayNeedsPresent(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUtils_CheckFileSignature(ISteamUtils* self, const char * szFileName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(szFileName);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_ShowGamepadTextInput(ISteamUtils* self, EGamepadTextInputMode eInputMode, EGamepadTextInputLineMode eLineInputMode, const char * pchDescription, uint32 unCharMax, const char * pchExistingText)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eInputMode);
    STAR_UNREFERENCED(eLineInputMode);
    STAR_UNREFERENCED(pchDescription);
    STAR_UNREFERENCED(unCharMax);
    STAR_UNREFERENCED(pchExistingText);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamUtils_GetEnteredGamepadTextLength(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_GetEnteredGamepadTextInput(ISteamUtils* self, char * pchText, uint32 cchText)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchText);
    STAR_UNREFERENCED(cchText);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamUtils_GetSteamUILanguage(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return "";
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_IsSteamRunningInVR(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamUtils_SetOverlayNotificationInset(ISteamUtils* self, int nHorizontalInset, int nVerticalInset)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nHorizontalInset);
    STAR_UNREFERENCED(nVerticalInset);
}

STAR_EXPORT void SteamAPI_ISteamUtils_StartVRDashboard(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_IsVRHeadsetStreamingEnabled(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamUtils_SetVRHeadsetStreamingEnabled(ISteamUtils* self, bool bEnabled)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bEnabled);
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_IsSteamChinaLauncher(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_InitFilterText(ISteamUtils* self, uint32 unFilterOptions)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unFilterOptions);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamUtils_FilterText(ISteamUtils* self, ETextFilteringContext eContext, uint64_steamid sourceSteamID, const char * pchInputMessage, char * pchOutFilteredText, uint32 nByteSizeOutFilteredText)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eContext);
    STAR_UNREFERENCED(sourceSteamID);
    STAR_UNREFERENCED(pchInputMessage);
    STAR_UNREFERENCED(pchOutFilteredText);
    STAR_UNREFERENCED(nByteSizeOutFilteredText);
    return {};
}

STAR_EXPORT ESteamIPv6ConnectivityState SteamAPI_ISteamUtils_GetIPv6ConnectivityState(ISteamUtils* self, ESteamIPv6ConnectivityProtocol eProtocol)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eProtocol);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_ShowModalGamepadTextInput(ISteamUtils* self, EGamepadTextInputLineMode eLineInputMode)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eLineInputMode);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamUtils_SetGameLauncherMode(ISteamUtils* self, bool bLauncherMode)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bLauncherMode);
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_DismissFloatingGamepadTextInput(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUtils_DismissGamepadTextInput(ISteamUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamMatchmaking_GetFavoriteGameCount(ISteamMatchmaking* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_GetFavoriteGame(ISteamMatchmaking* self, int iGame, AppId_t * pnAppID, uint32 * pnIP, uint16 * pnConnPort, uint16 * pnQueryPort, uint32 * punFlags, uint32 * pRTime32LastPlayedOnServer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iGame);
    STAR_UNREFERENCED(pnAppID);
    STAR_UNREFERENCED(pnIP);
    STAR_UNREFERENCED(pnConnPort);
    STAR_UNREFERENCED(pnQueryPort);
    STAR_UNREFERENCED(punFlags);
    STAR_UNREFERENCED(pRTime32LastPlayedOnServer);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamMatchmaking_AddFavoriteGame(ISteamMatchmaking* self, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
    STAR_UNREFERENCED(nIP);
    STAR_UNREFERENCED(nConnPort);
    STAR_UNREFERENCED(nQueryPort);
    STAR_UNREFERENCED(unFlags);
    STAR_UNREFERENCED(rTime32LastPlayedOnServer);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_RemoveFavoriteGame(ISteamMatchmaking* self, AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
    STAR_UNREFERENCED(nIP);
    STAR_UNREFERENCED(nConnPort);
    STAR_UNREFERENCED(nQueryPort);
    STAR_UNREFERENCED(unFlags);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamMatchmaking_RequestLobbyList(ISteamMatchmaking* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamMatchmaking_AddRequestLobbyListStringFilter(ISteamMatchmaking* self, const char * pchKeyToMatch, const char * pchValueToMatch, ELobbyComparison eComparisonType)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchKeyToMatch);
    STAR_UNREFERENCED(pchValueToMatch);
    STAR_UNREFERENCED(eComparisonType);
}

STAR_EXPORT void SteamAPI_ISteamMatchmaking_AddRequestLobbyListNumericalFilter(ISteamMatchmaking* self, const char * pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchKeyToMatch);
    STAR_UNREFERENCED(nValueToMatch);
    STAR_UNREFERENCED(eComparisonType);
}

STAR_EXPORT void SteamAPI_ISteamMatchmaking_AddRequestLobbyListNearValueFilter(ISteamMatchmaking* self, const char * pchKeyToMatch, int nValueToBeCloseTo)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchKeyToMatch);
    STAR_UNREFERENCED(nValueToBeCloseTo);
}

STAR_EXPORT void SteamAPI_ISteamMatchmaking_AddRequestLobbyListFilterSlotsAvailable(ISteamMatchmaking* self, int nSlotsAvailable)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nSlotsAvailable);
}

STAR_EXPORT void SteamAPI_ISteamMatchmaking_AddRequestLobbyListDistanceFilter(ISteamMatchmaking* self, ELobbyDistanceFilter eLobbyDistanceFilter)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eLobbyDistanceFilter);
}

STAR_EXPORT void SteamAPI_ISteamMatchmaking_AddRequestLobbyListResultCountFilter(ISteamMatchmaking* self, int cMaxResults)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(cMaxResults);
}

STAR_EXPORT void SteamAPI_ISteamMatchmaking_AddRequestLobbyListCompatibleMembersFilter(ISteamMatchmaking* self, uint64_steamid steamIDLobby)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamMatchmaking_GetLobbyByIndex(ISteamMatchmaking* self, int iLobby)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iLobby);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamMatchmaking_CreateLobby(ISteamMatchmaking* self, ELobbyType eLobbyType, int cMaxMembers)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eLobbyType);
    STAR_UNREFERENCED(cMaxMembers);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamMatchmaking_JoinLobby(ISteamMatchmaking* self, uint64_steamid steamIDLobby)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamMatchmaking_LeaveLobby(ISteamMatchmaking* self, uint64_steamid steamIDLobby)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_InviteUserToLobby(ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint64_steamid steamIDInvitee)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(steamIDInvitee);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamMatchmaking_GetNumLobbyMembers(ISteamMatchmaking* self, uint64_steamid steamIDLobby)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamMatchmaking_GetLobbyMemberByIndex(ISteamMatchmaking* self, uint64_steamid steamIDLobby, int iMember)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(iMember);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamMatchmaking_GetLobbyData(ISteamMatchmaking* self, uint64_steamid steamIDLobby, const char * pchKey)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(pchKey);
    return "";
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_SetLobbyData(ISteamMatchmaking* self, uint64_steamid steamIDLobby, const char * pchKey, const char * pchValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(pchKey);
    STAR_UNREFERENCED(pchValue);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamMatchmaking_GetLobbyDataCount(ISteamMatchmaking* self, uint64_steamid steamIDLobby)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_GetLobbyDataByIndex(ISteamMatchmaking* self, uint64_steamid steamIDLobby, int iLobbyData, char * pchKey, int cchKeyBufferSize, char * pchValue, int cchValueBufferSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(iLobbyData);
    STAR_UNREFERENCED(pchKey);
    STAR_UNREFERENCED(cchKeyBufferSize);
    STAR_UNREFERENCED(pchValue);
    STAR_UNREFERENCED(cchValueBufferSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_DeleteLobbyData(ISteamMatchmaking* self, uint64_steamid steamIDLobby, const char * pchKey)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(pchKey);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamMatchmaking_GetLobbyMemberData(ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint64_steamid steamIDUser, const char * pchKey)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchKey);
    return "";
}

STAR_EXPORT void SteamAPI_ISteamMatchmaking_SetLobbyMemberData(ISteamMatchmaking* self, uint64_steamid steamIDLobby, const char * pchKey, const char * pchValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(pchKey);
    STAR_UNREFERENCED(pchValue);
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_SendLobbyChatMsg(ISteamMatchmaking* self, uint64_steamid steamIDLobby, const void * pvMsgBody, int cubMsgBody)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(pvMsgBody);
    STAR_UNREFERENCED(cubMsgBody);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_RequestLobbyData(ISteamMatchmaking* self, uint64_steamid steamIDLobby)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamMatchmaking_SetLobbyGameServer(ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, uint64_steamid steamIDGameServer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(unGameServerIP);
    STAR_UNREFERENCED(unGameServerPort);
    STAR_UNREFERENCED(steamIDGameServer);
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_GetLobbyGameServer(ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint32 * punGameServerIP, uint16 * punGameServerPort, CSteamID * psteamIDGameServer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(punGameServerIP);
    STAR_UNREFERENCED(punGameServerPort);
    STAR_UNREFERENCED(psteamIDGameServer);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_SetLobbyMemberLimit(ISteamMatchmaking* self, uint64_steamid steamIDLobby, int cMaxMembers)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(cMaxMembers);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamMatchmaking_GetLobbyMemberLimit(ISteamMatchmaking* self, uint64_steamid steamIDLobby)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_SetLobbyType(ISteamMatchmaking* self, uint64_steamid steamIDLobby, ELobbyType eLobbyType)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(eLobbyType);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_SetLobbyJoinable(ISteamMatchmaking* self, uint64_steamid steamIDLobby, bool bLobbyJoinable)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(bLobbyJoinable);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamMatchmaking_GetLobbyOwner(ISteamMatchmaking* self, uint64_steamid steamIDLobby)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_SetLobbyOwner(ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint64_steamid steamIDNewOwner)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(steamIDNewOwner);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmaking_SetLinkedLobby(ISteamMatchmaking* self, uint64_steamid steamIDLobby, uint64_steamid steamIDLobbyDependent)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(steamIDLobbyDependent);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingServerListResponse_ServerResponded(ISteamMatchmakingServerListResponse* self, HServerListRequest hRequest, int iServer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(iServer);
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingServerListResponse_ServerFailedToRespond(ISteamMatchmakingServerListResponse* self, HServerListRequest hRequest, int iServer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(iServer);
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingServerListResponse_RefreshComplete(ISteamMatchmakingServerListResponse* self, HServerListRequest hRequest, EMatchMakingServerResponse response)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(response);
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingPingResponse_ServerResponded(ISteamMatchmakingPingResponse* self, gameserveritem_t & server)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(server);
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingPingResponse_ServerFailedToRespond(ISteamMatchmakingPingResponse* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingPlayersResponse_AddPlayerToList(ISteamMatchmakingPlayersResponse* self, const char * pchName, int nScore, float flTimePlayed)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(nScore);
    STAR_UNREFERENCED(flTimePlayed);
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingPlayersResponse_PlayersFailedToRespond(ISteamMatchmakingPlayersResponse* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingPlayersResponse_PlayersRefreshComplete(ISteamMatchmakingPlayersResponse* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingRulesResponse_RulesResponded(ISteamMatchmakingRulesResponse* self, const char * pchRule, const char * pchValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchRule);
    STAR_UNREFERENCED(pchValue);
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingRulesResponse_RulesFailedToRespond(ISteamMatchmakingRulesResponse* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingRulesResponse_RulesRefreshComplete(ISteamMatchmakingRulesResponse* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT HServerListRequest SteamAPI_ISteamMatchmakingServers_RequestInternetServerList(ISteamMatchmakingServers* self, AppId_t iApp, MatchMakingKeyValuePair_t ** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse * pRequestServersResponse)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iApp);
    STAR_UNREFERENCED(ppchFilters);
    STAR_UNREFERENCED(nFilters);
    STAR_UNREFERENCED(pRequestServersResponse);
    return {};
}

STAR_EXPORT HServerListRequest SteamAPI_ISteamMatchmakingServers_RequestLANServerList(ISteamMatchmakingServers* self, AppId_t iApp, ISteamMatchmakingServerListResponse * pRequestServersResponse)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iApp);
    STAR_UNREFERENCED(pRequestServersResponse);
    return {};
}

STAR_EXPORT HServerListRequest SteamAPI_ISteamMatchmakingServers_RequestFriendsServerList(ISteamMatchmakingServers* self, AppId_t iApp, MatchMakingKeyValuePair_t ** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse * pRequestServersResponse)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iApp);
    STAR_UNREFERENCED(ppchFilters);
    STAR_UNREFERENCED(nFilters);
    STAR_UNREFERENCED(pRequestServersResponse);
    return {};
}

STAR_EXPORT HServerListRequest SteamAPI_ISteamMatchmakingServers_RequestFavoritesServerList(ISteamMatchmakingServers* self, AppId_t iApp, MatchMakingKeyValuePair_t ** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse * pRequestServersResponse)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iApp);
    STAR_UNREFERENCED(ppchFilters);
    STAR_UNREFERENCED(nFilters);
    STAR_UNREFERENCED(pRequestServersResponse);
    return {};
}

STAR_EXPORT HServerListRequest SteamAPI_ISteamMatchmakingServers_RequestHistoryServerList(ISteamMatchmakingServers* self, AppId_t iApp, MatchMakingKeyValuePair_t ** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse * pRequestServersResponse)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iApp);
    STAR_UNREFERENCED(ppchFilters);
    STAR_UNREFERENCED(nFilters);
    STAR_UNREFERENCED(pRequestServersResponse);
    return {};
}

STAR_EXPORT HServerListRequest SteamAPI_ISteamMatchmakingServers_RequestSpectatorServerList(ISteamMatchmakingServers* self, AppId_t iApp, MatchMakingKeyValuePair_t ** ppchFilters, uint32 nFilters, ISteamMatchmakingServerListResponse * pRequestServersResponse)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iApp);
    STAR_UNREFERENCED(ppchFilters);
    STAR_UNREFERENCED(nFilters);
    STAR_UNREFERENCED(pRequestServersResponse);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingServers_ReleaseRequest(ISteamMatchmakingServers* self, HServerListRequest hServerListRequest)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hServerListRequest);
}

STAR_EXPORT gameserveritem_t * SteamAPI_ISteamMatchmakingServers_GetServerDetails(ISteamMatchmakingServers* self, HServerListRequest hRequest, int iServer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(iServer);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingServers_CancelQuery(ISteamMatchmakingServers* self, HServerListRequest hRequest)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingServers_RefreshQuery(ISteamMatchmakingServers* self, HServerListRequest hRequest)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
}

STAR_EXPORT steam_bool SteamAPI_ISteamMatchmakingServers_IsRefreshing(ISteamMatchmakingServers* self, HServerListRequest hRequest)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamMatchmakingServers_GetServerCount(ISteamMatchmakingServers* self, HServerListRequest hRequest)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingServers_RefreshServer(ISteamMatchmakingServers* self, HServerListRequest hRequest, int iServer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(iServer);
}

STAR_EXPORT HServerQuery SteamAPI_ISteamMatchmakingServers_PingServer(ISteamMatchmakingServers* self, uint32 unIP, uint16 usPort, ISteamMatchmakingPingResponse * pRequestServersResponse)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unIP);
    STAR_UNREFERENCED(usPort);
    STAR_UNREFERENCED(pRequestServersResponse);
    return {};
}

STAR_EXPORT HServerQuery SteamAPI_ISteamMatchmakingServers_PlayerDetails(ISteamMatchmakingServers* self, uint32 unIP, uint16 usPort, ISteamMatchmakingPlayersResponse * pRequestServersResponse)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unIP);
    STAR_UNREFERENCED(usPort);
    STAR_UNREFERENCED(pRequestServersResponse);
    return {};
}

STAR_EXPORT HServerQuery SteamAPI_ISteamMatchmakingServers_ServerRules(ISteamMatchmakingServers* self, uint32 unIP, uint16 usPort, ISteamMatchmakingRulesResponse * pRequestServersResponse)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unIP);
    STAR_UNREFERENCED(usPort);
    STAR_UNREFERENCED(pRequestServersResponse);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamMatchmakingServers_CancelServerQuery(ISteamMatchmakingServers* self, HServerQuery hServerQuery)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hServerQuery);
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_AddGameSearchParams(ISteamGameSearch* self, const char * pchKeyToFind, const char * pchValuesToFind)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchKeyToFind);
    STAR_UNREFERENCED(pchValuesToFind);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_SearchForGameWithLobby(ISteamGameSearch* self, uint64_steamid steamIDLobby, int nPlayerMin, int nPlayerMax)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDLobby);
    STAR_UNREFERENCED(nPlayerMin);
    STAR_UNREFERENCED(nPlayerMax);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_SearchForGameSolo(ISteamGameSearch* self, int nPlayerMin, int nPlayerMax)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nPlayerMin);
    STAR_UNREFERENCED(nPlayerMax);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_AcceptGame(ISteamGameSearch* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_DeclineGame(ISteamGameSearch* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_RetrieveConnectionDetails(ISteamGameSearch* self, uint64_steamid steamIDHost, char * pchConnectionDetails, int cubConnectionDetails)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDHost);
    STAR_UNREFERENCED(pchConnectionDetails);
    STAR_UNREFERENCED(cubConnectionDetails);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_EndGameSearch(ISteamGameSearch* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_SetGameHostParams(ISteamGameSearch* self, const char * pchKey, const char * pchValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchKey);
    STAR_UNREFERENCED(pchValue);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_SetConnectionDetails(ISteamGameSearch* self, const char * pchConnectionDetails, int cubConnectionDetails)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchConnectionDetails);
    STAR_UNREFERENCED(cubConnectionDetails);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_RequestPlayersForGame(ISteamGameSearch* self, int nPlayerMin, int nPlayerMax, int nMaxTeamSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nPlayerMin);
    STAR_UNREFERENCED(nPlayerMax);
    STAR_UNREFERENCED(nMaxTeamSize);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_HostConfirmGameStart(ISteamGameSearch* self, uint64 ullUniqueGameID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ullUniqueGameID);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_CancelRequestPlayersForGame(ISteamGameSearch* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_SubmitPlayerResult(ISteamGameSearch* self, uint64 ullUniqueGameID, uint64_steamid steamIDPlayer, EPlayerResult_t EPlayerResult)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ullUniqueGameID);
    STAR_UNREFERENCED(steamIDPlayer);
    STAR_UNREFERENCED(EPlayerResult);
    return {};
}

STAR_EXPORT EGameSearchErrorCode_t SteamAPI_ISteamGameSearch_EndGame(ISteamGameSearch* self, uint64 ullUniqueGameID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ullUniqueGameID);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamParties_GetNumActiveBeacons(ISteamParties* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT PartyBeaconID_t SteamAPI_ISteamParties_GetBeaconByIndex(ISteamParties* self, uint32 unIndex)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unIndex);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamParties_GetBeaconDetails(ISteamParties* self, PartyBeaconID_t ulBeaconID, CSteamID * pSteamIDBeaconOwner, SteamPartyBeaconLocation_t * pLocation, char * pchMetadata, int cchMetadata)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulBeaconID);
    STAR_UNREFERENCED(pSteamIDBeaconOwner);
    STAR_UNREFERENCED(pLocation);
    STAR_UNREFERENCED(pchMetadata);
    STAR_UNREFERENCED(cchMetadata);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamParties_JoinParty(ISteamParties* self, PartyBeaconID_t ulBeaconID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulBeaconID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamParties_GetNumAvailableBeaconLocations(ISteamParties* self, uint32 * puNumLocations)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(puNumLocations);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamParties_GetAvailableBeaconLocations(ISteamParties* self, SteamPartyBeaconLocation_t * pLocationList, uint32 uMaxNumLocations)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pLocationList);
    STAR_UNREFERENCED(uMaxNumLocations);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamParties_CreateBeacon(ISteamParties* self, uint32 unOpenSlots, SteamPartyBeaconLocation_t * pBeaconLocation, const char * pchConnectString, const char * pchMetadata)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unOpenSlots);
    STAR_UNREFERENCED(pBeaconLocation);
    STAR_UNREFERENCED(pchConnectString);
    STAR_UNREFERENCED(pchMetadata);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamParties_OnReservationCompleted(ISteamParties* self, PartyBeaconID_t ulBeacon, uint64_steamid steamIDUser)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulBeacon);
    STAR_UNREFERENCED(steamIDUser);
}

STAR_EXPORT void SteamAPI_ISteamParties_CancelReservation(ISteamParties* self, PartyBeaconID_t ulBeacon, uint64_steamid steamIDUser)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulBeacon);
    STAR_UNREFERENCED(steamIDUser);
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamParties_ChangeNumOpenSlots(ISteamParties* self, PartyBeaconID_t ulBeacon, uint32 unOpenSlots)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulBeacon);
    STAR_UNREFERENCED(unOpenSlots);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamParties_DestroyBeacon(ISteamParties* self, PartyBeaconID_t ulBeacon)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulBeacon);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamParties_GetBeaconLocationData(ISteamParties* self, SteamPartyBeaconLocation_t BeaconLocation, ESteamPartyBeaconLocationData eData, char * pchDataStringOut, int cchDataStringOut)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(BeaconLocation);
    STAR_UNREFERENCED(eData);
    STAR_UNREFERENCED(pchDataStringOut);
    STAR_UNREFERENCED(cchDataStringOut);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_FileForget(ISteamRemoteStorage* self, const char * pchFile)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchFile);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_FileShare(ISteamRemoteStorage* self, const char * pchFile)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchFile);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_SetSyncPlatforms(ISteamRemoteStorage* self, const char * pchFile, ERemoteStoragePlatform eRemoteStoragePlatform)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchFile);
    STAR_UNREFERENCED(eRemoteStoragePlatform);
    return {};
}

STAR_EXPORT UGCFileWriteStreamHandle_t SteamAPI_ISteamRemoteStorage_FileWriteStreamOpen(ISteamRemoteStorage* self, const char * pchFile)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchFile);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_FileWriteStreamWriteChunk(ISteamRemoteStorage* self, UGCFileWriteStreamHandle_t writeHandle, const void * pvData, int32 cubData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(writeHandle);
    STAR_UNREFERENCED(pvData);
    STAR_UNREFERENCED(cubData);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_FileWriteStreamClose(ISteamRemoteStorage* self, UGCFileWriteStreamHandle_t writeHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(writeHandle);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_FileWriteStreamCancel(ISteamRemoteStorage* self, UGCFileWriteStreamHandle_t writeHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(writeHandle);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_FilePersisted(ISteamRemoteStorage* self, const char * pchFile)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchFile);
    return {};
}

STAR_EXPORT int64 SteamAPI_ISteamRemoteStorage_GetFileTimestamp(ISteamRemoteStorage* self, const char * pchFile)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchFile);
    return {};
}

STAR_EXPORT ERemoteStoragePlatform SteamAPI_ISteamRemoteStorage_GetSyncPlatforms(ISteamRemoteStorage* self, const char * pchFile)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchFile);
    return {};
}

STAR_EXPORT int32 SteamAPI_ISteamRemoteStorage_GetFileCount(ISteamRemoteStorage* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamRemoteStorage_GetFileNameAndSize(ISteamRemoteStorage* self, int iFile, int32 * pnFileSizeInBytes)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iFile);
    STAR_UNREFERENCED(pnFileSizeInBytes);
    return "";
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_UGCDownload(ISteamRemoteStorage* self, UGCHandle_t hContent, uint32 unPriority)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hContent);
    STAR_UNREFERENCED(unPriority);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_GetUGCDownloadProgress(ISteamRemoteStorage* self, UGCHandle_t hContent, int32 * pnBytesDownloaded, int32 * pnBytesExpected)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hContent);
    STAR_UNREFERENCED(pnBytesDownloaded);
    STAR_UNREFERENCED(pnBytesExpected);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_GetUGCDetails(ISteamRemoteStorage* self, UGCHandle_t hContent, AppId_t * pnAppID, char ** ppchName, int32 * pnFileSizeInBytes, CSteamID * pSteamIDOwner)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hContent);
    STAR_UNREFERENCED(pnAppID);
    STAR_UNREFERENCED(ppchName);
    STAR_UNREFERENCED(pnFileSizeInBytes);
    STAR_UNREFERENCED(pSteamIDOwner);
    return {};
}

STAR_EXPORT int32 SteamAPI_ISteamRemoteStorage_UGCRead(ISteamRemoteStorage* self, UGCHandle_t hContent, void * pvData, int32 cubDataToRead, uint32 cOffset, EUGCReadAction eAction)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hContent);
    STAR_UNREFERENCED(pvData);
    STAR_UNREFERENCED(cubDataToRead);
    STAR_UNREFERENCED(cOffset);
    STAR_UNREFERENCED(eAction);
    return {};
}

STAR_EXPORT int32 SteamAPI_ISteamRemoteStorage_GetCachedUGCCount(ISteamRemoteStorage* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT UGCHandle_t SteamAPI_ISteamRemoteStorage_GetCachedUGCHandle(ISteamRemoteStorage* self, int32 iCachedContent)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iCachedContent);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_PublishWorkshopFile(ISteamRemoteStorage* self, const char * pchFile, const char * pchPreviewFile, AppId_t nConsumerAppId, const char * pchTitle, const char * pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t * pTags, EWorkshopFileType eWorkshopFileType)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchFile);
    STAR_UNREFERENCED(pchPreviewFile);
    STAR_UNREFERENCED(nConsumerAppId);
    STAR_UNREFERENCED(pchTitle);
    STAR_UNREFERENCED(pchDescription);
    STAR_UNREFERENCED(eVisibility);
    STAR_UNREFERENCED(pTags);
    STAR_UNREFERENCED(eWorkshopFileType);
    return {};
}

STAR_EXPORT PublishedFileUpdateHandle_t SteamAPI_ISteamRemoteStorage_CreatePublishedFileUpdateRequest(ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unPublishedFileId);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_UpdatePublishedFileFile(ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, const char * pchFile)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(updateHandle);
    STAR_UNREFERENCED(pchFile);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_UpdatePublishedFilePreviewFile(ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, const char * pchPreviewFile)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(updateHandle);
    STAR_UNREFERENCED(pchPreviewFile);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTitle(ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, const char * pchTitle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(updateHandle);
    STAR_UNREFERENCED(pchTitle);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_UpdatePublishedFileDescription(ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, const char * pchDescription)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(updateHandle);
    STAR_UNREFERENCED(pchDescription);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_UpdatePublishedFileVisibility(ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, ERemoteStoragePublishedFileVisibility eVisibility)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(updateHandle);
    STAR_UNREFERENCED(eVisibility);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_UpdatePublishedFileTags(ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, SteamParamStringArray_t * pTags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(updateHandle);
    STAR_UNREFERENCED(pTags);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_CommitPublishedFileUpdate(ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(updateHandle);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_GetPublishedFileDetails(ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId, uint32 unMaxSecondsOld)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unPublishedFileId);
    STAR_UNREFERENCED(unMaxSecondsOld);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_DeletePublishedFile(ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unPublishedFileId);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_EnumerateUserPublishedFiles(ISteamRemoteStorage* self, uint32 unStartIndex)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unStartIndex);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_EnumerateUserSubscribedFiles(ISteamRemoteStorage* self, uint32 unStartIndex)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unStartIndex);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_UnsubscribePublishedFile(ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unPublishedFileId);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemoteStorage_UpdatePublishedFileSetChangeDescription(ISteamRemoteStorage* self, PublishedFileUpdateHandle_t updateHandle, const char * pchChangeDescription)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(updateHandle);
    STAR_UNREFERENCED(pchChangeDescription);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_GetPublishedItemVoteDetails(ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unPublishedFileId);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_UpdateUserPublishedItemVote(ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId, bool bVoteUp)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unPublishedFileId);
    STAR_UNREFERENCED(bVoteUp);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_GetUserPublishedItemVoteDetails(ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unPublishedFileId);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_EnumerateUserSharedWorkshopFiles(ISteamRemoteStorage* self, uint64_steamid steamId, uint32 unStartIndex, SteamParamStringArray_t * pRequiredTags, SteamParamStringArray_t * pExcludedTags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamId);
    STAR_UNREFERENCED(unStartIndex);
    STAR_UNREFERENCED(pRequiredTags);
    STAR_UNREFERENCED(pExcludedTags);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_PublishVideo(ISteamRemoteStorage* self, EWorkshopVideoProvider eVideoProvider, const char * pchVideoAccount, const char * pchVideoIdentifier, const char * pchPreviewFile, AppId_t nConsumerAppId, const char * pchTitle, const char * pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t * pTags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eVideoProvider);
    STAR_UNREFERENCED(pchVideoAccount);
    STAR_UNREFERENCED(pchVideoIdentifier);
    STAR_UNREFERENCED(pchPreviewFile);
    STAR_UNREFERENCED(nConsumerAppId);
    STAR_UNREFERENCED(pchTitle);
    STAR_UNREFERENCED(pchDescription);
    STAR_UNREFERENCED(eVisibility);
    STAR_UNREFERENCED(pTags);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_SetUserPublishedFileAction(ISteamRemoteStorage* self, PublishedFileId_t unPublishedFileId, EWorkshopFileAction eAction)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unPublishedFileId);
    STAR_UNREFERENCED(eAction);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_EnumeratePublishedFilesByUserAction(ISteamRemoteStorage* self, EWorkshopFileAction eAction, uint32 unStartIndex)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eAction);
    STAR_UNREFERENCED(unStartIndex);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_EnumeratePublishedWorkshopFiles(ISteamRemoteStorage* self, EWorkshopEnumerationType eEnumerationType, uint32 unStartIndex, uint32 unCount, uint32 unDays, SteamParamStringArray_t * pTags, SteamParamStringArray_t * pUserTags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eEnumerationType);
    STAR_UNREFERENCED(unStartIndex);
    STAR_UNREFERENCED(unCount);
    STAR_UNREFERENCED(unDays);
    STAR_UNREFERENCED(pTags);
    STAR_UNREFERENCED(pUserTags);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamRemoteStorage_UGCDownloadToLocation(ISteamRemoteStorage* self, UGCHandle_t hContent, const char * pchLocation, uint32 unPriority)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hContent);
    STAR_UNREFERENCED(pchLocation);
    STAR_UNREFERENCED(unPriority);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_UpdateAvgRateStat(ISteamUserStats* self, const char * pchName, float flCountThisSession, double dSessionLength)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(flCountThisSession);
    STAR_UNREFERENCED(dSessionLength);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_GetAchievementAndUnlockTime(ISteamUserStats* self, const char * pchName, bool * pbAchieved, uint32 * punUnlockTime)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pbAchieved);
    STAR_UNREFERENCED(punUnlockTime);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamUserStats_GetAchievementIcon(ISteamUserStats* self, const char * pchName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchName);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamUserStats_GetAchievementDisplayAttribute(ISteamUserStats* self, const char * pchName, const char * pchKey)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pchKey);
    return "";
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUserStats_RequestUserStats(ISteamUserStats* self, uint64_steamid steamIDUser)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_GetUserStatInt32(ISteamUserStats* self, uint64_steamid steamIDUser, const char * pchName, int32 * pData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pData);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_GetUserStatFloat(ISteamUserStats* self, uint64_steamid steamIDUser, const char * pchName, float * pData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pData);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_GetUserAchievement(ISteamUserStats* self, uint64_steamid steamIDUser, const char * pchName, bool * pbAchieved)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pbAchieved);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_GetUserAchievementAndUnlockTime(ISteamUserStats* self, uint64_steamid steamIDUser, const char * pchName, bool * pbAchieved, uint32 * punUnlockTime)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pbAchieved);
    STAR_UNREFERENCED(punUnlockTime);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUserStats_FindOrCreateLeaderboard(ISteamUserStats* self, const char * pchLeaderboardName, ELeaderboardSortMethod eLeaderboardSortMethod, ELeaderboardDisplayType eLeaderboardDisplayType)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchLeaderboardName);
    STAR_UNREFERENCED(eLeaderboardSortMethod);
    STAR_UNREFERENCED(eLeaderboardDisplayType);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUserStats_FindLeaderboard(ISteamUserStats* self, const char * pchLeaderboardName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchLeaderboardName);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamUserStats_GetLeaderboardName(ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSteamLeaderboard);
    return "";
}

STAR_EXPORT int SteamAPI_ISteamUserStats_GetLeaderboardEntryCount(ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSteamLeaderboard);
    return {};
}

STAR_EXPORT ELeaderboardSortMethod SteamAPI_ISteamUserStats_GetLeaderboardSortMethod(ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSteamLeaderboard);
    return {};
}

STAR_EXPORT ELeaderboardDisplayType SteamAPI_ISteamUserStats_GetLeaderboardDisplayType(ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSteamLeaderboard);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUserStats_DownloadLeaderboardEntries(ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardDataRequest eLeaderboardDataRequest, int nRangeStart, int nRangeEnd)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSteamLeaderboard);
    STAR_UNREFERENCED(eLeaderboardDataRequest);
    STAR_UNREFERENCED(nRangeStart);
    STAR_UNREFERENCED(nRangeEnd);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUserStats_DownloadLeaderboardEntriesForUsers(ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard, CSteamID * prgUsers, int cUsers)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSteamLeaderboard);
    STAR_UNREFERENCED(prgUsers);
    STAR_UNREFERENCED(cUsers);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_GetDownloadedLeaderboardEntry(ISteamUserStats* self, SteamLeaderboardEntries_t hSteamLeaderboardEntries, int index, LeaderboardEntry_t * pLeaderboardEntry, int32 * pDetails, int cDetailsMax)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSteamLeaderboardEntries);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(pLeaderboardEntry);
    STAR_UNREFERENCED(pDetails);
    STAR_UNREFERENCED(cDetailsMax);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUserStats_UploadLeaderboardScore(ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard, ELeaderboardUploadScoreMethod eLeaderboardUploadScoreMethod, int32 nScore, const int32 * pScoreDetails, int cScoreDetailsCount)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSteamLeaderboard);
    STAR_UNREFERENCED(eLeaderboardUploadScoreMethod);
    STAR_UNREFERENCED(nScore);
    STAR_UNREFERENCED(pScoreDetails);
    STAR_UNREFERENCED(cScoreDetailsCount);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUserStats_AttachLeaderboardUGC(ISteamUserStats* self, SteamLeaderboard_t hSteamLeaderboard, UGCHandle_t hUGC)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSteamLeaderboard);
    STAR_UNREFERENCED(hUGC);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUserStats_GetNumberOfCurrentPlayers(ISteamUserStats* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUserStats_RequestGlobalAchievementPercentages(ISteamUserStats* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamUserStats_GetMostAchievedAchievementInfo(ISteamUserStats* self, char * pchName, uint32 unNameBufLen, float * pflPercent, bool * pbAchieved)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(unNameBufLen);
    STAR_UNREFERENCED(pflPercent);
    STAR_UNREFERENCED(pbAchieved);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamUserStats_GetNextMostAchievedAchievementInfo(ISteamUserStats* self, int iIteratorPrevious, char * pchName, uint32 unNameBufLen, float * pflPercent, bool * pbAchieved)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iIteratorPrevious);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(unNameBufLen);
    STAR_UNREFERENCED(pflPercent);
    STAR_UNREFERENCED(pbAchieved);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_GetAchievementAchievedPercent(ISteamUserStats* self, const char * pchName, float * pflPercent)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pflPercent);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUserStats_RequestGlobalStats(ISteamUserStats* self, int nHistoryDays)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nHistoryDays);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_GetGlobalStatInt64(ISteamUserStats* self, const char * pchStatName, int64 * pData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchStatName);
    STAR_UNREFERENCED(pData);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_GetGlobalStatDouble(ISteamUserStats* self, const char * pchStatName, double * pData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchStatName);
    STAR_UNREFERENCED(pData);
    return {};
}

STAR_EXPORT int32 SteamAPI_ISteamUserStats_GetGlobalStatHistoryInt64(ISteamUserStats* self, const char * pchStatName, int64 * pData, uint32 cubData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchStatName);
    STAR_UNREFERENCED(pData);
    STAR_UNREFERENCED(cubData);
    return {};
}

STAR_EXPORT int32 SteamAPI_ISteamUserStats_GetGlobalStatHistoryDouble(ISteamUserStats* self, const char * pchStatName, double * pData, uint32 cubData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchStatName);
    STAR_UNREFERENCED(pData);
    STAR_UNREFERENCED(cubData);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_GetAchievementProgressLimitsInt32(ISteamUserStats* self, const char * pchName, int32 * pnMinProgress, int32 * pnMaxProgress)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pnMinProgress);
    STAR_UNREFERENCED(pnMaxProgress);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUserStats_GetAchievementProgressLimitsFloat(ISteamUserStats* self, const char * pchName, float * pfMinProgress, float * pfMaxProgress)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pfMinProgress);
    STAR_UNREFERENCED(pfMaxProgress);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_BIsLowViolence(ISteamApps* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_BIsCybercafe(ISteamApps* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_BIsVACBanned(ISteamApps* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamApps_GetAvailableGameLanguages(ISteamApps* self)
{
    STAR_UNREFERENCED(self);
    return "";
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_BIsSubscribedApp(ISteamApps* self, AppId_t appID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(appID);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamApps_GetEarliestPurchaseUnixTime(ISteamApps* self, AppId_t nAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_BIsSubscribedFromFreeWeekend(ISteamApps* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamApps_GetDLCCount(ISteamApps* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_BGetDLCDataByIndex(ISteamApps* self, int iDLC, AppId_t * pAppID, bool * pbAvailable, char * pchName, int cchNameBufferSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iDLC);
    STAR_UNREFERENCED(pAppID);
    STAR_UNREFERENCED(pbAvailable);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(cchNameBufferSize);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamApps_InstallDLC(ISteamApps* self, AppId_t nAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
}

STAR_EXPORT void SteamAPI_ISteamApps_UninstallDLC(ISteamApps* self, AppId_t nAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
}

STAR_EXPORT void SteamAPI_ISteamApps_RequestAppProofOfPurchaseKey(ISteamApps* self, AppId_t nAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_GetCurrentBetaName(ISteamApps* self, char * pchName, int cchNameBufferSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(cchNameBufferSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_MarkContentCorrupt(ISteamApps* self, bool bMissingFilesOnly)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bMissingFilesOnly);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamApps_GetInstalledDepots(ISteamApps* self, AppId_t appID, DepotId_t * pvecDepots, uint32 cMaxDepots)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(appID);
    STAR_UNREFERENCED(pvecDepots);
    STAR_UNREFERENCED(cMaxDepots);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamApps_GetAppInstallDir(ISteamApps* self, AppId_t appID, char * pchFolder, uint32 cchFolderBufferSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(appID);
    STAR_UNREFERENCED(pchFolder);
    STAR_UNREFERENCED(cchFolderBufferSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_BIsAppInstalled(ISteamApps* self, AppId_t appID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(appID);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamApps_GetAppOwner(ISteamApps* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamApps_GetLaunchQueryParam(ISteamApps* self, const char * pchKey)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchKey);
    return "";
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_GetDlcDownloadProgress(ISteamApps* self, AppId_t nAppID, uint64 * punBytesDownloaded, uint64 * punBytesTotal)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
    STAR_UNREFERENCED(punBytesDownloaded);
    STAR_UNREFERENCED(punBytesTotal);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamApps_GetAppBuildId(ISteamApps* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamApps_RequestAllProofOfPurchaseKeys(ISteamApps* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamApps_GetFileDetails(ISteamApps* self, const char * pszFileName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszFileName);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_BIsSubscribedFromFamilySharing(ISteamApps* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_BIsTimedTrial(ISteamApps* self, uint32 * punSecondsAllowed, uint32 * punSecondsPlayed)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(punSecondsAllowed);
    STAR_UNREFERENCED(punSecondsPlayed);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_SetDlcContext(ISteamApps* self, AppId_t nAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamApps_GetNumBetas(ISteamApps* self, int * pnAvailable, int * pnPrivate)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pnAvailable);
    STAR_UNREFERENCED(pnPrivate);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_GetBetaInfo(ISteamApps* self, int iBetaIndex, uint32 * punFlags, uint32 * punBuildID, char * pchBetaName, int cchBetaName, char * pchDescription, int cchDescription, uint32 *punLastUpdated)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iBetaIndex);
    STAR_UNREFERENCED(punFlags);
    STAR_UNREFERENCED(punBuildID);
    STAR_UNREFERENCED(pchBetaName);
    STAR_UNREFERENCED(cchBetaName);
    STAR_UNREFERENCED(pchDescription);
    STAR_UNREFERENCED(cchDescription);
    STAR_UNREFERENCED(punLastUpdated);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamApps_SetActiveBeta(ISteamApps* self, const char * pchBetaName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchBetaName);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_SendP2PPacket(ISteamNetworking* self, uint64_steamid steamIDRemote, const void * pubData, uint32 cubData, EP2PSend eP2PSendType, int nChannel)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDRemote);
    STAR_UNREFERENCED(pubData);
    STAR_UNREFERENCED(cubData);
    STAR_UNREFERENCED(eP2PSendType);
    STAR_UNREFERENCED(nChannel);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_IsP2PPacketAvailable(ISteamNetworking* self, uint32 * pcubMsgSize, int nChannel)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pcubMsgSize);
    STAR_UNREFERENCED(nChannel);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_ReadP2PPacket(ISteamNetworking* self, void * pubDest, uint32 cubDest, uint32 * pcubMsgSize, CSteamID * psteamIDRemote, int nChannel)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pubDest);
    STAR_UNREFERENCED(cubDest);
    STAR_UNREFERENCED(pcubMsgSize);
    STAR_UNREFERENCED(psteamIDRemote);
    STAR_UNREFERENCED(nChannel);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_AcceptP2PSessionWithUser(ISteamNetworking* self, uint64_steamid steamIDRemote)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDRemote);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_CloseP2PSessionWithUser(ISteamNetworking* self, uint64_steamid steamIDRemote)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDRemote);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_CloseP2PChannelWithUser(ISteamNetworking* self, uint64_steamid steamIDRemote, int nChannel)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDRemote);
    STAR_UNREFERENCED(nChannel);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_GetP2PSessionState(ISteamNetworking* self, uint64_steamid steamIDRemote, P2PSessionState_t * pConnectionState)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDRemote);
    STAR_UNREFERENCED(pConnectionState);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_AllowP2PPacketRelay(ISteamNetworking* self, bool bAllow)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bAllow);
    return {};
}

STAR_EXPORT SNetSocket_t SteamAPI_ISteamNetworking_CreateP2PConnectionSocket(ISteamNetworking* self, uint64_steamid steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDTarget);
    STAR_UNREFERENCED(nVirtualPort);
    STAR_UNREFERENCED(nTimeoutSec);
    STAR_UNREFERENCED(bAllowUseOfPacketRelay);
    return {};
}

STAR_EXPORT SNetSocket_t SteamAPI_ISteamNetworking_CreateConnectionSocket(ISteamNetworking* self, SteamIPAddress_t nIP, uint16 nPort, int nTimeoutSec)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nIP);
    STAR_UNREFERENCED(nPort);
    STAR_UNREFERENCED(nTimeoutSec);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_DestroySocket(ISteamNetworking* self, SNetSocket_t hSocket, bool bNotifyRemoteEnd)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSocket);
    STAR_UNREFERENCED(bNotifyRemoteEnd);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_DestroyListenSocket(ISteamNetworking* self, SNetListenSocket_t hSocket, bool bNotifyRemoteEnd)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSocket);
    STAR_UNREFERENCED(bNotifyRemoteEnd);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_SendDataOnSocket(ISteamNetworking* self, SNetSocket_t hSocket, void * pubData, uint32 cubData, bool bReliable)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSocket);
    STAR_UNREFERENCED(pubData);
    STAR_UNREFERENCED(cubData);
    STAR_UNREFERENCED(bReliable);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_IsDataAvailableOnSocket(ISteamNetworking* self, SNetSocket_t hSocket, uint32 * pcubMsgSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSocket);
    STAR_UNREFERENCED(pcubMsgSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_RetrieveDataFromSocket(ISteamNetworking* self, SNetSocket_t hSocket, void * pubDest, uint32 cubDest, uint32 * pcubMsgSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSocket);
    STAR_UNREFERENCED(pubDest);
    STAR_UNREFERENCED(cubDest);
    STAR_UNREFERENCED(pcubMsgSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_IsDataAvailable(ISteamNetworking* self, SNetListenSocket_t hListenSocket, uint32 * pcubMsgSize, SNetSocket_t * phSocket)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hListenSocket);
    STAR_UNREFERENCED(pcubMsgSize);
    STAR_UNREFERENCED(phSocket);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_RetrieveData(ISteamNetworking* self, SNetListenSocket_t hListenSocket, void * pubDest, uint32 cubDest, uint32 * pcubMsgSize, SNetSocket_t * phSocket)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hListenSocket);
    STAR_UNREFERENCED(pubDest);
    STAR_UNREFERENCED(cubDest);
    STAR_UNREFERENCED(pcubMsgSize);
    STAR_UNREFERENCED(phSocket);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_GetSocketInfo(ISteamNetworking* self, SNetSocket_t hSocket, CSteamID * pSteamIDRemote, int * peSocketStatus, SteamIPAddress_t * punIPRemote, uint16 * punPortRemote)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSocket);
    STAR_UNREFERENCED(pSteamIDRemote);
    STAR_UNREFERENCED(peSocketStatus);
    STAR_UNREFERENCED(punIPRemote);
    STAR_UNREFERENCED(punPortRemote);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworking_GetListenSocketInfo(ISteamNetworking* self, SNetListenSocket_t hListenSocket, SteamIPAddress_t * pnIP, uint16 * pnPort)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hListenSocket);
    STAR_UNREFERENCED(pnIP);
    STAR_UNREFERENCED(pnPort);
    return {};
}

STAR_EXPORT ESNetSocketConnectionType SteamAPI_ISteamNetworking_GetSocketConnectionType(ISteamNetworking* self, SNetSocket_t hSocket)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSocket);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworking_GetMaxPacketSize(ISteamNetworking* self, SNetSocket_t hSocket)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSocket);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusic_BIsEnabled(ISteamMusic* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusic_BIsPlaying(ISteamMusic* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT AudioPlayback_Status SteamAPI_ISteamMusic_GetPlaybackStatus(ISteamMusic* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamMusic_PlayPrevious(ISteamMusic* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamMusic_SetVolume(ISteamMusic* self, float flVolume)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(flVolume);
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_RegisterSteamMusicRemote(ISteamMusicRemote* self, const char * pchName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchName);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_DeregisterSteamMusicRemote(ISteamMusicRemote* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_BIsCurrentMusicRemote(ISteamMusicRemote* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_BActivationSuccess(ISteamMusicRemote* self, bool bValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_SetDisplayName(ISteamMusicRemote* self, const char * pchDisplayName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchDisplayName);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_SetPNGIcon_64x64(ISteamMusicRemote* self, void * pvBuffer, uint32 cbBufferLength)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pvBuffer);
    STAR_UNREFERENCED(cbBufferLength);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_EnablePlayPrevious(ISteamMusicRemote* self, bool bValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_EnablePlayNext(ISteamMusicRemote* self, bool bValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_EnableShuffled(ISteamMusicRemote* self, bool bValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_EnableLooped(ISteamMusicRemote* self, bool bValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_EnableQueue(ISteamMusicRemote* self, bool bValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_EnablePlaylists(ISteamMusicRemote* self, bool bValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_UpdatePlaybackStatus(ISteamMusicRemote* self, AudioPlayback_Status nStatus)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nStatus);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_UpdateShuffled(ISteamMusicRemote* self, bool bValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_UpdateLooped(ISteamMusicRemote* self, bool bValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_UpdateVolume(ISteamMusicRemote* self, float flValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(flValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_CurrentEntryWillChange(ISteamMusicRemote* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_CurrentEntryIsAvailable(ISteamMusicRemote* self, bool bAvailable)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bAvailable);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_UpdateCurrentEntryText(ISteamMusicRemote* self, const char * pchText)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchText);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_UpdateCurrentEntryElapsedSeconds(ISteamMusicRemote* self, int nValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_UpdateCurrentEntryCoverArt(ISteamMusicRemote* self, void * pvBuffer, uint32 cbBufferLength)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pvBuffer);
    STAR_UNREFERENCED(cbBufferLength);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_CurrentEntryDidChange(ISteamMusicRemote* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_QueueWillChange(ISteamMusicRemote* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_ResetQueueEntries(ISteamMusicRemote* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_SetQueueEntry(ISteamMusicRemote* self, int nID, int nPosition, const char * pchEntryText)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nID);
    STAR_UNREFERENCED(nPosition);
    STAR_UNREFERENCED(pchEntryText);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_SetCurrentQueueEntry(ISteamMusicRemote* self, int nID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_QueueDidChange(ISteamMusicRemote* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_PlaylistWillChange(ISteamMusicRemote* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_ResetPlaylistEntries(ISteamMusicRemote* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_SetPlaylistEntry(ISteamMusicRemote* self, int nID, int nPosition, const char * pchEntryText)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nID);
    STAR_UNREFERENCED(nPosition);
    STAR_UNREFERENCED(pchEntryText);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_SetCurrentPlaylistEntry(ISteamMusicRemote* self, int nID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamMusicRemote_PlaylistDidChange(ISteamMusicRemote* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT HTTPRequestHandle SteamAPI_ISteamHTTP_CreateHTTPRequest(ISteamHTTP* self, EHTTPMethod eHTTPRequestMethod, const char * pchAbsoluteURL)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eHTTPRequestMethod);
    STAR_UNREFERENCED(pchAbsoluteURL);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SetHTTPRequestContextValue(ISteamHTTP* self, HTTPRequestHandle hRequest, uint64 ulContextValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(ulContextValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SetHTTPRequestNetworkActivityTimeout(ISteamHTTP* self, HTTPRequestHandle hRequest, uint32 unTimeoutSeconds)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(unTimeoutSeconds);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SetHTTPRequestHeaderValue(ISteamHTTP* self, HTTPRequestHandle hRequest, const char * pchHeaderName, const char * pchHeaderValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(pchHeaderName);
    STAR_UNREFERENCED(pchHeaderValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SetHTTPRequestGetOrPostParameter(ISteamHTTP* self, HTTPRequestHandle hRequest, const char * pchParamName, const char * pchParamValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(pchParamName);
    STAR_UNREFERENCED(pchParamValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SendHTTPRequest(ISteamHTTP* self, HTTPRequestHandle hRequest, SteamAPICall_t * pCallHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(pCallHandle);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SendHTTPRequestAndStreamResponse(ISteamHTTP* self, HTTPRequestHandle hRequest, SteamAPICall_t * pCallHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(pCallHandle);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_DeferHTTPRequest(ISteamHTTP* self, HTTPRequestHandle hRequest)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_PrioritizeHTTPRequest(ISteamHTTP* self, HTTPRequestHandle hRequest)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_GetHTTPResponseHeaderSize(ISteamHTTP* self, HTTPRequestHandle hRequest, const char * pchHeaderName, uint32 * unResponseHeaderSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(pchHeaderName);
    STAR_UNREFERENCED(unResponseHeaderSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_GetHTTPResponseHeaderValue(ISteamHTTP* self, HTTPRequestHandle hRequest, const char * pchHeaderName, uint8 * pHeaderValueBuffer, uint32 unBufferSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(pchHeaderName);
    STAR_UNREFERENCED(pHeaderValueBuffer);
    STAR_UNREFERENCED(unBufferSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_GetHTTPResponseBodySize(ISteamHTTP* self, HTTPRequestHandle hRequest, uint32 * unBodySize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(unBodySize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_GetHTTPResponseBodyData(ISteamHTTP* self, HTTPRequestHandle hRequest, uint8 * pBodyDataBuffer, uint32 unBufferSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(pBodyDataBuffer);
    STAR_UNREFERENCED(unBufferSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_GetHTTPStreamingResponseBodyData(ISteamHTTP* self, HTTPRequestHandle hRequest, uint32 cOffset, uint8 * pBodyDataBuffer, uint32 unBufferSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(cOffset);
    STAR_UNREFERENCED(pBodyDataBuffer);
    STAR_UNREFERENCED(unBufferSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_ReleaseHTTPRequest(ISteamHTTP* self, HTTPRequestHandle hRequest)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_GetHTTPDownloadProgressPct(ISteamHTTP* self, HTTPRequestHandle hRequest, float * pflPercentOut)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(pflPercentOut);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SetHTTPRequestRawPostBody(ISteamHTTP* self, HTTPRequestHandle hRequest, const char * pchContentType, uint8 * pubBody, uint32 unBodyLen)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(pchContentType);
    STAR_UNREFERENCED(pubBody);
    STAR_UNREFERENCED(unBodyLen);
    return {};
}

STAR_EXPORT HTTPCookieContainerHandle SteamAPI_ISteamHTTP_CreateCookieContainer(ISteamHTTP* self, bool bAllowResponsesToModify)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bAllowResponsesToModify);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_ReleaseCookieContainer(ISteamHTTP* self, HTTPCookieContainerHandle hCookieContainer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hCookieContainer);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SetCookie(ISteamHTTP* self, HTTPCookieContainerHandle hCookieContainer, const char * pchHost, const char * pchUrl, const char * pchCookie)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hCookieContainer);
    STAR_UNREFERENCED(pchHost);
    STAR_UNREFERENCED(pchUrl);
    STAR_UNREFERENCED(pchCookie);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SetHTTPRequestCookieContainer(ISteamHTTP* self, HTTPRequestHandle hRequest, HTTPCookieContainerHandle hCookieContainer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(hCookieContainer);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SetHTTPRequestUserAgentInfo(ISteamHTTP* self, HTTPRequestHandle hRequest, const char * pchUserAgentInfo)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(pchUserAgentInfo);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SetHTTPRequestRequiresVerifiedCertificate(ISteamHTTP* self, HTTPRequestHandle hRequest, bool bRequireVerifiedCertificate)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(bRequireVerifiedCertificate);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_SetHTTPRequestAbsoluteTimeoutMS(ISteamHTTP* self, HTTPRequestHandle hRequest, uint32 unMilliseconds)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(unMilliseconds);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamHTTP_GetHTTPRequestWasTimedOut(ISteamHTTP* self, HTTPRequestHandle hRequest, bool * pbWasTimedOut)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hRequest);
    STAR_UNREFERENCED(pbWasTimedOut);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamController_Init(ISteamController* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamController_Shutdown(ISteamController* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamController_RunFrame(ISteamController* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT int SteamAPI_ISteamController_GetConnectedControllers(ISteamController* self, ControllerHandle_t * handlesOut)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handlesOut);
    return {};
}

STAR_EXPORT ControllerActionSetHandle_t SteamAPI_ISteamController_GetActionSetHandle(ISteamController* self, const char * pszActionSetName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszActionSetName);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamController_ActivateActionSet(ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(actionSetHandle);
}

STAR_EXPORT ControllerActionSetHandle_t SteamAPI_ISteamController_GetCurrentActionSet(ISteamController* self, ControllerHandle_t controllerHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamController_ActivateActionSetLayer(ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetLayerHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(actionSetLayerHandle);
}

STAR_EXPORT void SteamAPI_ISteamController_DeactivateActionSetLayer(ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetLayerHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(actionSetLayerHandle);
}

STAR_EXPORT void SteamAPI_ISteamController_DeactivateAllActionSetLayers(ISteamController* self, ControllerHandle_t controllerHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
}

STAR_EXPORT int SteamAPI_ISteamController_GetActiveActionSetLayers(ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t * handlesOut)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(handlesOut);
    return {};
}

STAR_EXPORT ControllerDigitalActionHandle_t SteamAPI_ISteamController_GetDigitalActionHandle(ISteamController* self, const char * pszActionName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszActionName);
    return {};
}

STAR_EXPORT InputDigitalActionData_t SteamAPI_ISteamController_GetDigitalActionData(ISteamController* self, ControllerHandle_t controllerHandle, ControllerDigitalActionHandle_t digitalActionHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(digitalActionHandle);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamController_GetDigitalActionOrigins(ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerDigitalActionHandle_t digitalActionHandle, EControllerActionOrigin * originsOut)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(actionSetHandle);
    STAR_UNREFERENCED(digitalActionHandle);
    STAR_UNREFERENCED(originsOut);
    return {};
}

STAR_EXPORT ControllerAnalogActionHandle_t SteamAPI_ISteamController_GetAnalogActionHandle(ISteamController* self, const char * pszActionName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszActionName);
    return {};
}

STAR_EXPORT InputAnalogActionData_t SteamAPI_ISteamController_GetAnalogActionData(ISteamController* self, ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t analogActionHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(analogActionHandle);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamController_GetAnalogActionOrigins(ISteamController* self, ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerAnalogActionHandle_t analogActionHandle, EControllerActionOrigin * originsOut)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(actionSetHandle);
    STAR_UNREFERENCED(analogActionHandle);
    STAR_UNREFERENCED(originsOut);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamController_GetGlyphForActionOrigin(ISteamController* self, EControllerActionOrigin eOrigin)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eOrigin);
    return "";
}

STAR_EXPORT const char * SteamAPI_ISteamController_GetStringForActionOrigin(ISteamController* self, EControllerActionOrigin eOrigin)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eOrigin);
    return "";
}

STAR_EXPORT void SteamAPI_ISteamController_StopAnalogActionMomentum(ISteamController* self, ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t eAction)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(eAction);
}

STAR_EXPORT InputMotionData_t SteamAPI_ISteamController_GetMotionData(ISteamController* self, ControllerHandle_t controllerHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamController_TriggerHapticPulse(ISteamController* self, ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(eTargetPad);
    STAR_UNREFERENCED(usDurationMicroSec);
}

STAR_EXPORT void SteamAPI_ISteamController_TriggerRepeatedHapticPulse(ISteamController* self, ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec, unsigned short usOffMicroSec, unsigned short unRepeat, unsigned int nFlags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(eTargetPad);
    STAR_UNREFERENCED(usDurationMicroSec);
    STAR_UNREFERENCED(usOffMicroSec);
    STAR_UNREFERENCED(unRepeat);
    STAR_UNREFERENCED(nFlags);
}

STAR_EXPORT void SteamAPI_ISteamController_TriggerVibration(ISteamController* self, ControllerHandle_t controllerHandle, unsigned short usLeftSpeed, unsigned short usRightSpeed)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(usLeftSpeed);
    STAR_UNREFERENCED(usRightSpeed);
}

STAR_EXPORT void SteamAPI_ISteamController_SetLEDColor(ISteamController* self, ControllerHandle_t controllerHandle, uint8 nColorR, uint8 nColorG, uint8 nColorB, unsigned int nFlags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(nColorR);
    STAR_UNREFERENCED(nColorG);
    STAR_UNREFERENCED(nColorB);
    STAR_UNREFERENCED(nFlags);
}

STAR_EXPORT steam_bool SteamAPI_ISteamController_ShowBindingPanel(ISteamController* self, ControllerHandle_t controllerHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    return {};
}

STAR_EXPORT ESteamInputType SteamAPI_ISteamController_GetInputTypeForHandle(ISteamController* self, ControllerHandle_t controllerHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    return {};
}

STAR_EXPORT ControllerHandle_t SteamAPI_ISteamController_GetControllerForGamepadIndex(ISteamController* self, int nIndex)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nIndex);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamController_GetGamepadIndexForController(ISteamController* self, ControllerHandle_t ulControllerHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulControllerHandle);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamController_GetStringForXboxOrigin(ISteamController* self, EXboxOrigin eOrigin)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eOrigin);
    return "";
}

STAR_EXPORT const char * SteamAPI_ISteamController_GetGlyphForXboxOrigin(ISteamController* self, EXboxOrigin eOrigin)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eOrigin);
    return "";
}

STAR_EXPORT EControllerActionOrigin SteamAPI_ISteamController_GetActionOriginFromXboxOrigin(ISteamController* self, ControllerHandle_t controllerHandle, EXboxOrigin eOrigin)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(eOrigin);
    return {};
}

STAR_EXPORT EControllerActionOrigin SteamAPI_ISteamController_TranslateActionOrigin(ISteamController* self, ESteamInputType eDestinationInputType, EControllerActionOrigin eSourceOrigin)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eDestinationInputType);
    STAR_UNREFERENCED(eSourceOrigin);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamController_GetControllerBindingRevision(ISteamController* self, ControllerHandle_t controllerHandle, int * pMajor, int * pMinor)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(controllerHandle);
    STAR_UNREFERENCED(pMajor);
    STAR_UNREFERENCED(pMinor);
    return {};
}

STAR_EXPORT UGCQueryHandle_t SteamAPI_ISteamUGC_CreateQueryAllUGCRequestPage(ISteamUGC* self, EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eQueryType);
    STAR_UNREFERENCED(eMatchingeMatchingUGCTypeFileType);
    STAR_UNREFERENCED(nCreatorAppID);
    STAR_UNREFERENCED(nConsumerAppID);
    STAR_UNREFERENCED(unPage);
    return {};
}

STAR_EXPORT UGCQueryHandle_t SteamAPI_ISteamUGC_CreateQueryAllUGCRequestCursor(ISteamUGC* self, EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, const char * pchCursor)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eQueryType);
    STAR_UNREFERENCED(eMatchingeMatchingUGCTypeFileType);
    STAR_UNREFERENCED(nCreatorAppID);
    STAR_UNREFERENCED(nConsumerAppID);
    STAR_UNREFERENCED(pchCursor);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamUGC_GetQueryUGCNumTags(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_GetQueryUGCTag(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, uint32 indexTag, char * pchValue, uint32 cchValueSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(indexTag);
    STAR_UNREFERENCED(pchValue);
    STAR_UNREFERENCED(cchValueSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_GetQueryUGCTagDisplayName(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, uint32 indexTag, char * pchValue, uint32 cchValueSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(indexTag);
    STAR_UNREFERENCED(pchValue);
    STAR_UNREFERENCED(cchValueSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_GetQueryUGCPreviewURL(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, char * pchURL, uint32 cchURLSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(pchURL);
    STAR_UNREFERENCED(cchURLSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_GetQueryUGCMetadata(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, char * pchMetadata, uint32 cchMetadatasize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(pchMetadata);
    STAR_UNREFERENCED(cchMetadatasize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_GetQueryUGCStatistic(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, EItemStatistic eStatType, uint64 * pStatValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(eStatType);
    STAR_UNREFERENCED(pStatValue);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamUGC_GetQueryUGCNumAdditionalPreviews(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_GetQueryUGCAdditionalPreview(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, uint32 previewIndex, char * pchURLOrVideoID, uint32 cchURLSize, char * pchOriginalFileName, uint32 cchOriginalFileNameSize, EItemPreviewType * pPreviewType)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(previewIndex);
    STAR_UNREFERENCED(pchURLOrVideoID);
    STAR_UNREFERENCED(cchURLSize);
    STAR_UNREFERENCED(pchOriginalFileName);
    STAR_UNREFERENCED(cchOriginalFileNameSize);
    STAR_UNREFERENCED(pPreviewType);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamUGC_GetQueryUGCNumKeyValueTags(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_GetQueryUGCKeyValueTag(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, uint32 keyValueTagIndex, char * pchKey, uint32 cchKeySize, char * pchValue, uint32 cchValueSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(keyValueTagIndex);
    STAR_UNREFERENCED(pchKey);
    STAR_UNREFERENCED(cchKeySize);
    STAR_UNREFERENCED(pchValue);
    STAR_UNREFERENCED(cchValueSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_GetQueryFirstUGCKeyValueTag(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, const char * pchKey, char * pchValue, uint32 cchValueSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(pchKey);
    STAR_UNREFERENCED(pchValue);
    STAR_UNREFERENCED(cchValueSize);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamUGC_GetNumSupportedGameVersions(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_GetSupportedGameVersionData(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, uint32 versionIndex, char * pchGameBranchMin, char * pchGameBranchMax, uint32 cchGameBranchSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(versionIndex);
    STAR_UNREFERENCED(pchGameBranchMin);
    STAR_UNREFERENCED(pchGameBranchMax);
    STAR_UNREFERENCED(cchGameBranchSize);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamUGC_GetQueryUGCContentDescriptors(ISteamUGC* self, UGCQueryHandle_t handle, uint32 index, EUGCContentDescriptorID * pvecDescriptors, uint32 cMaxEntries)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(pvecDescriptors);
    STAR_UNREFERENCED(cMaxEntries);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_AddRequiredTag(ISteamUGC* self, UGCQueryHandle_t handle, const char * pTagName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pTagName);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_AddRequiredTagGroup(ISteamUGC* self, UGCQueryHandle_t handle, const SteamParamStringArray_t * pTagGroups)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pTagGroups);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_AddExcludedTag(ISteamUGC* self, UGCQueryHandle_t handle, const char * pTagName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pTagName);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetReturnOnlyIDs(ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnOnlyIDs)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(bReturnOnlyIDs);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetReturnKeyValueTags(ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnKeyValueTags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(bReturnKeyValueTags);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetReturnMetadata(ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnMetadata)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(bReturnMetadata);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetReturnAdditionalPreviews(ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnAdditionalPreviews)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(bReturnAdditionalPreviews);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetReturnTotalOnly(ISteamUGC* self, UGCQueryHandle_t handle, bool bReturnTotalOnly)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(bReturnTotalOnly);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetReturnPlaytimeStats(ISteamUGC* self, UGCQueryHandle_t handle, uint32 unDays)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(unDays);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetLanguage(ISteamUGC* self, UGCQueryHandle_t handle, const char * pchLanguage)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pchLanguage);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetAdminQuery(ISteamUGC* self, UGCUpdateHandle_t handle, bool bAdminQuery)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(bAdminQuery);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetCloudFileNameFilter(ISteamUGC* self, UGCQueryHandle_t handle, const char * pMatchCloudFileName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pMatchCloudFileName);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetMatchAnyTag(ISteamUGC* self, UGCQueryHandle_t handle, bool bMatchAnyTag)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(bMatchAnyTag);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetRankedByTrendDays(ISteamUGC* self, UGCQueryHandle_t handle, uint32 unDays)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(unDays);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetTimeCreatedDateRange(ISteamUGC* self, UGCQueryHandle_t handle, RTime32 rtStart, RTime32 rtEnd)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(rtStart);
    STAR_UNREFERENCED(rtEnd);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetTimeUpdatedDateRange(ISteamUGC* self, UGCQueryHandle_t handle, RTime32 rtStart, RTime32 rtEnd)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(rtStart);
    STAR_UNREFERENCED(rtEnd);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_AddRequiredKeyValueTag(ISteamUGC* self, UGCQueryHandle_t handle, const char * pKey, const char * pValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pKey);
    STAR_UNREFERENCED(pValue);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_RequestUGCDetails(ISteamUGC* self, PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nPublishedFileID);
    STAR_UNREFERENCED(unMaxAgeSeconds);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetItemUpdateLanguage(ISteamUGC* self, UGCUpdateHandle_t handle, const char * pchLanguage)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pchLanguage);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetItemMetadata(ISteamUGC* self, UGCUpdateHandle_t handle, const char * pchMetaData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pchMetaData);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetAllowLegacyUpload(ISteamUGC* self, UGCUpdateHandle_t handle, bool bAllowLegacyUpload)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(bAllowLegacyUpload);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_RemoveAllItemKeyValueTags(ISteamUGC* self, UGCUpdateHandle_t handle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_RemoveItemKeyValueTags(ISteamUGC* self, UGCUpdateHandle_t handle, const char * pchKey)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pchKey);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_AddItemKeyValueTag(ISteamUGC* self, UGCUpdateHandle_t handle, const char * pchKey, const char * pchValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pchKey);
    STAR_UNREFERENCED(pchValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_AddItemPreviewFile(ISteamUGC* self, UGCUpdateHandle_t handle, const char * pszPreviewFile, EItemPreviewType type)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pszPreviewFile);
    STAR_UNREFERENCED(type);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_AddItemPreviewVideo(ISteamUGC* self, UGCUpdateHandle_t handle, const char * pszVideoID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pszVideoID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_UpdateItemPreviewFile(ISteamUGC* self, UGCUpdateHandle_t handle, uint32 index, const char * pszPreviewFile)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(pszPreviewFile);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_UpdateItemPreviewVideo(ISteamUGC* self, UGCUpdateHandle_t handle, uint32 index, const char * pszVideoID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    STAR_UNREFERENCED(pszVideoID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_RemoveItemPreview(ISteamUGC* self, UGCUpdateHandle_t handle, uint32 index)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(index);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_AddContentDescriptor(ISteamUGC* self, UGCUpdateHandle_t handle, EUGCContentDescriptorID descid)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(descid);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_RemoveContentDescriptor(ISteamUGC* self, UGCUpdateHandle_t handle, EUGCContentDescriptorID descid)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(descid);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetRequiredGameVersions(ISteamUGC* self, UGCUpdateHandle_t handle, const char * pszGameBranchMin, const char * pszGameBranchMax)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pszGameBranchMin);
    STAR_UNREFERENCED(pszGameBranchMax);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_SetUserItemVote(ISteamUGC* self, PublishedFileId_t nPublishedFileID, bool bVoteUp)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nPublishedFileID);
    STAR_UNREFERENCED(bVoteUp);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_GetUserItemVote(ISteamUGC* self, PublishedFileId_t nPublishedFileID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nPublishedFileID);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_AddItemToFavorites(ISteamUGC* self, AppId_t nAppId, PublishedFileId_t nPublishedFileID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppId);
    STAR_UNREFERENCED(nPublishedFileID);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_RemoveItemFromFavorites(ISteamUGC* self, AppId_t nAppId, PublishedFileId_t nPublishedFileID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppId);
    STAR_UNREFERENCED(nPublishedFileID);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_UnsubscribeItem(ISteamUGC* self, PublishedFileId_t nPublishedFileID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nPublishedFileID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_GetItemDownloadInfo(ISteamUGC* self, PublishedFileId_t nPublishedFileID, uint64 * punBytesDownloaded, uint64 * punBytesTotal)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nPublishedFileID);
    STAR_UNREFERENCED(punBytesDownloaded);
    STAR_UNREFERENCED(punBytesTotal);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_BInitWorkshopForGameServer(ISteamUGC* self, DepotId_t unWorkshopDepotID, const char * pszFolder)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unWorkshopDepotID);
    STAR_UNREFERENCED(pszFolder);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamUGC_SuspendDownloads(ISteamUGC* self, bool bSuspend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bSuspend);
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_StartPlaytimeTracking(ISteamUGC* self, PublishedFileId_t * pvecPublishedFileID, uint32 unNumPublishedFileIDs)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pvecPublishedFileID);
    STAR_UNREFERENCED(unNumPublishedFileIDs);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_StopPlaytimeTracking(ISteamUGC* self, PublishedFileId_t * pvecPublishedFileID, uint32 unNumPublishedFileIDs)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pvecPublishedFileID);
    STAR_UNREFERENCED(unNumPublishedFileIDs);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_StopPlaytimeTrackingForAllItems(ISteamUGC* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_AddDependency(ISteamUGC* self, PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nParentPublishedFileID);
    STAR_UNREFERENCED(nChildPublishedFileID);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_RemoveDependency(ISteamUGC* self, PublishedFileId_t nParentPublishedFileID, PublishedFileId_t nChildPublishedFileID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nParentPublishedFileID);
    STAR_UNREFERENCED(nChildPublishedFileID);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_AddAppDependency(ISteamUGC* self, PublishedFileId_t nPublishedFileID, AppId_t nAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nPublishedFileID);
    STAR_UNREFERENCED(nAppID);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_RemoveAppDependency(ISteamUGC* self, PublishedFileId_t nPublishedFileID, AppId_t nAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nPublishedFileID);
    STAR_UNREFERENCED(nAppID);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_GetAppDependencies(ISteamUGC* self, PublishedFileId_t nPublishedFileID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nPublishedFileID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_ShowWorkshopEULA(ISteamUGC* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamUGC_GetWorkshopEULAStatus(ISteamUGC* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamUGC_GetUserContentDescriptorPreferences(ISteamUGC* self, EUGCContentDescriptorID * pvecDescriptors, uint32 cMaxEntries)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pvecDescriptors);
    STAR_UNREFERENCED(cMaxEntries);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetItemsDisabledLocally(ISteamUGC* self, PublishedFileId_t * pvecPublishedFileIDs, uint32 unNumPublishedFileIDs, bool bDisabledLocally)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pvecPublishedFileIDs);
    STAR_UNREFERENCED(unNumPublishedFileIDs);
    STAR_UNREFERENCED(bDisabledLocally);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamUGC_SetSubscriptionsLoadOrder(ISteamUGC* self, PublishedFileId_t * pvecPublishedFileIDs, uint32 unNumPublishedFileIDs)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pvecPublishedFileIDs);
    STAR_UNREFERENCED(unNumPublishedFileIDs);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamAppList_GetNumInstalledApps(ISteamAppList* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamAppList_GetInstalledApps(ISteamAppList* self, AppId_t * pvecAppID, uint32 unMaxAppIDs)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pvecAppID);
    STAR_UNREFERENCED(unMaxAppIDs);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamAppList_GetAppName(ISteamAppList* self, AppId_t nAppID, char * pchName, int cchNameMax)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(cchNameMax);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamAppList_GetAppInstallDir(ISteamAppList* self, AppId_t nAppID, char * pchDirectory, int cchNameMax)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
    STAR_UNREFERENCED(pchDirectory);
    STAR_UNREFERENCED(cchNameMax);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamAppList_GetAppBuildId(ISteamAppList* self, AppId_t nAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamHTMLSurface_CreateBrowser(ISteamHTMLSurface* self, const char * pchUserAgent, const char * pchUserCSS)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchUserAgent);
    STAR_UNREFERENCED(pchUserCSS);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_RemoveBrowser(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_LoadURL(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, const char * pchURL, const char * pchPostData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(pchURL);
    STAR_UNREFERENCED(pchPostData);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_StopLoad(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_GoForward(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_AddHeader(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, const char * pchKey, const char * pchValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(pchKey);
    STAR_UNREFERENCED(pchValue);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_ExecuteJavascript(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, const char * pchScript)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(pchScript);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_MouseUp(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(eMouseButton);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_MouseDown(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(eMouseButton);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_MouseDoubleClick(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(eMouseButton);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_MouseMove(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, int x, int y)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(x);
    STAR_UNREFERENCED(y);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_MouseWheel(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, int32 nDelta)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(nDelta);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_KeyChar(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, uint32 cUnicodeChar, EHTMLKeyModifiers eHTMLKeyModifiers)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(cUnicodeChar);
    STAR_UNREFERENCED(eHTMLKeyModifiers);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_SetHorizontalScroll(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(nAbsolutePixelScroll);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_SetVerticalScroll(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(nAbsolutePixelScroll);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_SetKeyFocus(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, bool bHasKeyFocus)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(bHasKeyFocus);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_ViewSource(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_CopyToClipboard(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_PasteFromClipboard(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_StopFind(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_GetLinkAtPosition(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, int x, int y)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(x);
    STAR_UNREFERENCED(y);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_SetCookie(ISteamHTMLSurface* self, const char * pchHostname, const char * pchKey, const char * pchValue, const char * pchPath, RTime32 nExpires, bool bSecure, bool bHTTPOnly)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchHostname);
    STAR_UNREFERENCED(pchKey);
    STAR_UNREFERENCED(pchValue);
    STAR_UNREFERENCED(pchPath);
    STAR_UNREFERENCED(nExpires);
    STAR_UNREFERENCED(bSecure);
    STAR_UNREFERENCED(bHTTPOnly);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_SetPageScaleFactor(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, float flZoom, int nPointX, int nPointY)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(flZoom);
    STAR_UNREFERENCED(nPointX);
    STAR_UNREFERENCED(nPointY);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_SetBackgroundMode(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, bool bBackgroundMode)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(bBackgroundMode);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_SetDPIScalingFactor(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, float flDPIScaling)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(flDPIScaling);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_OpenDeveloperTools(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_AllowStartRequest(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, bool bAllowed)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(bAllowed);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_JSDialogResponse(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, bool bResult)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(bResult);
}

STAR_EXPORT void SteamAPI_ISteamHTMLSurface_FileLoadDialogResponse(ISteamHTMLSurface* self, HHTMLBrowser unBrowserHandle, const char ** pchSelectedFiles)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unBrowserHandle);
    STAR_UNREFERENCED(pchSelectedFiles);
}

STAR_EXPORT EResult SteamAPI_ISteamInventory_GetResultStatus(ISteamInventory* self, SteamInventoryResult_t resultHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(resultHandle);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamInventory_GetResultTimestamp(ISteamInventory* self, SteamInventoryResult_t resultHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(resultHandle);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_CheckResultSteamID(ISteamInventory* self, SteamInventoryResult_t resultHandle, uint64_steamid steamIDExpected)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(resultHandle);
    STAR_UNREFERENCED(steamIDExpected);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_GetAllItems(ISteamInventory* self, SteamInventoryResult_t * pResultHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pResultHandle);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_GetItemsByID(ISteamInventory* self, SteamInventoryResult_t * pResultHandle, const SteamItemInstanceID_t * pInstanceIDs, uint32 unCountInstanceIDs)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pResultHandle);
    STAR_UNREFERENCED(pInstanceIDs);
    STAR_UNREFERENCED(unCountInstanceIDs);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_SerializeResult(ISteamInventory* self, SteamInventoryResult_t resultHandle, void * pOutBuffer, uint32 * punOutBufferSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(resultHandle);
    STAR_UNREFERENCED(pOutBuffer);
    STAR_UNREFERENCED(punOutBufferSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_DeserializeResult(ISteamInventory* self, SteamInventoryResult_t * pOutResultHandle, const void * pBuffer, uint32 unBufferSize, bool bRESERVED_MUST_BE_FALSE)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pOutResultHandle);
    STAR_UNREFERENCED(pBuffer);
    STAR_UNREFERENCED(unBufferSize);
    STAR_UNREFERENCED(bRESERVED_MUST_BE_FALSE);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_GrantPromoItems(ISteamInventory* self, SteamInventoryResult_t * pResultHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pResultHandle);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_AddPromoItem(ISteamInventory* self, SteamInventoryResult_t * pResultHandle, SteamItemDef_t itemDef)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pResultHandle);
    STAR_UNREFERENCED(itemDef);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_AddPromoItems(ISteamInventory* self, SteamInventoryResult_t * pResultHandle, const SteamItemDef_t * pArrayItemDefs, uint32 unArrayLength)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pResultHandle);
    STAR_UNREFERENCED(pArrayItemDefs);
    STAR_UNREFERENCED(unArrayLength);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_ConsumeItem(ISteamInventory* self, SteamInventoryResult_t * pResultHandle, SteamItemInstanceID_t itemConsume, uint32 unQuantity)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pResultHandle);
    STAR_UNREFERENCED(itemConsume);
    STAR_UNREFERENCED(unQuantity);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_ExchangeItems(ISteamInventory* self, SteamInventoryResult_t * pResultHandle, const SteamItemDef_t * pArrayGenerate, const uint32 * punArrayGenerateQuantity, uint32 unArrayGenerateLength, const SteamItemInstanceID_t * pArrayDestroy, const uint32 * punArrayDestroyQuantity, uint32 unArrayDestroyLength)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pResultHandle);
    STAR_UNREFERENCED(pArrayGenerate);
    STAR_UNREFERENCED(punArrayGenerateQuantity);
    STAR_UNREFERENCED(unArrayGenerateLength);
    STAR_UNREFERENCED(pArrayDestroy);
    STAR_UNREFERENCED(punArrayDestroyQuantity);
    STAR_UNREFERENCED(unArrayDestroyLength);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_TransferItemQuantity(ISteamInventory* self, SteamInventoryResult_t * pResultHandle, SteamItemInstanceID_t itemIdSource, uint32 unQuantity, SteamItemInstanceID_t itemIdDest)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pResultHandle);
    STAR_UNREFERENCED(itemIdSource);
    STAR_UNREFERENCED(unQuantity);
    STAR_UNREFERENCED(itemIdDest);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamInventory_SendItemDropHeartbeat(ISteamInventory* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_TriggerItemDrop(ISteamInventory* self, SteamInventoryResult_t * pResultHandle, SteamItemDef_t dropListDefinition)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pResultHandle);
    STAR_UNREFERENCED(dropListDefinition);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_TradeItems(ISteamInventory* self, SteamInventoryResult_t * pResultHandle, uint64_steamid steamIDTradePartner, const SteamItemInstanceID_t * pArrayGive, const uint32 * pArrayGiveQuantity, uint32 nArrayGiveLength, const SteamItemInstanceID_t * pArrayGet, const uint32 * pArrayGetQuantity, uint32 nArrayGetLength)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pResultHandle);
    STAR_UNREFERENCED(steamIDTradePartner);
    STAR_UNREFERENCED(pArrayGive);
    STAR_UNREFERENCED(pArrayGiveQuantity);
    STAR_UNREFERENCED(nArrayGiveLength);
    STAR_UNREFERENCED(pArrayGet);
    STAR_UNREFERENCED(pArrayGetQuantity);
    STAR_UNREFERENCED(nArrayGetLength);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_LoadItemDefinitions(ISteamInventory* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_GetItemDefinitionProperty(ISteamInventory* self, SteamItemDef_t iDefinition, const char * pchPropertyName, char * pchValueBuffer, uint32 * punValueBufferSizeOut)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iDefinition);
    STAR_UNREFERENCED(pchPropertyName);
    STAR_UNREFERENCED(pchValueBuffer);
    STAR_UNREFERENCED(punValueBufferSizeOut);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamInventory_RequestEligiblePromoItemDefinitionsIDs(ISteamInventory* self, uint64_steamid steamID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_GetEligiblePromoItemDefinitionIDs(ISteamInventory* self, uint64_steamid steamID, SteamItemDef_t * pItemDefIDs, uint32 * punItemDefIDsArraySize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
    STAR_UNREFERENCED(pItemDefIDs);
    STAR_UNREFERENCED(punItemDefIDsArraySize);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamInventory_StartPurchase(ISteamInventory* self, const SteamItemDef_t * pArrayItemDefs, const uint32 * punArrayQuantity, uint32 unArrayLength)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pArrayItemDefs);
    STAR_UNREFERENCED(punArrayQuantity);
    STAR_UNREFERENCED(unArrayLength);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamInventory_RequestPrices(ISteamInventory* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamInventory_GetNumItemsWithPrices(ISteamInventory* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_GetItemsWithPrices(ISteamInventory* self, SteamItemDef_t * pArrayItemDefs, uint64 * pCurrentPrices, uint64 * pBasePrices, uint32 unArrayLength)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pArrayItemDefs);
    STAR_UNREFERENCED(pCurrentPrices);
    STAR_UNREFERENCED(pBasePrices);
    STAR_UNREFERENCED(unArrayLength);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_GetItemPrice(ISteamInventory* self, SteamItemDef_t iDefinition, uint64 * pCurrentPrice, uint64 * pBasePrice)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iDefinition);
    STAR_UNREFERENCED(pCurrentPrice);
    STAR_UNREFERENCED(pBasePrice);
    return {};
}

STAR_EXPORT SteamInventoryUpdateHandle_t SteamAPI_ISteamInventory_StartUpdateProperties(ISteamInventory* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_RemoveProperty(ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char * pchPropertyName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(nItemID);
    STAR_UNREFERENCED(pchPropertyName);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_SetPropertyString(ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char * pchPropertyName, const char * pchPropertyValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(nItemID);
    STAR_UNREFERENCED(pchPropertyName);
    STAR_UNREFERENCED(pchPropertyValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_SetPropertyBool(ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char * pchPropertyName, bool bValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(nItemID);
    STAR_UNREFERENCED(pchPropertyName);
    STAR_UNREFERENCED(bValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_SetPropertyInt64(ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char * pchPropertyName, int64 nValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(nItemID);
    STAR_UNREFERENCED(pchPropertyName);
    STAR_UNREFERENCED(nValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_SetPropertyFloat(ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char * pchPropertyName, float flValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(nItemID);
    STAR_UNREFERENCED(pchPropertyName);
    STAR_UNREFERENCED(flValue);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_SubmitUpdateProperties(ISteamInventory* self, SteamInventoryUpdateHandle_t handle, SteamInventoryResult_t * pResultHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(handle);
    STAR_UNREFERENCED(pResultHandle);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamInventory_InspectItem(ISteamInventory* self, SteamInventoryResult_t * pResultHandle, const char * pchItemToken)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pResultHandle);
    STAR_UNREFERENCED(pchItemToken);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamTimeline_SetTimelineStateDescription(ISteamTimeline* self, const char * pchDescription, float flTimeDelta)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchDescription);
    STAR_UNREFERENCED(flTimeDelta);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_ClearTimelineStateDescription(ISteamTimeline* self, float flTimeDelta)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(flTimeDelta);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_AddTimelineEvent(ISteamTimeline* self, const char * pchIcon, const char * pchTitle, const char * pchDescription, uint32 unPriority, float flStartOffsetSeconds, float flDurationSeconds, ETimelineEventClipPriority ePossibleClip)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchIcon);
    STAR_UNREFERENCED(pchTitle);
    STAR_UNREFERENCED(pchDescription);
    STAR_UNREFERENCED(unPriority);
    STAR_UNREFERENCED(flStartOffsetSeconds);
    STAR_UNREFERENCED(flDurationSeconds);
    STAR_UNREFERENCED(ePossibleClip);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_SetTimelineGameMode(ISteamTimeline* self, ETimelineGameMode eMode)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eMode);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_SetTimelineTooltip(ISteamTimeline* self, const char * pchDescription, float flTimeDelta)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchDescription);
    STAR_UNREFERENCED(flTimeDelta);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_ClearTimelineTooltip(ISteamTimeline* self, float flTimeDelta)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(flTimeDelta);
}

STAR_EXPORT TimelineEventHandle_t SteamAPI_ISteamTimeline_AddInstantaneousTimelineEvent(ISteamTimeline* self, const char * pchTitle, const char * pchDescription, const char * pchIcon, uint32 unIconPriority, float flStartOffsetSeconds, ETimelineEventClipPriority ePossibleClip)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchTitle);
    STAR_UNREFERENCED(pchDescription);
    STAR_UNREFERENCED(pchIcon);
    STAR_UNREFERENCED(unIconPriority);
    STAR_UNREFERENCED(flStartOffsetSeconds);
    STAR_UNREFERENCED(ePossibleClip);
    return {};
}

STAR_EXPORT TimelineEventHandle_t SteamAPI_ISteamTimeline_AddRangeTimelineEvent(ISteamTimeline* self, const char * pchTitle, const char * pchDescription, const char * pchIcon, uint32 unIconPriority, float flStartOffsetSeconds, float flDuration, ETimelineEventClipPriority ePossibleClip)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchTitle);
    STAR_UNREFERENCED(pchDescription);
    STAR_UNREFERENCED(pchIcon);
    STAR_UNREFERENCED(unIconPriority);
    STAR_UNREFERENCED(flStartOffsetSeconds);
    STAR_UNREFERENCED(flDuration);
    STAR_UNREFERENCED(ePossibleClip);
    return {};
}

STAR_EXPORT TimelineEventHandle_t SteamAPI_ISteamTimeline_StartRangeTimelineEvent(ISteamTimeline* self, const char * pchTitle, const char * pchDescription, const char * pchIcon, uint32 unPriority, float flStartOffsetSeconds, ETimelineEventClipPriority ePossibleClip)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchTitle);
    STAR_UNREFERENCED(pchDescription);
    STAR_UNREFERENCED(pchIcon);
    STAR_UNREFERENCED(unPriority);
    STAR_UNREFERENCED(flStartOffsetSeconds);
    STAR_UNREFERENCED(ePossibleClip);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamTimeline_UpdateRangeTimelineEvent(ISteamTimeline* self, TimelineEventHandle_t ulEvent, const char * pchTitle, const char * pchDescription, const char * pchIcon, uint32 unPriority, ETimelineEventClipPriority ePossibleClip)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulEvent);
    STAR_UNREFERENCED(pchTitle);
    STAR_UNREFERENCED(pchDescription);
    STAR_UNREFERENCED(pchIcon);
    STAR_UNREFERENCED(unPriority);
    STAR_UNREFERENCED(ePossibleClip);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_EndRangeTimelineEvent(ISteamTimeline* self, TimelineEventHandle_t ulEvent, float flEndOffsetSeconds)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulEvent);
    STAR_UNREFERENCED(flEndOffsetSeconds);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_RemoveTimelineEvent(ISteamTimeline* self, TimelineEventHandle_t ulEvent)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulEvent);
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamTimeline_DoesEventRecordingExist(ISteamTimeline* self, TimelineEventHandle_t ulEvent)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulEvent);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamTimeline_StartGamePhase(ISteamTimeline* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_EndGamePhase(ISteamTimeline* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_SetGamePhaseID(ISteamTimeline* self, const char * pchPhaseID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchPhaseID);
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamTimeline_DoesGamePhaseRecordingExist(ISteamTimeline* self, const char * pchPhaseID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchPhaseID);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamTimeline_AddGamePhaseTag(ISteamTimeline* self, const char * pchTagName, const char * pchTagIcon, const char * pchTagGroup, uint32 unPriority)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchTagName);
    STAR_UNREFERENCED(pchTagIcon);
    STAR_UNREFERENCED(pchTagGroup);
    STAR_UNREFERENCED(unPriority);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_SetGamePhaseAttribute(ISteamTimeline* self, const char * pchAttributeGroup, const char * pchAttributeValue, uint32 unPriority)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchAttributeGroup);
    STAR_UNREFERENCED(pchAttributeValue);
    STAR_UNREFERENCED(unPriority);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_OpenOverlayToGamePhase(ISteamTimeline* self, const char * pchPhaseID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchPhaseID);
}

STAR_EXPORT void SteamAPI_ISteamTimeline_OpenOverlayToTimelineEvent(ISteamTimeline* self, const TimelineEventHandle_t ulEvent)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ulEvent);
}

STAR_EXPORT void SteamAPI_ISteamVideo_GetVideoURL(ISteamVideo* self, AppId_t unVideoAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unVideoAppID);
}

STAR_EXPORT steam_bool SteamAPI_ISteamVideo_IsBroadcasting(ISteamVideo* self, int * pnNumViewers)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pnNumViewers);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamVideo_GetOPFSettings(ISteamVideo* self, AppId_t unVideoAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unVideoAppID);
}

STAR_EXPORT steam_bool SteamAPI_ISteamVideo_GetOPFStringForApp(ISteamVideo* self, AppId_t unVideoAppID, char * pchBuffer, int32 * pnBufferSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unVideoAppID);
    STAR_UNREFERENCED(pchBuffer);
    STAR_UNREFERENCED(pnBufferSize);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamTV_IsBroadcasting(ISteamTV* self, int * pnNumViewers)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pnNumViewers);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamTV_AddBroadcastGameData(ISteamTV* self, const char * pchKey, const char * pchValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchKey);
    STAR_UNREFERENCED(pchValue);
}

STAR_EXPORT void SteamAPI_ISteamTV_RemoveBroadcastGameData(ISteamTV* self, const char * pchKey)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchKey);
}

STAR_EXPORT void SteamAPI_ISteamTV_AddTimelineMarker(ISteamTV* self, const char * pchTemplateName, bool bPersistent, uint8 nColorR, uint8 nColorG, uint8 nColorB)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchTemplateName);
    STAR_UNREFERENCED(bPersistent);
    STAR_UNREFERENCED(nColorR);
    STAR_UNREFERENCED(nColorG);
    STAR_UNREFERENCED(nColorB);
}

STAR_EXPORT void SteamAPI_ISteamTV_RemoveTimelineMarker(ISteamTV* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT uint32 SteamAPI_ISteamTV_AddRegion(ISteamTV* self, const char * pchElementName, const char * pchTimelineDataSection, const SteamTVRegion_t * pSteamTVRegion, ESteamTVRegionBehavior eSteamTVRegionBehavior)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchElementName);
    STAR_UNREFERENCED(pchTimelineDataSection);
    STAR_UNREFERENCED(pSteamTVRegion);
    STAR_UNREFERENCED(eSteamTVRegionBehavior);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamTV_RemoveRegion(ISteamTV* self, uint32 unRegionHandle)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unRegionHandle);
}

STAR_EXPORT steam_bool SteamAPI_ISteamParentalSettings_BIsParentalLockEnabled(ISteamParentalSettings* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamParentalSettings_BIsParentalLockLocked(ISteamParentalSettings* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamParentalSettings_BIsAppBlocked(ISteamParentalSettings* self, AppId_t nAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamParentalSettings_BIsAppInBlockList(ISteamParentalSettings* self, AppId_t nAppID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nAppID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamParentalSettings_BIsFeatureBlocked(ISteamParentalSettings* self, EParentalFeature eFeature)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eFeature);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamParentalSettings_BIsFeatureInBlockList(ISteamParentalSettings* self, EParentalFeature eFeature)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eFeature);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamRemotePlay_GetSessionCount(ISteamRemotePlay* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT RemotePlaySessionID_t SteamAPI_ISteamRemotePlay_GetSessionID(ISteamRemotePlay* self, int iSessionIndex)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iSessionIndex);
    return {};
}

STAR_EXPORT bool SteamAPI_ISteamRemotePlay_BSessionRemotePlayTogether(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamRemotePlay_GetSessionSteamID(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    return {};
}

STAR_EXPORT uint32 SteamAPI_ISteamRemotePlay_GetSessionGuestID(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamRemotePlay_GetSmallSessionAvatar(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamRemotePlay_GetMediumSessionAvatar(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamRemotePlay_GetLargeSessionAvatar(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamRemotePlay_GetSessionClientName(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    return "";
}

STAR_EXPORT ESteamDeviceFormFactor SteamAPI_ISteamRemotePlay_GetSessionClientFormFactor(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemotePlay_BGetSessionClientResolution(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID, int * pnResolutionX, int * pnResolutionY)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    STAR_UNREFERENCED(pnResolutionX);
    STAR_UNREFERENCED(pnResolutionY);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemotePlay_BStartRemotePlayTogether(ISteamRemotePlay* self, bool bShowOverlay)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bShowOverlay);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemotePlay_ShowRemotePlayTogetherUI(ISteamRemotePlay* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemotePlay_BSendRemotePlayTogetherInvite(ISteamRemotePlay* self, uint64_steamid steamIDFriend)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDFriend);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamRemotePlay_BEnableRemotePlayTogetherDirectInput(ISteamRemotePlay* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamRemotePlay_DisableRemotePlayTogetherDirectInput(ISteamRemotePlay* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT uint32 SteamAPI_ISteamRemotePlay_GetInput(ISteamRemotePlay* self, RemotePlayInput_t * pInput, uint32 unMaxEvents)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pInput);
    STAR_UNREFERENCED(unMaxEvents);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamRemotePlay_SetMouseVisibility(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID, bool bVisible)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    STAR_UNREFERENCED(bVisible);
}

STAR_EXPORT void SteamAPI_ISteamRemotePlay_SetMousePosition(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID, float flNormalizedX, float flNormalizedY)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    STAR_UNREFERENCED(flNormalizedX);
    STAR_UNREFERENCED(flNormalizedY);
}

STAR_EXPORT RemotePlayCursorID_t SteamAPI_ISteamRemotePlay_CreateMouseCursor(ISteamRemotePlay* self, int nWidth, int nHeight, int nHotX, int nHotY, const void * pBGRA, int nPitch)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nWidth);
    STAR_UNREFERENCED(nHeight);
    STAR_UNREFERENCED(nHotX);
    STAR_UNREFERENCED(nHotY);
    STAR_UNREFERENCED(pBGRA);
    STAR_UNREFERENCED(nPitch);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamRemotePlay_SetMouseCursor(ISteamRemotePlay* self, RemotePlaySessionID_t unSessionID, RemotePlayCursorID_t unCursorID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSessionID);
    STAR_UNREFERENCED(unCursorID);
}

STAR_EXPORT EResult SteamAPI_ISteamNetworkingMessages_SendMessageToUser(ISteamNetworkingMessages* self, const SteamNetworkingIdentity & identityRemote, const void * pubData, uint32 cubData, int nSendFlags, int nRemoteChannel)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(identityRemote);
    STAR_UNREFERENCED(pubData);
    STAR_UNREFERENCED(cubData);
    STAR_UNREFERENCED(nSendFlags);
    STAR_UNREFERENCED(nRemoteChannel);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworkingMessages_ReceiveMessagesOnChannel(ISteamNetworkingMessages* self, int nLocalChannel, SteamNetworkingMessage_t ** ppOutMessages, int nMaxMessages)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nLocalChannel);
    STAR_UNREFERENCED(ppOutMessages);
    STAR_UNREFERENCED(nMaxMessages);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingMessages_AcceptSessionWithUser(ISteamNetworkingMessages* self, const SteamNetworkingIdentity & identityRemote)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(identityRemote);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingMessages_CloseSessionWithUser(ISteamNetworkingMessages* self, const SteamNetworkingIdentity & identityRemote)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(identityRemote);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingMessages_CloseChannelWithUser(ISteamNetworkingMessages* self, const SteamNetworkingIdentity & identityRemote, int nLocalChannel)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(identityRemote);
    STAR_UNREFERENCED(nLocalChannel);
    return {};
}

STAR_EXPORT ESteamNetworkingConnectionState SteamAPI_ISteamNetworkingMessages_GetSessionConnectionInfo(ISteamNetworkingMessages* self, const SteamNetworkingIdentity & identityRemote, SteamNetConnectionInfo_t * pConnectionInfo, SteamNetworkingQuickConnectionStatus * pQuickStatus)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(identityRemote);
    STAR_UNREFERENCED(pConnectionInfo);
    STAR_UNREFERENCED(pQuickStatus);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_SetConnectionUserData(ISteamNetworkingSockets* self, HSteamNetConnection hPeer, int64 nUserData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hPeer);
    STAR_UNREFERENCED(nUserData);
    return {};
}

STAR_EXPORT int64 SteamAPI_ISteamNetworkingSockets_GetConnectionUserData(ISteamNetworkingSockets* self, HSteamNetConnection hPeer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hPeer);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamNetworkingSockets_SetConnectionName(ISteamNetworkingSockets* self, HSteamNetConnection hPeer, const char * pszName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hPeer);
    STAR_UNREFERENCED(pszName);
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_GetConnectionName(ISteamNetworkingSockets* self, HSteamNetConnection hPeer, char * pszName, int nMaxLen)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hPeer);
    STAR_UNREFERENCED(pszName);
    STAR_UNREFERENCED(nMaxLen);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamNetworkingSockets_SendMessages(ISteamNetworkingSockets* self, int nMessages, SteamNetworkingMessage_t *const * pMessages, int64 * pOutMessageNumberOrResult)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nMessages);
    STAR_UNREFERENCED(pMessages);
    STAR_UNREFERENCED(pOutMessageNumberOrResult);
}

STAR_EXPORT EResult SteamAPI_ISteamNetworkingSockets_FlushMessagesOnConnection(ISteamNetworkingSockets* self, HSteamNetConnection hConn)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworkingSockets_ReceiveMessagesOnConnection(ISteamNetworkingSockets* self, HSteamNetConnection hConn, SteamNetworkingMessage_t ** ppOutMessages, int nMaxMessages)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(ppOutMessages);
    STAR_UNREFERENCED(nMaxMessages);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_GetConnectionInfo(ISteamNetworkingSockets* self, HSteamNetConnection hConn, SteamNetConnectionInfo_t * pInfo)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(pInfo);
    return {};
}

STAR_EXPORT EResult SteamAPI_ISteamNetworkingSockets_GetConnectionRealTimeStatus(ISteamNetworkingSockets* self, HSteamNetConnection hConn, SteamNetConnectionRealTimeStatus_t * pStatus, int nLanes, SteamNetConnectionRealTimeLaneStatus_t * pLanes)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(pStatus);
    STAR_UNREFERENCED(nLanes);
    STAR_UNREFERENCED(pLanes);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_GetQuickConnectionStatus(ISteamNetworkingSockets009* self, HSteamNetConnection hConn, SteamNetworkingQuickConnectionStatus * pStats)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(pStats);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworkingSockets_GetDetailedConnectionStatus(ISteamNetworkingSockets* self, HSteamNetConnection hConn, char * pszBuf, int cbBuf)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(pszBuf);
    STAR_UNREFERENCED(cbBuf);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_GetListenSocketAddress(ISteamNetworkingSockets* self, HSteamListenSocket hSocket, SteamNetworkingIPAddr * address)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hSocket);
    STAR_UNREFERENCED(address);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_CreateSocketPair(ISteamNetworkingSockets* self, HSteamNetConnection * pOutConnection1, HSteamNetConnection * pOutConnection2, bool bUseNetworkLoopback, const SteamNetworkingIdentity * pIdentity1, const SteamNetworkingIdentity * pIdentity2)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pOutConnection1);
    STAR_UNREFERENCED(pOutConnection2);
    STAR_UNREFERENCED(bUseNetworkLoopback);
    STAR_UNREFERENCED(pIdentity1);
    STAR_UNREFERENCED(pIdentity2);
    return {};
}

STAR_EXPORT EResult SteamAPI_ISteamNetworkingSockets_ConfigureConnectionLanes(ISteamNetworkingSockets* self, HSteamNetConnection hConn, int nNumLanes, const int * pLanePriorities, const uint16 * pLaneWeights)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(nNumLanes);
    STAR_UNREFERENCED(pLanePriorities);
    STAR_UNREFERENCED(pLaneWeights);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_GetIdentity(ISteamNetworkingSockets* self, SteamNetworkingIdentity * pIdentity)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pIdentity);
    return {};
}

STAR_EXPORT ESteamNetworkingAvailability SteamAPI_ISteamNetworkingSockets_InitAuthentication(ISteamNetworkingSockets* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT ESteamNetworkingAvailability SteamAPI_ISteamNetworkingSockets_GetAuthenticationStatus(ISteamNetworkingSockets* self, SteamNetAuthenticationStatus_t * pDetails)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pDetails);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_ReceivedRelayAuthTicket(ISteamNetworkingSockets* self, const void * pvTicket, int cbTicket, SteamDatagramRelayAuthTicket * pOutParsedTicket)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pvTicket);
    STAR_UNREFERENCED(cbTicket);
    STAR_UNREFERENCED(pOutParsedTicket);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworkingSockets_FindRelayAuthTicketForServer(ISteamNetworkingSockets* self, const SteamNetworkingIdentity & identityGameServer, int nRemoteVirtualPort, SteamDatagramRelayAuthTicket * pOutParsedTicket)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(identityGameServer);
    STAR_UNREFERENCED(nRemoteVirtualPort);
    STAR_UNREFERENCED(pOutParsedTicket);
    return {};
}

STAR_EXPORT HSteamNetConnection SteamAPI_ISteamNetworkingSockets_ConnectToHostedDedicatedServer(ISteamNetworkingSockets* self, const SteamNetworkingIdentity & identityTarget, int nRemoteVirtualPort, int nOptions, const SteamNetworkingConfigValue_t * pOptions)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(identityTarget);
    STAR_UNREFERENCED(nRemoteVirtualPort);
    STAR_UNREFERENCED(nOptions);
    STAR_UNREFERENCED(pOptions);
    return {};
}

STAR_EXPORT uint16 SteamAPI_ISteamNetworkingSockets_GetHostedDedicatedServerPort(ISteamNetworkingSockets* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT SteamNetworkingPOPID SteamAPI_ISteamNetworkingSockets_GetHostedDedicatedServerPOPID(ISteamNetworkingSockets* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT EResult SteamAPI_ISteamNetworkingSockets_GetHostedDedicatedServerAddress(ISteamNetworkingSockets* self, SteamDatagramHostedAddress * pRouting)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pRouting);
    return {};
}

STAR_EXPORT HSteamListenSocket SteamAPI_ISteamNetworkingSockets_CreateHostedDedicatedServerListenSocket(ISteamNetworkingSockets* self, int nLocalVirtualPort, int nOptions, const SteamNetworkingConfigValue_t * pOptions)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nLocalVirtualPort);
    STAR_UNREFERENCED(nOptions);
    STAR_UNREFERENCED(pOptions);
    return {};
}

STAR_EXPORT EResult SteamAPI_ISteamNetworkingSockets_GetGameCoordinatorServerLogin(ISteamNetworkingSockets* self, SteamDatagramGameCoordinatorServerLogin * pLoginInfo, int * pcbSignedBlob, void * pBlob)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pLoginInfo);
    STAR_UNREFERENCED(pcbSignedBlob);
    STAR_UNREFERENCED(pBlob);
    return {};
}

STAR_EXPORT HSteamNetConnection SteamAPI_ISteamNetworkingSockets_ConnectP2PCustomSignaling(ISteamNetworkingSockets* self, ISteamNetworkingConnectionSignaling * pSignaling, const SteamNetworkingIdentity * pPeerIdentity, int nRemoteVirtualPort, int nOptions, const SteamNetworkingConfigValue_t * pOptions)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pSignaling);
    STAR_UNREFERENCED(pPeerIdentity);
    STAR_UNREFERENCED(nRemoteVirtualPort);
    STAR_UNREFERENCED(nOptions);
    STAR_UNREFERENCED(pOptions);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_ReceivedP2PCustomSignal(ISteamNetworkingSockets* self, const void * pMsg, int cbMsg, ISteamNetworkingSignalingRecvContext * pContext)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pMsg);
    STAR_UNREFERENCED(cbMsg);
    STAR_UNREFERENCED(pContext);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_GetCertificateRequest(ISteamNetworkingSockets* self, int * pcbBlob, void * pBlob, SteamNetworkingErrMsg & errMsg)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pcbBlob);
    STAR_UNREFERENCED(pBlob);
    STAR_UNREFERENCED(errMsg);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_SetCertificate(ISteamNetworkingSockets* self, const void * pCertificate, int cbCertificate, SteamNetworkingErrMsg & errMsg)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pCertificate);
    STAR_UNREFERENCED(cbCertificate);
    STAR_UNREFERENCED(errMsg);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamNetworkingSockets_ResetIdentity(ISteamNetworkingSockets* self, const SteamNetworkingIdentity * pIdentity)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pIdentity);
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingSockets_BeginAsyncRequestFakeIP(ISteamNetworkingSockets* self, int nNumPorts)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nNumPorts);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamNetworkingSockets_GetFakeIP(ISteamNetworkingSockets* self, int idxFirstPort, SteamNetworkingFakeIPResult_t * pInfo)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(idxFirstPort);
    STAR_UNREFERENCED(pInfo);
}

STAR_EXPORT HSteamListenSocket SteamAPI_ISteamNetworkingSockets_CreateListenSocketP2PFakeIP(ISteamNetworkingSockets* self, int idxFakePort, int nOptions, const SteamNetworkingConfigValue_t * pOptions)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(idxFakePort);
    STAR_UNREFERENCED(nOptions);
    STAR_UNREFERENCED(pOptions);
    return {};
}

STAR_EXPORT EResult SteamAPI_ISteamNetworkingSockets_GetRemoteFakeIPForConnection(ISteamNetworkingSockets* self, HSteamNetConnection hConn, SteamNetworkingIPAddr * pOutAddr)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(pOutAddr);
    return {};
}

STAR_EXPORT ISteamNetworkingFakeUDPPort * SteamAPI_ISteamNetworkingSockets_CreateFakeUDPPort(ISteamNetworkingSockets* self, int idxFakeServerPort)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(idxFakeServerPort);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingConnectionCustomSignaling_SendSignal(ISteamNetworkingConnectionCustomSignaling* self, HSteamNetConnection hConn, const SteamNetConnectionInfo_t & info, const void * pMsg, int cbMsg)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(info);
    STAR_UNREFERENCED(pMsg);
    STAR_UNREFERENCED(cbMsg);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamNetworkingConnectionCustomSignaling_Release(ISteamNetworkingConnectionCustomSignaling* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT ISteamNetworkingConnectionCustomSignaling * SteamAPI_ISteamNetworkingCustomSignalingRecvContext_OnConnectRequest(ISteamNetworkingCustomSignalingRecvContext* self, HSteamNetConnection hConn, const SteamNetworkingIdentity & identityPeer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(identityPeer);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamNetworkingCustomSignalingRecvContext_SendRejectionSignal(ISteamNetworkingCustomSignalingRecvContext* self, const SteamNetworkingIdentity & identityPeer, const void * pMsg, int cbMsg)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(identityPeer);
    STAR_UNREFERENCED(pMsg);
    STAR_UNREFERENCED(cbMsg);
}

STAR_EXPORT SteamNetworkingMessage_t * SteamAPI_ISteamNetworkingUtils_AllocateMessage(ISteamNetworkingUtils* self, int cbAllocateBuffer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(cbAllocateBuffer);
    return {};
}

STAR_EXPORT ESteamNetworkingAvailability SteamAPI_ISteamNetworkingUtils_GetRelayNetworkStatus(ISteamNetworkingUtils* self, SteamRelayNetworkStatus_t * pDetails)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pDetails);
    return {};
}

STAR_EXPORT float SteamAPI_ISteamNetworkingUtils_GetLocalPingLocation(ISteamNetworkingUtils* self, SteamNetworkPingLocation_t & result)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(result);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworkingUtils_EstimatePingTimeBetweenTwoLocations(ISteamNetworkingUtils* self, const SteamNetworkPingLocation_t & location1, const SteamNetworkPingLocation_t & location2)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(location1);
    STAR_UNREFERENCED(location2);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworkingUtils_EstimatePingTimeFromLocalHost(ISteamNetworkingUtils* self, const SteamNetworkPingLocation_t & remoteLocation)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(remoteLocation);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamNetworkingUtils_ConvertPingLocationToString(ISteamNetworkingUtils* self, const SteamNetworkPingLocation_t & location, char * pszBuf, int cchBufSize)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(location);
    STAR_UNREFERENCED(pszBuf);
    STAR_UNREFERENCED(cchBufSize);
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_ParsePingLocationString(ISteamNetworkingUtils* self, const char * pszString, SteamNetworkPingLocation_t & result)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszString);
    STAR_UNREFERENCED(result);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_CheckPingDataUpToDate(ISteamNetworkingUtils* self, float flMaxAgeSeconds)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(flMaxAgeSeconds);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworkingUtils_GetPingToDataCenter(ISteamNetworkingUtils* self, SteamNetworkingPOPID popID, SteamNetworkingPOPID * pViaRelayPoP)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(popID);
    STAR_UNREFERENCED(pViaRelayPoP);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworkingUtils_GetDirectPingToPOP(ISteamNetworkingUtils* self, SteamNetworkingPOPID popID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(popID);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworkingUtils_GetPOPCount(ISteamNetworkingUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworkingUtils_GetPOPList(ISteamNetworkingUtils* self, SteamNetworkingPOPID * list, int nListSz)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(list);
    STAR_UNREFERENCED(nListSz);
    return {};
}

STAR_EXPORT SteamNetworkingMicroseconds SteamAPI_ISteamNetworkingUtils_GetLocalTimestamp(ISteamNetworkingUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamNetworkingUtils_SetDebugOutputFunction(ISteamNetworkingUtils* self, ESteamNetworkingSocketsDebugOutputType eDetailLevel, FSteamNetworkingSocketsDebugOutput pfnFunc)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eDetailLevel);
    STAR_UNREFERENCED(pfnFunc);
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_IsFakeIPv4(ISteamNetworkingUtils* self, uint32 nIPv4)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nIPv4);
    return {};
}

STAR_EXPORT ESteamNetworkingFakeIPType SteamAPI_ISteamNetworkingUtils_GetIPv4FakeIPType(ISteamNetworkingUtils* self, uint32 nIPv4)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nIPv4);
    return {};
}

STAR_EXPORT EResult SteamAPI_ISteamNetworkingUtils_GetRealIdentityForFakeIP(ISteamNetworkingUtils* self, const SteamNetworkingIPAddr & fakeIP, SteamNetworkingIdentity * pOutRealIdentity)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(fakeIP);
    STAR_UNREFERENCED(pOutRealIdentity);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetGlobalConfigValueInt32(ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, int32 val)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eValue);
    STAR_UNREFERENCED(val);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetGlobalConfigValueFloat(ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, float val)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eValue);
    STAR_UNREFERENCED(val);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetGlobalConfigValueString(ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, const char * val)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eValue);
    STAR_UNREFERENCED(val);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetGlobalConfigValuePtr(ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, void * val)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eValue);
    STAR_UNREFERENCED(val);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetConnectionConfigValueInt32(ISteamNetworkingUtils* self, HSteamNetConnection hConn, ESteamNetworkingConfigValue eValue, int32 val)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(eValue);
    STAR_UNREFERENCED(val);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetConnectionConfigValueFloat(ISteamNetworkingUtils* self, HSteamNetConnection hConn, ESteamNetworkingConfigValue eValue, float val)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(eValue);
    STAR_UNREFERENCED(val);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetConnectionConfigValueString(ISteamNetworkingUtils* self, HSteamNetConnection hConn, ESteamNetworkingConfigValue eValue, const char * val)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hConn);
    STAR_UNREFERENCED(eValue);
    STAR_UNREFERENCED(val);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetGlobalCallback_SteamNetConnectionStatusChanged(ISteamNetworkingUtils* self, FnSteamNetConnectionStatusChanged fnCallback)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(fnCallback);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetGlobalCallback_SteamNetAuthenticationStatusChanged(ISteamNetworkingUtils* self, FnSteamNetAuthenticationStatusChanged fnCallback)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(fnCallback);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetGlobalCallback_SteamRelayNetworkStatusChanged(ISteamNetworkingUtils* self, FnSteamRelayNetworkStatusChanged fnCallback)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(fnCallback);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetGlobalCallback_FakeIPResult(ISteamNetworkingUtils* self, FnSteamNetworkingFakeIPResult fnCallback)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(fnCallback);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetGlobalCallback_MessagesSessionRequest(ISteamNetworkingUtils* self, FnSteamNetworkingMessagesSessionRequest fnCallback)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(fnCallback);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetGlobalCallback_MessagesSessionFailed(ISteamNetworkingUtils* self, FnSteamNetworkingMessagesSessionFailed fnCallback)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(fnCallback);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetConfigValue(ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, ESteamNetworkingConfigScope eScopeType, intptr_t scopeObj, ESteamNetworkingConfigDataType eDataType, const void * pArg)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eValue);
    STAR_UNREFERENCED(eScopeType);
    STAR_UNREFERENCED(scopeObj);
    STAR_UNREFERENCED(eDataType);
    STAR_UNREFERENCED(pArg);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SetConfigValueStruct(ISteamNetworkingUtils* self, const SteamNetworkingConfigValue_t & opt, ESteamNetworkingConfigScope eScopeType, intptr_t scopeObj)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(opt);
    STAR_UNREFERENCED(eScopeType);
    STAR_UNREFERENCED(scopeObj);
    return {};
}

STAR_EXPORT ESteamNetworkingGetConfigValueResult SteamAPI_ISteamNetworkingUtils_GetConfigValue(ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, ESteamNetworkingConfigScope eScopeType, intptr_t scopeObj, ESteamNetworkingConfigDataType * pOutDataType, void * pResult, size_t * cbResult)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eValue);
    STAR_UNREFERENCED(eScopeType);
    STAR_UNREFERENCED(scopeObj);
    STAR_UNREFERENCED(pOutDataType);
    STAR_UNREFERENCED(pResult);
    STAR_UNREFERENCED(cbResult);
    return {};
}

STAR_EXPORT const char * SteamAPI_ISteamNetworkingUtils_GetConfigValueInfo(ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eValue, ESteamNetworkingConfigDataType * pOutDataType, ESteamNetworkingConfigScope * pOutScope)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eValue);
    STAR_UNREFERENCED(pOutDataType);
    STAR_UNREFERENCED(pOutScope);
    return "";
}

STAR_EXPORT ESteamNetworkingConfigValue SteamAPI_ISteamNetworkingUtils_GetFirstConfigValue(ISteamNetworkingUtils* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT ESteamNetworkingConfigValue SteamAPI_ISteamNetworkingUtils_IterateGenericEditableConfigValues(ISteamNetworkingUtils* self, ESteamNetworkingConfigValue eCurrent, bool bEnumerateDevVars)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eCurrent);
    STAR_UNREFERENCED(bEnumerateDevVars);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SteamNetworkingIPAddr_ParseString(ISteamNetworkingUtils* self, SteamNetworkingIPAddr * pAddr, const char * pszStr)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pAddr);
    STAR_UNREFERENCED(pszStr);
    return {};
}

STAR_EXPORT ESteamNetworkingFakeIPType SteamAPI_ISteamNetworkingUtils_SteamNetworkingIPAddr_GetFakeIPType(ISteamNetworkingUtils* self, const SteamNetworkingIPAddr & addr)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(addr);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamNetworkingUtils_SteamNetworkingIdentity_ParseString(ISteamNetworkingUtils* self, SteamNetworkingIdentity * pIdentity, const char * pszStr)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pIdentity);
    STAR_UNREFERENCED(pszStr);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetProduct(ISteamGameServer* self, const char * pszProduct)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszProduct);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetGameDescription(ISteamGameServer* self, const char * pszGameDescription)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszGameDescription);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetModDir(ISteamGameServer* self, const char * pszModDir)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszModDir);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetDedicatedServer(ISteamGameServer* self, bool bDedicated)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bDedicated);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_LogOn(ISteamGameServer* self, const char * pszToken)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszToken);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_LogOnAnonymous(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_LogOff(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServer_BLoggedOn(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServer_BSecure(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServer_WasRestartRequested(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetMaxPlayerCount(ISteamGameServer* self, int cPlayersMax)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(cPlayersMax);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetBotPlayerCount(ISteamGameServer* self, int cBotplayers)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(cBotplayers);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetServerName(ISteamGameServer* self, const char * pszServerName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszServerName);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetMapName(ISteamGameServer* self, const char * pszMapName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszMapName);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetPasswordProtected(ISteamGameServer* self, bool bPasswordProtected)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bPasswordProtected);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetSpectatorPort(ISteamGameServer* self, uint16 unSpectatorPort)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unSpectatorPort);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetSpectatorServerName(ISteamGameServer* self, const char * pszSpectatorServerName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszSpectatorServerName);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_ClearAllKeyValues(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetKeyValue(ISteamGameServer* self, const char * pKey, const char * pValue)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pKey);
    STAR_UNREFERENCED(pValue);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetGameTags(ISteamGameServer* self, const char * pchGameTags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchGameTags);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetGameData(ISteamGameServer* self, const char * pchGameData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pchGameData);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetRegion(ISteamGameServer* self, const char * pszRegion)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pszRegion);
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate(ISteamGameServer* self, uint32 unIPClient, const void * pvAuthBlob, uint32 cubAuthBlobSize, CSteamID * pSteamIDUser)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unIPClient);
    STAR_UNREFERENCED(pvAuthBlob);
    STAR_UNREFERENCED(cubAuthBlobSize);
    STAR_UNREFERENCED(pSteamIDUser);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SendUserDisconnect(ISteamGameServer* self, uint64_steamid steamIDUser)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetAdvertiseServerActive(ISteamGameServer* self, bool bActive)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bActive);
}

STAR_EXPORT HAuthTicket SteamAPI_ISteamGameServer_GetAuthSessionTicket(ISteamGameServer* self, void * pTicket, int cbMaxTicket, uint32 * pcbTicket, const SteamNetworkingIdentity * pSnid)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pTicket);
    STAR_UNREFERENCED(cbMaxTicket);
    STAR_UNREFERENCED(pcbTicket);
    STAR_UNREFERENCED(pSnid);
    return {};
}

STAR_EXPORT EBeginAuthSessionResult SteamAPI_ISteamGameServer_BeginAuthSession(ISteamGameServer* self, const void * pAuthTicket, int cbAuthTicket, uint64_steamid steamID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pAuthTicket);
    STAR_UNREFERENCED(cbAuthTicket);
    STAR_UNREFERENCED(steamID);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamGameServer_EndAuthSession(ISteamGameServer* self, uint64_steamid steamID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_CancelAuthTicket(ISteamGameServer* self, HAuthTicket hAuthTicket)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(hAuthTicket);
}

STAR_EXPORT EUserHasLicenseForAppResult SteamAPI_ISteamGameServer_UserHasLicenseForApp(ISteamGameServer* self, uint64_steamid steamID, AppId_t appID)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamID);
    STAR_UNREFERENCED(appID);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServer_RequestUserGroupStatus(ISteamGameServer* self, uint64_steamid steamIDUser, uint64_steamid steamIDGroup)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(steamIDGroup);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamGameServer_GetGameplayStats(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamGameServer_GetServerReputation(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT SteamIPAddress_t SteamAPI_ISteamGameServer_GetPublicIP(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServer_HandleIncomingPacket(ISteamGameServer* self, const void * pData, int cbData, uint32 srcIP, uint16 srcPort)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pData);
    STAR_UNREFERENCED(cbData);
    STAR_UNREFERENCED(srcIP);
    STAR_UNREFERENCED(srcPort);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamGameServer_GetNextOutgoingPacket(ISteamGameServer* self, void * pOut, int cbMaxOut, uint32 * pNetAdr, uint16 * pPort)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pOut);
    STAR_UNREFERENCED(cbMaxOut);
    STAR_UNREFERENCED(pNetAdr);
    STAR_UNREFERENCED(pPort);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamGameServer_EnableHeartbeats(ISteamGameServer* self, bool bActive)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(bActive);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SetHeartbeatInterval(ISteamGameServer* self, int iHeartbeatInterval)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(iHeartbeatInterval);
}

STAR_EXPORT void SteamAPI_ISteamGameServer_ForceHeartbeat(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamGameServer_AssociateWithClan(ISteamGameServer* self, uint64_steamid steamIDClan)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDClan);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamGameServer_ComputeNewPlayerCompatibility(ISteamGameServer* self, uint64_steamid steamIDNewPlayer)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDNewPlayer);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServer_SendUserConnectAndAuthenticate_DEPRECATED(ISteamGameServer* self, uint32 unIPClient, const void * pvAuthBlob, uint32 cubAuthBlobSize, CSteamID * pSteamIDUser)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unIPClient);
    STAR_UNREFERENCED(pvAuthBlob);
    STAR_UNREFERENCED(cubAuthBlobSize);
    STAR_UNREFERENCED(pSteamIDUser);
    return {};
}

STAR_EXPORT uint64_steamid SteamAPI_ISteamGameServer_CreateUnauthenticatedUserConnection(ISteamGameServer* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamGameServer_SendUserDisconnect_DEPRECATED(ISteamGameServer* self, uint64_steamid steamIDUser)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServer_BUpdateUserData(ISteamGameServer* self, uint64_steamid steamIDUser, const char * pchPlayerName, uint32 uScore)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchPlayerName);
    STAR_UNREFERENCED(uScore);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamGameServerStats_RequestUserStats(ISteamGameServerStats* self, uint64_steamid steamIDUser)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServerStats_GetUserStatInt32(ISteamGameServerStats* self, uint64_steamid steamIDUser, const char * pchName, int32 * pData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pData);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServerStats_GetUserStatFloat(ISteamGameServerStats* self, uint64_steamid steamIDUser, const char * pchName, float * pData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pData);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServerStats_GetUserAchievement(ISteamGameServerStats* self, uint64_steamid steamIDUser, const char * pchName, bool * pbAchieved)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(pbAchieved);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServerStats_SetUserStatInt32(ISteamGameServerStats* self, uint64_steamid steamIDUser, const char * pchName, int32 nData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(nData);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServerStats_SetUserStatFloat(ISteamGameServerStats* self, uint64_steamid steamIDUser, const char * pchName, float fData)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(fData);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServerStats_UpdateUserAvgRateStat(ISteamGameServerStats* self, uint64_steamid steamIDUser, const char * pchName, float flCountThisSession, double dSessionLength)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    STAR_UNREFERENCED(flCountThisSession);
    STAR_UNREFERENCED(dSessionLength);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServerStats_SetUserAchievement(ISteamGameServerStats* self, uint64_steamid steamIDUser, const char * pchName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    return {};
}

STAR_EXPORT steam_bool SteamAPI_ISteamGameServerStats_ClearUserAchievement(ISteamGameServerStats* self, uint64_steamid steamIDUser, const char * pchName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    STAR_UNREFERENCED(pchName);
    return {};
}

STAR_EXPORT SteamAPICall_t SteamAPI_ISteamGameServerStats_StoreUserStats(ISteamGameServerStats* self, uint64_steamid steamIDUser)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(steamIDUser);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamNetworkingFakeUDPPort_DestroyFakeUDPPort(ISteamNetworkingFakeUDPPort* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT EResult SteamAPI_ISteamNetworkingFakeUDPPort_SendMessageToFakeIP(ISteamNetworkingFakeUDPPort* self, const SteamNetworkingIPAddr & remoteAddress, const void * pData, uint32 cbData, int nSendFlags)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(remoteAddress);
    STAR_UNREFERENCED(pData);
    STAR_UNREFERENCED(cbData);
    STAR_UNREFERENCED(nSendFlags);
    return {};
}

STAR_EXPORT int SteamAPI_ISteamNetworkingFakeUDPPort_ReceiveMessages(ISteamNetworkingFakeUDPPort* self, SteamNetworkingMessage_t ** ppOutMessages, int nMaxMessages)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ppOutMessages);
    STAR_UNREFERENCED(nMaxMessages);
    return {};
}

STAR_EXPORT void SteamAPI_ISteamNetworkingFakeUDPPort_ScheduleCleanup(ISteamNetworkingFakeUDPPort* self, const SteamNetworkingIPAddr & remoteAddress)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(remoteAddress);
}

STAR_EXPORT steam_bool SteamAPI_SteamIPAddress_t_IsSet(SteamIPAddress_t* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_MatchMakingKeyValuePair_t_Construct(MatchMakingKeyValuePair_t* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_servernetadr_t_Construct(servernetadr_t* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT void SteamAPI_servernetadr_t_Init(servernetadr_t* self, unsigned int ip, uint16 usQueryPort, uint16 usConnectionPort)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(ip);
    STAR_UNREFERENCED(usQueryPort);
    STAR_UNREFERENCED(usConnectionPort);
}

STAR_EXPORT uint16 SteamAPI_servernetadr_t_GetQueryPort(servernetadr_t* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_servernetadr_t_SetQueryPort(servernetadr_t* self, uint16 usPort)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(usPort);
}

STAR_EXPORT uint16 SteamAPI_servernetadr_t_GetConnectionPort(servernetadr_t* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_servernetadr_t_SetConnectionPort(servernetadr_t* self, uint16 usPort)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(usPort);
}

STAR_EXPORT uint32 SteamAPI_servernetadr_t_GetIP(servernetadr_t* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_servernetadr_t_SetIP(servernetadr_t* self, uint32 unIP)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(unIP);
}

STAR_EXPORT const char * SteamAPI_servernetadr_t_GetConnectionAddressString(servernetadr_t* self)
{
    STAR_UNREFERENCED(self);
    return "";
}

STAR_EXPORT const char * SteamAPI_servernetadr_t_GetQueryAddressString(servernetadr_t* self)
{
    STAR_UNREFERENCED(self);
    return "";
}

STAR_EXPORT steam_bool SteamAPI_servernetadr_t_IsLessThan(servernetadr_t* self, const servernetadr_t & netadr)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(netadr);
    return {};
}

STAR_EXPORT void SteamAPI_servernetadr_t_Assign(servernetadr_t* self, const servernetadr_t & that)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(that);
}

STAR_EXPORT void SteamAPI_gameserveritem_t_Construct(gameserveritem_t* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT const char * SteamAPI_gameserveritem_t_GetName(gameserveritem_t* self)
{
    STAR_UNREFERENCED(self);
    return "";
}

STAR_EXPORT void SteamAPI_gameserveritem_t_SetName(gameserveritem_t* self, const char * pName)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(pName);
}

STAR_EXPORT void SteamAPI_SteamNetworkingConfigValue_t_SetInt32(SteamNetworkingConfigValue_t* self, ESteamNetworkingConfigValue eVal, int32_t data)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eVal);
    STAR_UNREFERENCED(data);
}

STAR_EXPORT void SteamAPI_SteamNetworkingConfigValue_t_SetInt64(SteamNetworkingConfigValue_t* self, ESteamNetworkingConfigValue eVal, int64_t data)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eVal);
    STAR_UNREFERENCED(data);
}

STAR_EXPORT void SteamAPI_SteamNetworkingConfigValue_t_SetFloat(SteamNetworkingConfigValue_t* self, ESteamNetworkingConfigValue eVal, float data)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eVal);
    STAR_UNREFERENCED(data);
}

STAR_EXPORT void SteamAPI_SteamNetworkingConfigValue_t_SetPtr(SteamNetworkingConfigValue_t* self, ESteamNetworkingConfigValue eVal, void * data)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eVal);
    STAR_UNREFERENCED(data);
}

STAR_EXPORT void SteamAPI_SteamNetworkingConfigValue_t_SetString(SteamNetworkingConfigValue_t* self, ESteamNetworkingConfigValue eVal, const char * data)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(eVal);
    STAR_UNREFERENCED(data);
}

STAR_EXPORT const char * SteamAPI_SteamNetworkingPOPIDRender_c_str(SteamNetworkingPOPIDRender* self)
{
    STAR_UNREFERENCED(self);
    return "";
}

STAR_EXPORT const char * SteamAPI_SteamNetworkingIdentityRender_c_str(SteamNetworkingIdentityRender* self)
{
    STAR_UNREFERENCED(self);
    return "";
}

STAR_EXPORT const char * SteamAPI_SteamNetworkingIPAddrRender_c_str(SteamNetworkingIPAddrRender* self)
{
    STAR_UNREFERENCED(self);
    return "";
}

STAR_EXPORT void SteamAPI_SteamDatagramHostedAddress_Clear(SteamDatagramHostedAddress* self)
{
    STAR_UNREFERENCED(self);
}

STAR_EXPORT SteamNetworkingPOPID SteamAPI_SteamDatagramHostedAddress_GetPopID(SteamDatagramHostedAddress* self)
{
    STAR_UNREFERENCED(self);
    return {};
}

STAR_EXPORT void SteamAPI_SteamDatagramHostedAddress_SetDevAddress(SteamDatagramHostedAddress* self, uint32 nIP, uint16 nPort, SteamNetworkingPOPID popid)
{
    STAR_UNREFERENCED(self);
    STAR_UNREFERENCED(nIP);
    STAR_UNREFERENCED(nPort);
    STAR_UNREFERENCED(popid);
}

#pragma warning(pop)
