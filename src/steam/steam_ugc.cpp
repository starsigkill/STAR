#include "steam/steam_ugc.h"
#include "core/callbacks.h"
#include "steam/isteamugc.h"

StarSteamUGC& StarSteamUGC::get() { static StarSteamUGC i; return i; }
UGCQueryHandle_t StarSteamUGC::CreateQueryUserUGCRequest(AccountID_t a, EUserUGCList b, EUGCMatchingUGCType c, EUserUGCListSortOrder d, AppId_t e, AppId_t f, uint32 g) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(b); STAR_UNREFERENCED(c); STAR_UNREFERENCED(d); STAR_UNREFERENCED(e); STAR_UNREFERENCED(f); STAR_UNREFERENCED(g); return k_UGCQueryHandleInvalid; }
UGCQueryHandle_t StarSteamUGC::CreateQueryAllUGCRequest(EUGCQuery a, EUGCMatchingUGCType b, AppId_t c, AppId_t d, uint32 e) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(b); STAR_UNREFERENCED(c); STAR_UNREFERENCED(d); STAR_UNREFERENCED(e); return k_UGCQueryHandleInvalid; }
UGCQueryHandle_t StarSteamUGC::CreateQueryUGCDetailsRequest(PublishedFileId_t* p, uint32 n) { STAR_UNREFERENCED(p); STAR_UNREFERENCED(n); return k_UGCQueryHandleInvalid; }
SteamAPICall_t StarSteamUGC::SendQueryUGCRequest(UGCQueryHandle_t h) { STAR_UNREFERENCED(h); SteamUGCQueryCompleted_t r{}; r.m_handle=h; r.m_eResult=k_EResultOK; r.m_unNumResultsReturned=0; r.m_unTotalMatchingResults=0; return STAR_PostCallResult(SteamUGCQueryCompleted_t::k_iCallback, &r, sizeof(r)); }
bool StarSteamUGC::GetQueryUGCResult_old(UGCQueryHandle_t h, uint32 i, SteamUGCDetails_t* p) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); if(p) memset(p,0,sizeof(*p)); return false; }
bool StarSteamUGC::GetQueryUGCPreviewURL(UGCQueryHandle_t h, uint32 i, char* u, uint32 c) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); if(u&&c>0) u[0]=0; return false; }
bool StarSteamUGC::GetQueryUGCMetadata(UGCQueryHandle_t h, uint32 i, char* m, uint32 c) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); if(m&&c>0) m[0]=0; return false; }
bool StarSteamUGC::GetQueryUGCChildren(UGCQueryHandle_t h, uint32 i, PublishedFileId_t* p, uint32 c) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); STAR_UNREFERENCED(p); STAR_UNREFERENCED(c); return false; }
bool StarSteamUGC::GetQueryUGCStatistic(UGCQueryHandle_t h, uint32 i, EItemStatistic e, uint32* v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); STAR_UNREFERENCED(e); if(v) *v=0; return false; }
uint32 StarSteamUGC::GetQueryUGCNumAdditionalPreviews(UGCQueryHandle_t h, uint32 i) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); return 0; }
bool StarSteamUGC::GetQueryUGCAdditionalPreview(UGCQueryHandle_t h, uint32 i, uint32 pi, char* u, uint32 cu, bool* hz) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); STAR_UNREFERENCED(pi); if(u&&cu>0) u[0]=0; if(hz) *hz=false; return false; }
uint32 StarSteamUGC::GetQueryUGCNumKeyValueTags(UGCQueryHandle_t h, uint32 i) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); return 0; }
bool StarSteamUGC::GetQueryUGCKeyValueTag(UGCQueryHandle_t h, uint32 i, uint32 ki, char* k, uint32 ck, char* v, uint32 cv) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(i); STAR_UNREFERENCED(ki); STAR_UNREFERENCED(k); STAR_UNREFERENCED(ck); STAR_UNREFERENCED(v); STAR_UNREFERENCED(cv); return false; }
bool StarSteamUGC::ReleaseQueryUGCRequest(UGCQueryHandle_t h) { STAR_UNREFERENCED(h); return true; }
bool StarSteamUGC::AddRequiredTag(UGCQueryHandle_t h, const char* t) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(t); return false; }
bool StarSteamUGC::AddExcludedTag(UGCQueryHandle_t h, const char* t) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(t); return false; }
bool StarSteamUGC::SetReturnKeyValueTags(UGCQueryHandle_t h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); return false; }
bool StarSteamUGC::SetReturnLongDescription(UGCQueryHandle_t h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); return false; }
bool StarSteamUGC::SetReturnMetadata(UGCQueryHandle_t h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); return false; }
bool StarSteamUGC::SetReturnChildren(UGCQueryHandle_t h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); return false; }
bool StarSteamUGC::SetReturnAdditionalPreviews(UGCQueryHandle_t h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); return false; }
bool StarSteamUGC::SetReturnTotalOnly(UGCQueryHandle_t h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); return false; }
bool StarSteamUGC::SetLanguage(UGCQueryHandle_t h, const char* l) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(l); return false; }
bool StarSteamUGC::SetAllowCachedResponse(UGCQueryHandle_t h, uint32 s) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(s); return false; }
bool StarSteamUGC::SetCloudFileNameFilter(UGCQueryHandle_t h, const char* f) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(f); return false; }
bool StarSteamUGC::SetMatchAnyTag(UGCQueryHandle_t h, bool b) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(b); return false; }
bool StarSteamUGC::SetSearchText(UGCQueryHandle_t h, const char* t) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(t); return false; }
bool StarSteamUGC::SetRankedByTrendDays(UGCQueryHandle_t h, uint32 d) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(d); return false; }
bool StarSteamUGC::AddRequiredKeyValueTag(UGCQueryHandle_t h, const char* k, const char* v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(k); STAR_UNREFERENCED(v); return false; }
SteamAPICall_t StarSteamUGC::RequestUGCDetails_old(PublishedFileId_t f, uint32 a) { STAR_UNREFERENCED(f); STAR_UNREFERENCED(a); SteamUGCRequestUGCDetailsResult_t r{}; r.m_details.m_eResult=k_EResultFail; return STAR_PostCallResult(SteamUGCRequestUGCDetailsResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamUGC::CreateItem(AppId_t a, EWorkshopFileType t) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(t); CreateItemResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(CreateItemResult_t::k_iCallback, &r, sizeof(r)); }
UGCUpdateHandle_t StarSteamUGC::StartItemUpdate(AppId_t a, PublishedFileId_t f) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(f); return k_UGCUpdateHandleInvalid; }
bool StarSteamUGC::SetItemTitle(UGCUpdateHandle_t h, const char* t) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(t); return false; }
bool StarSteamUGC::SetItemDescription(UGCUpdateHandle_t h, const char* d) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(d); return false; }
bool StarSteamUGC::SetItemUpdateLanguage(UGCUpdateHandle_t h, const char* l) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(l); return false; }
bool StarSteamUGC::SetItemMetadata(UGCUpdateHandle_t h, const char* m) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(m); return false; }
bool StarSteamUGC::SetItemVisibility(UGCUpdateHandle_t h, ERemoteStoragePublishedFileVisibility v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(v); return false; }
bool StarSteamUGC::SetItemTags(UGCUpdateHandle_t h, const SteamParamStringArray_t* t) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(t); return false; }
bool StarSteamUGC::SetItemContent(UGCUpdateHandle_t h, const char* f) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(f); return false; }
bool StarSteamUGC::SetItemPreview(UGCUpdateHandle_t h, const char* f) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(f); return false; }
bool StarSteamUGC::RemoveItemKeyValueTags(UGCUpdateHandle_t h, const char* k) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(k); return false; }
bool StarSteamUGC::AddItemKeyValueTag(UGCUpdateHandle_t h, const char* k, const char* v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(k); STAR_UNREFERENCED(v); return false; }
SteamAPICall_t StarSteamUGC::SubmitItemUpdate(UGCUpdateHandle_t h, const char* n) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(n); SubmitItemUpdateResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(SubmitItemUpdateResult_t::k_iCallback, &r, sizeof(r)); }
EItemUpdateStatus StarSteamUGC::GetItemUpdateProgress(UGCUpdateHandle_t h, uint64* p, uint64* t) { STAR_UNREFERENCED(h); if(p) *p=0; if(t) *t=0; return k_EItemUpdateStatusInvalid; }
SteamAPICall_t StarSteamUGC::SetUserItemVote(PublishedFileId_t f, bool v) { STAR_UNREFERENCED(f); STAR_UNREFERENCED(v); SetUserItemVoteResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(SetUserItemVoteResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamUGC::GetUserItemVote(PublishedFileId_t f) { STAR_UNREFERENCED(f); GetUserItemVoteResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(GetUserItemVoteResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamUGC::AddItemToFavorites(AppId_t a, PublishedFileId_t f) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(f); UserFavoriteItemsListChanged_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(UserFavoriteItemsListChanged_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamUGC::RemoveItemFromFavorites(AppId_t a, PublishedFileId_t f) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(f); UserFavoriteItemsListChanged_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(UserFavoriteItemsListChanged_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamUGC::SubscribeItem(PublishedFileId_t f) { STAR_UNREFERENCED(f); RemoteStorageSubscribePublishedFileResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageSubscribePublishedFileResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamUGC::UnsubscribeItem(PublishedFileId_t f) { STAR_UNREFERENCED(f); RemoteStorageUnsubscribePublishedFileResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageUnsubscribePublishedFileResult_t::k_iCallback, &r, sizeof(r)); }
uint32 StarSteamUGC::GetNumSubscribedItems() { return 0; }
uint32 StarSteamUGC::GetSubscribedItems(PublishedFileId_t* p, uint32 c) { STAR_UNREFERENCED(p); STAR_UNREFERENCED(c); return 0; }
uint32 StarSteamUGC::GetItemState(PublishedFileId_t f) { STAR_UNREFERENCED(f); return 0; }
bool StarSteamUGC::GetItemInstallInfo(PublishedFileId_t f, uint64* s, char* p, uint32 c, uint32* t) { STAR_UNREFERENCED(f); STAR_UNREFERENCED(s); STAR_UNREFERENCED(p); STAR_UNREFERENCED(c); STAR_UNREFERENCED(t); return false; }
bool StarSteamUGC::GetItemDownloadInfo(PublishedFileId_t f, uint64* d, uint64* t) { STAR_UNREFERENCED(f); if(d) *d=0; if(t) *t=0; return false; }
bool StarSteamUGC::DownloadItem(PublishedFileId_t f, bool h) { STAR_UNREFERENCED(f); STAR_UNREFERENCED(h); return false; }
bool StarSteamUGC::BInitWorkshopForGameServer(DepotId_t d, const char* f) { STAR_UNREFERENCED(d); STAR_UNREFERENCED(f); return false; }
void StarSteamUGC::SuspendDownloads(bool b) { STAR_UNREFERENCED(b); }
