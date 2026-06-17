#pragma once
#include "core/star_common.h"
#include "steam/isteamhttp.h"

class StarSteamHTTP : public ISteamHTTP {
public:
    static StarSteamHTTP& get();
    HTTPRequestHandle CreateHTTPRequest(EHTTPMethod eHTTPRequestMethod, const char* pchAbsoluteURL) override;
    bool SetHTTPRequestContextValue(HTTPRequestHandle hRequest, uint64 ulContextValue) override;
    bool SetHTTPRequestNetworkActivityTimeout(HTTPRequestHandle hRequest, uint32 unTimeoutSeconds) override;
    bool SetHTTPRequestHeaderValue(HTTPRequestHandle hRequest, const char* pchHeaderName, const char* pchHeaderValue) override;
    bool SetHTTPRequestGetOrPostParameter(HTTPRequestHandle hRequest, const char* pchParamName, const char* pchParamValue) override;
    bool SendHTTPRequest(HTTPRequestHandle hRequest, SteamAPICall_t* pCallHandle) override;
    bool SendHTTPRequestAndStreamResponse(HTTPRequestHandle hRequest, SteamAPICall_t* pCallHandle) override;
    bool DeferHTTPRequest(HTTPRequestHandle hRequest) override;
    bool PrioritizeHTTPRequest(HTTPRequestHandle hRequest) override;
    bool GetHTTPResponseHeaderSize(HTTPRequestHandle hRequest, const char* pchHeaderName, uint32* unResponseHeaderSize) override;
    bool GetHTTPResponseHeaderValue(HTTPRequestHandle hRequest, const char* pchHeaderName, uint8* pHeaderValueBuffer, uint32 unBufferSize) override;
    bool GetHTTPResponseBodySize(HTTPRequestHandle hRequest, uint32* unBodySize) override;
    bool GetHTTPResponseBodyData(HTTPRequestHandle hRequest, uint8* pBodyDataBuffer, uint32 unBufferSize) override;
    bool GetHTTPStreamingResponseBodyData(HTTPRequestHandle hRequest, uint32 cOffset, uint8* pBodyDataBuffer, uint32 unBufferSize) override;
    bool ReleaseHTTPRequest(HTTPRequestHandle hRequest) override;
    bool GetHTTPDownloadProgressPct(HTTPRequestHandle hRequest, float* pflPercentOut) override;
    bool SetHTTPRequestRawPostBody(HTTPRequestHandle hRequest, const char* pchContentType, uint8* pubBody, uint32 unBodyLen) override;
    HTTPCookieContainerHandle CreateCookieContainer(bool bAllowResponsesToModify) override;
    bool ReleaseCookieContainer(HTTPCookieContainerHandle hCookieContainer) override;
    bool SetCookie(HTTPCookieContainerHandle hCookieContainer, const char* pchHost, const char* pchUrl, const char* pchCookie) override;
    bool SetHTTPRequestCookieContainer(HTTPRequestHandle hRequest, HTTPCookieContainerHandle hCookieContainer) override;
    bool SetHTTPRequestUserAgentInfo(HTTPRequestHandle hRequest, const char* pchUserAgentInfo) override;
    bool SetHTTPRequestRequiresVerifiedCertificate(HTTPRequestHandle hRequest, bool bRequireVerifiedCertificate) override;
    bool SetHTTPRequestAbsoluteTimeoutMS(HTTPRequestHandle hRequest, uint32 unMilliseconds) override;
    bool GetHTTPRequestWasTimedOut(HTTPRequestHandle hRequest, bool* pbWasTimedOut) override;
private:
    StarSteamHTTP() = default;
};
