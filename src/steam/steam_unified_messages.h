#pragma once
#include "core/star_common.h"
#include "steam/isteamunifiedmessages.h"

class StarSteamUnifiedMessages : public ISteamUnifiedMessages {
public:
    static StarSteamUnifiedMessages& get();
    ClientUnifiedMessageHandle SendMethod(const char* pchServiceMethod, const void* pRequestBuffer, uint32 unRequestBufferSize, uint64 unContext) override;
    bool GetMethodResponseInfo(ClientUnifiedMessageHandle hHandle, uint32* punResponseSize, EResult* peResult) override;
    bool GetMethodResponseData(ClientUnifiedMessageHandle hHandle, void* pResponseBuffer, uint32 unResponseBufferSize, bool bAutoRelease) override;
    bool ReleaseMethod(ClientUnifiedMessageHandle hHandle) override;
    bool SendNotification(const char* pchServiceNotification, const void* pNotificationBuffer, uint32 unNotificationBufferSize) override;
private:
    StarSteamUnifiedMessages() = default;
};
