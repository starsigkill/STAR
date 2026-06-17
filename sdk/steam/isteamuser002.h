
#ifndef ISTEAMUSER002_H
#define ISTEAMUSER002_H
#ifdef STEAM_WIN32
#pragma once
#endif

// this interface version is not found in public SDK archives, it is based on reversing old Linux binaries

enum ELogonState
{
	k_ELogonStateNotLoggedOn = 0,
	k_ELogonStateLoggingOn = 1,
	k_ELogonStateLoggingOff = 2,
	k_ELogonStateLoggedOn = 3
};

class ICMCallback
{
public:
	virtual ~ICMCallback() {}

	virtual void OnLogonSuccess() = 0;
	virtual void OnLogonFailure( EResult eResult ) = 0;
	virtual void OnLoggedOff( EResult eResult ) = 0;
	virtual void OnBeginLogonRetry() = 0;
	virtual void HandleVACChallenge( int nClientGameID, uint8 *pubChallenge, int cubChallenge ) = 0;
	virtual void GSHandleClientApprove( CSteamID &steamID ) = 0;
	virtual void GSHandleClientDeny( CSteamID &steamID, EDenyReason eDenyReason ) = 0;
	virtual void GSHandleClientKick( CSteamID &steamID, EDenyReason eDenyReason ) = 0;
};

class ISteamUser002
{
public:
	virtual void Init( ICMCallback *cmcallback, ISteam2Auth *steam2auth ) = 0;
	virtual int ProcessCall( int unk ) = 0;
	virtual void LogOn_old( CSteamID &steamID ) = 0;
	virtual void LogOff() = 0;
	virtual bool BLoggedOn() = 0;
	virtual ELogonState GetLogonState() = 0;
	virtual bool BConnected() = 0;
	virtual int CreateAccount( const char *unk1, uint8 *unk2, uint8 *unk3, const char *unk4, int unk5, uint8 *unk6 ) = 0;
	virtual bool IsVACBanned( int nGameID ) = 0;
	virtual bool RequireShowVACBannedMessage( int nGameID ) = 0;
	virtual void AcknowledgeVACBanning( int nGameID ) = 0;
	virtual bool GSSendLogonRequest( CSteamID &steamID ) = 0;
	virtual bool GSSendDisconnect( CSteamID &steamID ) = 0;
	virtual bool GSSendStatusResponse( CSteamID &steamID, int nSecondsConnected, int nSecondsSinceLast ) = 0;
	virtual bool GSSetStatus( int32 nAppIdServed, uint32 unServerFlags, int cPlayers, int cPlayersMax, int cBotPlayers, int unGamePort, const char *pchServerName, const char *pchGameDir, const char *pchMapName, const char *pchVersion ) = 0;
	virtual int NClientGameIDAdd( int nGameID ) = 0;
	virtual void RemoveClientGame( int nClientGameID ) = 0;
	virtual void SetClientGameServer( int nClientGameID, uint32 unIPServer, uint16 usPortServer ) = 0;
	virtual void Test_SuspendActivity() = 0;
	virtual void Test_ResumeActivity() = 0;
	virtual void Test_SendVACResponse( int nClientGameID, uint8 *pubResponse, int cubResponse ) = 0;
	virtual void Test_SetFakePrivateIP( uint32 unIPPrivate ) = 0;
	virtual void Test_SendBigMessage() = 0;
	virtual bool Test_BBigMessageResponseReceived() = 0;
	virtual void Test_SetPktLossPct( int nPct ) = 0;
	virtual void Test_SetForceTCP( bool bForceTCP ) = 0;
	virtual void Test_SetMaxUDPConnectionAttempts( int unk1 ) = 0;
	virtual void Test_Heartbeat() = 0;
	virtual void Test_FakeDisconnect() = 0;
	virtual EUniverse Test_GetEUniverse() = 0;
};

#endif // ISTEAMUSER002_H
