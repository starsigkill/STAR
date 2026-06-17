#pragma once
#include "core/star_common.h"
#include "steam/isteamugc007.h"

class StarSteamUGC : public ISteamUGC007 {
public:
    static StarSteamUGC& get();
    UGCQueryHandle_t CreateQueryUserUGCRequest(AccountID_t unAccountID, EUserUGCList eListType, EUGCMatchingUGCType eMatchingUGCType, EUserUGCListSortOrder eSortOrder, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage) override;
    UGCQueryHandle_t CreateQueryAllUGCRequest(EUGCQuery eQueryType, EUGCMatchingUGCType eMatchingeMatchingUGCTypeFileType, AppId_t nCreatorAppID, AppId_t nConsumerAppID, uint32 unPage) override;
    UGCQueryHandle_t CreateQueryUGCDetailsRequest(PublishedFileId_t* pvecPublishedFileID, uint32 unNumPublishedFileIDs) override;
    SteamAPICall_t SendQueryUGCRequest(UGCQueryHandle_t handle) override;
    bool GetQueryUGCResult_old(UGCQueryHandle_t handle, uint32 index, SteamUGCDetails_t* pDetails) override;
    bool GetQueryUGCPreviewURL(UGCQueryHandle_t handle, uint32 index, char* pchURL, uint32 cchURLSize) override;
    bool GetQueryUGCMetadata(UGCQueryHandle_t handle, uint32 index, char* pchMetadata, uint32 cchMetadatasize) override;
    bool GetQueryUGCChildren(UGCQueryHandle_t handle, uint32 index, PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries) override;
    bool GetQueryUGCStatistic(UGCQueryHandle_t handle, uint32 index, EItemStatistic eStatType, uint32* pStatValue) override;
    uint32 GetQueryUGCNumAdditionalPreviews(UGCQueryHandle_t handle, uint32 index) override;
    bool GetQueryUGCAdditionalPreview(UGCQueryHandle_t handle, uint32 index, uint32 previewIndex, char* pchURLOrVideoID, uint32 cchURLSize, bool* hz) override;
    uint32 GetQueryUGCNumKeyValueTags(UGCQueryHandle_t handle, uint32 index) override;
    bool GetQueryUGCKeyValueTag(UGCQueryHandle_t handle, uint32 index, uint32 keyValueTagIndex, char* pchKey, uint32 cchKeySize, char* pchValue, uint32 cchValueSize) override;
    bool ReleaseQueryUGCRequest(UGCQueryHandle_t handle) override;
    bool AddRequiredTag(UGCQueryHandle_t handle, const char* pTagName) override;
    bool AddExcludedTag(UGCQueryHandle_t handle, const char* pTagName) override;
    bool SetReturnKeyValueTags(UGCQueryHandle_t handle, bool bReturnKeyValueTags) override;
    bool SetReturnLongDescription(UGCQueryHandle_t handle, bool bReturnLongDescription) override;
    bool SetReturnMetadata(UGCQueryHandle_t handle, bool bReturnMetadata) override;
    bool SetReturnChildren(UGCQueryHandle_t handle, bool bReturnChildren) override;
    bool SetReturnAdditionalPreviews(UGCQueryHandle_t handle, bool bReturnAdditionalPreviews) override;
    bool SetReturnTotalOnly(UGCQueryHandle_t handle, bool bReturnTotalOnly) override;
    bool SetLanguage(UGCQueryHandle_t handle, const char* pchLanguage) override;
    bool SetAllowCachedResponse(UGCQueryHandle_t handle, uint32 unMaxAgeSeconds) override;
    bool SetCloudFileNameFilter(UGCQueryHandle_t handle, const char* pMatchCloudFileName) override;
    bool SetMatchAnyTag(UGCQueryHandle_t handle, bool bMatchAnyTag) override;
    bool SetSearchText(UGCQueryHandle_t handle, const char* pSearchText) override;
    bool SetRankedByTrendDays(UGCQueryHandle_t handle, uint32 unDays) override;
    bool AddRequiredKeyValueTag(UGCQueryHandle_t handle, const char* pKey, const char* pValue) override;
    SteamAPICall_t RequestUGCDetails_old(PublishedFileId_t nPublishedFileID, uint32 unMaxAgeSeconds) override;
    SteamAPICall_t CreateItem(AppId_t nConsumerAppId, EWorkshopFileType eFileType) override;
    UGCUpdateHandle_t StartItemUpdate(AppId_t nConsumerAppId, PublishedFileId_t nPublishedFileID) override;
    bool SetItemTitle(UGCUpdateHandle_t handle, const char* pchTitle) override;
    bool SetItemDescription(UGCUpdateHandle_t handle, const char* pchDescription) override;
    bool SetItemUpdateLanguage(UGCUpdateHandle_t handle, const char* pchLanguage) override;
    bool SetItemMetadata(UGCUpdateHandle_t handle, const char* pchMetaData) override;
    bool SetItemVisibility(UGCUpdateHandle_t handle, ERemoteStoragePublishedFileVisibility eVisibility) override;
    bool SetItemTags(UGCUpdateHandle_t updateHandle, const SteamParamStringArray_t* pTags) override;
    bool SetItemContent(UGCUpdateHandle_t handle, const char* pszContentFolder) override;
    bool SetItemPreview(UGCUpdateHandle_t handle, const char* pszPreviewFile) override;
    bool RemoveItemKeyValueTags(UGCUpdateHandle_t handle, const char* pchKey) override;
    bool AddItemKeyValueTag(UGCUpdateHandle_t handle, const char* pchKey, const char* pchValue) override;
    SteamAPICall_t SubmitItemUpdate(UGCUpdateHandle_t handle, const char* pchChangeNote) override;
    EItemUpdateStatus GetItemUpdateProgress(UGCUpdateHandle_t handle, uint64* punBytesProcessed, uint64* punBytesTotal) override;
    SteamAPICall_t SetUserItemVote(PublishedFileId_t nPublishedFileID, bool bVoteUp) override;
    SteamAPICall_t GetUserItemVote(PublishedFileId_t nPublishedFileID) override;
    SteamAPICall_t AddItemToFavorites(AppId_t nAppId, PublishedFileId_t nPublishedFileID) override;
    SteamAPICall_t RemoveItemFromFavorites(AppId_t nAppId, PublishedFileId_t nPublishedFileID) override;
    SteamAPICall_t SubscribeItem(PublishedFileId_t nPublishedFileID) override;
    SteamAPICall_t UnsubscribeItem(PublishedFileId_t nPublishedFileID) override;
    uint32 GetNumSubscribedItems() override;
    uint32 GetSubscribedItems(PublishedFileId_t* pvecPublishedFileID, uint32 cMaxEntries) override;
    uint32 GetItemState(PublishedFileId_t nPublishedFileID) override;
    bool GetItemInstallInfo(PublishedFileId_t nPublishedFileID, uint64* punSizeOnDisk, char* pchFolder, uint32 cchFolderSize, uint32* punTimeStamp) override;
    bool GetItemDownloadInfo(PublishedFileId_t nPublishedFileID, uint64* punBytesDownloaded, uint64* punBytesTotal) override;
    bool DownloadItem(PublishedFileId_t nPublishedFileID, bool bHighPriority) override;
    bool BInitWorkshopForGameServer(DepotId_t unWorkshopDepotID, const char* pszFolder) override;
    void SuspendDownloads(bool bSuspend) override;
private:
    StarSteamUGC() = default;
};
