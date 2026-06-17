#pragma once
#include "core/star_common.h"
#include "steam/isteamremotestorage001.h"
#include "steam/isteamremotestorage002.h"
#include "steam/isteamremotestorage003.h"
#include "steam/isteamremotestorage004.h"
#include "steam/isteamremotestorage005.h"
#include "steam/isteamremotestorage006.h"
#include "steam/isteamremotestorage007.h"
#include "steam/isteamremotestorage008.h"
#include "steam/isteamremotestorage009.h"
#include "steam/isteamremotestorage010.h"
#include "steam/isteamremotestorage011.h"
#include "steam/isteamremotestorage012.h"
#include "steam/isteamremotestorage013.h"
#include "steam/isteamremotestorage014.h"
#include "steam/isteamremotestorage015.h"

class StarSteamRemoteStorage :
    public ISteamRemoteStorage001,
    public ISteamRemoteStorage002,
    public ISteamRemoteStorage003,
    public ISteamRemoteStorage004,
    public ISteamRemoteStorage005,
    public ISteamRemoteStorage006,
    public ISteamRemoteStorage007,
    public ISteamRemoteStorage008,
    public ISteamRemoteStorage009,
    public ISteamRemoteStorage010,
    public ISteamRemoteStorage011,
    public ISteamRemoteStorage012,
    public ISteamRemoteStorage013,
    public ISteamRemoteStorage014,
    public ISteamRemoteStorage015,
    public ISteamRemoteStorage {
public:
    static StarSteamRemoteStorage& get();

    int32 UGCRead(UGCHandle_t hContent, void* pvData, int32 cubDataToRead) override;
    int32 UGCRead(UGCHandle_t hContent, void* pvData, int32 cubDataToRead, uint32 cOffset) override;
    SteamAPICall_t UGCDownload(UGCHandle_t hContent) override;
    bool GetUGCDownloadProgress(UGCHandle_t hContent, uint32* puDownloadedBytes, uint32* puTotalBytes) override;
    SteamAPICall_t GetPublishedFileDetails(PublishedFileId_t unPublishedFileId) override;
    bool GetQuota(uint64* pnTotalBytes, uint64* puAvailableBytes) override;

    SteamAPICall_t PublishFile(const char* pchFile, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags) override;
    SteamAPICall_t PublishWorkshopFile(const char* pchFile, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, SteamParamStringArray_t* pTags) override;
    SteamAPICall_t UpdatePublishedFile(RemoteStorageUpdatePublishedFileRequest_t updatePublishedFileRequest) override;

    SteamAPICall_t PublishVideo(const char* pchVideoURL, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags) override;

    int32 GetLocalFileChangeCount() override;
    const char* GetLocalFileChange(int iFile, ERemoteStorageLocalFileChange* pEChangeType, ERemoteStorageFilePathType* pEFilePathType) override;

    bool BeginFileWriteBatch() override;
    bool EndFileWriteBatch() override;

    bool FileWrite(const char* pchFile, const void* pvData, int32 cubData) override;
    int32 FileRead(const char* pchFile, void* pvData, int32 cubDataToRead) override;
    SteamAPICall_t FileWriteAsync(const char* pchFile, const void* pvData, uint32 cubData) override;
    SteamAPICall_t FileReadAsync(const char* pchFile, uint32 nOffset, uint32 cubToRead) override;
    bool FileReadAsyncComplete(SteamAPICall_t hReadCall, void* pvBuffer, uint32 cubToRead) override;
    bool FileForget(const char* pchFile) override;
    bool FileDelete(const char* pchFile) override;
    SteamAPICall_t FileShare(const char* pchFile) override;
    bool SetSyncPlatforms(const char* pchFile, ERemoteStoragePlatform eRemoteStoragePlatform) override;
    UGCFileWriteStreamHandle_t FileWriteStreamOpen(const char* pchFile) override;
    bool FileWriteStreamWriteChunk(UGCFileWriteStreamHandle_t writeHandle, const void* pvData, int32 cubData) override;
    bool FileWriteStreamClose(UGCFileWriteStreamHandle_t writeHandle) override;
    bool FileWriteStreamCancel(UGCFileWriteStreamHandle_t writeHandle) override;
    bool FileExists(const char* pchFile) override;
    bool FilePersisted(const char* pchFile) override;
    int32 GetFileSize(const char* pchFile) override;
    int64 GetFileTimestamp(const char* pchFile) override;
    ERemoteStoragePlatform GetSyncPlatforms(const char* pchFile) override;
    int32 GetFileCount() override;
    const char* GetFileNameAndSize(int iFile, int32* pnFileSizeInBytes) override;
    bool GetQuota(int32* pnTotalBytes, int32* puAvailableBytes) override;
    bool IsCloudEnabledForAccount() override;
    bool IsCloudEnabledForApp() override;
    void SetCloudEnabledForApp(bool bEnabled) override;
    SteamAPICall_t UGCDownload(UGCHandle_t hContent, uint32 unPriority) override;
    bool GetUGCDownloadProgress(UGCHandle_t hContent, int32* pnBytesDownloaded, int32* pnBytesExpected) override;
    bool GetUGCDetails(UGCHandle_t hContent, AppId_t* pnAppID, char** ppchName, int32* pnFileSizeInBytes, CSteamID* pSteamIDOwner) override;
    int32 UGCRead(UGCHandle_t hContent, void* pvData, int32 cubDataToRead, uint32 cOffset, EUGCReadAction eAction) override;
    int32 GetCachedUGCCount() override;
    UGCHandle_t GetCachedUGCHandle(int32 iCachedContent) override;
    SteamAPICall_t PublishWorkshopFile(const char* pchFile, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags, EWorkshopFileType eWorkshopFileType) override;
    PublishedFileUpdateHandle_t CreatePublishedFileUpdateRequest(PublishedFileId_t unPublishedFileId) override;
    bool UpdatePublishedFileFile(PublishedFileUpdateHandle_t updateHandle, const char* pchFile) override;
    bool UpdatePublishedFilePreviewFile(PublishedFileUpdateHandle_t updateHandle, const char* pchPreviewFile) override;
    bool UpdatePublishedFileTitle(PublishedFileUpdateHandle_t updateHandle, const char* pchTitle) override;
    bool UpdatePublishedFileDescription(PublishedFileUpdateHandle_t updateHandle, const char* pchDescription) override;
    bool UpdatePublishedFileVisibility(PublishedFileUpdateHandle_t updateHandle, ERemoteStoragePublishedFileVisibility eVisibility) override;
    bool UpdatePublishedFileTags(PublishedFileUpdateHandle_t updateHandle, SteamParamStringArray_t* pTags) override;
    SteamAPICall_t CommitPublishedFileUpdate(PublishedFileUpdateHandle_t updateHandle) override;
    SteamAPICall_t GetPublishedFileDetails(PublishedFileId_t unPublishedFileId, uint32 unMaxSecondsOld) override;
    SteamAPICall_t DeletePublishedFile(PublishedFileId_t unPublishedFileId) override;
    SteamAPICall_t EnumerateUserPublishedFiles(uint32 unStartIndex) override;
    SteamAPICall_t SubscribePublishedFile(PublishedFileId_t unPublishedFileId) override;
    SteamAPICall_t EnumerateUserSubscribedFiles(uint32 unStartIndex) override;
    SteamAPICall_t UnsubscribePublishedFile(PublishedFileId_t unPublishedFileId) override;
    bool UpdatePublishedFileSetChangeDescription(PublishedFileUpdateHandle_t updateHandle, const char* pchChangeDescription) override;
    SteamAPICall_t GetPublishedItemVoteDetails(PublishedFileId_t unPublishedFileId) override;
    SteamAPICall_t UpdateUserPublishedItemVote(PublishedFileId_t unPublishedFileId, bool bVoteUp) override;
    SteamAPICall_t GetUserPublishedItemVoteDetails(PublishedFileId_t unPublishedFileId) override;
    SteamAPICall_t EnumerateUserSharedWorkshopFiles(CSteamID steamId, uint32 unStartIndex, SteamParamStringArray_t* pRequiredTags, SteamParamStringArray_t* pExcludedTags) override;
    SteamAPICall_t PublishVideo(EWorkshopVideoProvider eVideoProvider, const char* pchVideoAccount, const char* pchVideoIdentifier, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags) override;
    SteamAPICall_t SetUserPublishedFileAction(PublishedFileId_t unPublishedFileId, EWorkshopFileAction eAction) override;
    SteamAPICall_t EnumeratePublishedFilesByUserAction(EWorkshopFileAction eAction, uint32 unStartIndex) override;
    SteamAPICall_t EnumeratePublishedWorkshopFiles(EWorkshopEnumerationType eEnumerationType, uint32 unStartIndex, uint32 unCount, uint32 unDays, SteamParamStringArray_t* pTags, SteamParamStringArray_t* pUserTags) override;
    SteamAPICall_t UGCDownloadToLocation(UGCHandle_t hContent, const char* pchLocation, uint32 unPriority) override;

private:
    StarSteamRemoteStorage() = default;

    struct WriteStream { std::string filename; std::vector<uint8_t> data; };
    std::map<UGCFileWriteStreamHandle_t, WriteStream> streams_;
    std::vector<std::string> cached_filelist_;
    UGCFileWriteStreamHandle_t next_stream_handle_ = 1;

    struct PendingAsyncRead { std::vector<uint8_t> data; };
    std::map<SteamAPICall_t, PendingAsyncRead> pending_reads_;
};
