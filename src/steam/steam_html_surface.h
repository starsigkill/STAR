#pragma once
#include "core/star_common.h"
#include "steam/isteamhtmlsurface.h"

class StarSteamHTMLSurface : public ISteamHTMLSurface {
public:
    static StarSteamHTMLSurface& get();
    bool Init() override;
    bool Shutdown() override;
    SteamAPICall_t CreateBrowser(const char* pchUserAgent, const char* pchUserCSS) override;
    void RemoveBrowser(HHTMLBrowser unBrowserHandle) override;
    void LoadURL(HHTMLBrowser unBrowserHandle, const char* pchURL, const char* pchPostData) override;
    void SetSize(HHTMLBrowser unBrowserHandle, uint32 unWidth, uint32 unHeight) override;
    void StopLoad(HHTMLBrowser unBrowserHandle) override;
    void Reload(HHTMLBrowser unBrowserHandle) override;
    void GoBack(HHTMLBrowser unBrowserHandle) override;
    void GoForward(HHTMLBrowser unBrowserHandle) override;
    void AddHeader(HHTMLBrowser unBrowserHandle, const char* pchKey, const char* pchValue) override;
    void ExecuteJavascript(HHTMLBrowser unBrowserHandle, const char* pchScript) override;
    void MouseUp(HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton) override;
    void MouseDown(HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton) override;
    void MouseDoubleClick(HHTMLBrowser unBrowserHandle, EHTMLMouseButton eMouseButton) override;
    void MouseMove(HHTMLBrowser unBrowserHandle, int x, int y) override;
    void MouseWheel(HHTMLBrowser unBrowserHandle, int32 nDelta) override;
    void KeyDown(HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode, EHTMLKeyModifiers eHTMLKeyModifiers, bool bIsSystemKey = false) override;
    void KeyUp(HHTMLBrowser unBrowserHandle, uint32 nNativeKeyCode, EHTMLKeyModifiers eHTMLKeyModifiers) override;
    void KeyChar(HHTMLBrowser unBrowserHandle, uint32 cUnicodeChar, EHTMLKeyModifiers eHTMLKeyModifiers) override;
    void SetHorizontalScroll(HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll) override;
    void SetVerticalScroll(HHTMLBrowser unBrowserHandle, uint32 nAbsolutePixelScroll) override;
    void SetKeyFocus(HHTMLBrowser unBrowserHandle, bool bHasKeyFocus) override;
    void ViewSource(HHTMLBrowser unBrowserHandle) override;
    void CopyToClipboard(HHTMLBrowser unBrowserHandle) override;
    void PasteFromClipboard(HHTMLBrowser unBrowserHandle) override;
    void Find(HHTMLBrowser unBrowserHandle, const char* pchSearchStr, bool bCurrentlyInFind, bool bReverse) override;
    void StopFind(HHTMLBrowser unBrowserHandle) override;
    void GetLinkAtPosition(HHTMLBrowser unBrowserHandle, int x, int y) override;
    void SetCookie(const char* pchHostname, const char* pchKey, const char* pchValue, const char* pchPath, RTime32 nExpires, bool bSecure, bool bHTTPOnly) override;
    void SetPageScaleFactor(HHTMLBrowser unBrowserHandle, float flZoom, int nPointX, int nPointY) override;
    void SetBackgroundMode(HHTMLBrowser unBrowserHandle, bool bBackgroundMode) override;
    void SetDPIScalingFactor(HHTMLBrowser unBrowserHandle, float flDPIScaling) override;
    void OpenDeveloperTools(HHTMLBrowser unBrowserHandle) override;
    void AllowStartRequest(HHTMLBrowser unBrowserHandle, bool bAllowed) override;
    void JSDialogResponse(HHTMLBrowser unBrowserHandle, bool bResult) override;
    void FileLoadDialogResponse(HHTMLBrowser unBrowserHandle, const char** pchSelectedFiles) override;
private:
    StarSteamHTMLSurface() = default;
};
