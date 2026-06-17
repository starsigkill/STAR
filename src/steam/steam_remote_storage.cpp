#include "steam/steam_remote_storage.h"
#include "core/storage.h"
#include "core/callbacks.h"
#include "core/settings.h"
#include "steam/isteamremotestorage.h"

StarSteamRemoteStorage& StarSteamRemoteStorage::get()
{
    static StarSteamRemoteStorage instance;
    return instance;
}

bool StarSteamRemoteStorage::FileWrite(const char* pchFile, const void* pvData, int32 cubData)
{
    if (!pchFile) return false;
    return Storage::get().write_remote_file(pchFile, pvData, (size_t)cubData);
}

int32 StarSteamRemoteStorage::FileRead(const char* pchFile, void* pvData, int32 cubDataToRead)
{
    if (!pchFile || !pvData) return 0;
    std::vector<uint8_t> buf;
    if (!Storage::get().read_remote_file(pchFile, buf)) return 0;
    int32 to_copy = std::min(cubDataToRead, (int32)buf.size());
    memcpy(pvData, buf.data(), to_copy);
    return to_copy;
}

SteamAPICall_t StarSteamRemoteStorage::FileWriteAsync(const char* pchFile, const void* pvData, uint32 cubData)
{
    bool ok = FileWrite(pchFile, pvData, (int32)cubData);
    RemoteStorageFileWriteAsyncComplete_t result{};
    result.m_eResult = ok ? k_EResultOK : k_EResultFail;
    return STAR_PostCallResult(RemoteStorageFileWriteAsyncComplete_t::k_iCallback, &result, sizeof(result));
}

SteamAPICall_t StarSteamRemoteStorage::FileReadAsync(const char* pchFile, uint32 nOffset, uint32 cubToRead)
{
    RemoteStorageFileReadAsyncComplete_t result{};
    result.m_eResult = k_EResultFail;
    result.m_nOffset = nOffset;
    result.m_cubRead = 0;

    if (pchFile) {
        std::vector<uint8_t> buf;
        if (Storage::get().read_remote_file(pchFile, buf)) {
            uint32 available = (nOffset < (uint32)buf.size()) ? (uint32)(buf.size() - nOffset) : 0;
            uint32 to_read   = (cubToRead == 0 || cubToRead > available) ? available : cubToRead;

            SteamAPICall_t handle = STAR_ReserveCallHandle();

            result.m_hFileReadAsync = handle;
            result.m_eResult = k_EResultOK;
            result.m_cubRead = to_read;

            PendingAsyncRead pr;
            pr.data.assign(buf.begin() + nOffset, buf.begin() + nOffset + to_read);
            pending_reads_[handle] = std::move(pr);

            STAR_PostCallResult(RemoteStorageFileReadAsyncComplete_t::k_iCallback, &result, sizeof(result), false, handle);
            return handle;
        }
    }

    result.m_hFileReadAsync = k_uAPICallInvalid;
    return STAR_PostCallResult(RemoteStorageFileReadAsyncComplete_t::k_iCallback, &result, sizeof(result));
}


bool StarSteamRemoteStorage::FileReadAsyncComplete(SteamAPICall_t hReadCall, void* pvBuffer, uint32 cubToRead)
{
    if (!pvBuffer) return false;
    auto it = pending_reads_.find(hReadCall);
    if (it == pending_reads_.end()) return false;
    uint32 copy_sz = std::min(cubToRead, (uint32)it->second.data.size());
    memcpy(pvBuffer, it->second.data.data(), copy_sz);
    pending_reads_.erase(it);
    return true;
}

bool StarSteamRemoteStorage::FileForget(const char* pchFile) { STAR_UNREFERENCED(pchFile); return true; }

bool StarSteamRemoteStorage::FileDelete(const char* pchFile)
{
    if (!pchFile) return false;
    return Storage::get().delete_remote_file(pchFile);
}

SteamAPICall_t StarSteamRemoteStorage::FileShare(const char* pchFile)
{
    STAR_UNREFERENCED(pchFile);
    RemoteStorageFileShareResult_t result{};
    result.m_eResult = k_EResultOK;
    result.m_hFile = 1;
    return STAR_PostCallResult(RemoteStorageFileShareResult_t::k_iCallback, &result, sizeof(result));
}

bool StarSteamRemoteStorage::SetSyncPlatforms(const char* pchFile, ERemoteStoragePlatform eRemoteStoragePlatform)
{
    STAR_UNREFERENCED(pchFile); STAR_UNREFERENCED(eRemoteStoragePlatform);
    return true;
}

UGCFileWriteStreamHandle_t StarSteamRemoteStorage::FileWriteStreamOpen(const char* pchFile)
{
    if (!pchFile) return k_UGCFileStreamHandleInvalid;
    UGCFileWriteStreamHandle_t h = next_stream_handle_++;
    WriteStream ws;
    ws.filename = pchFile;
    streams_[h] = std::move(ws);
    return h;
}

bool StarSteamRemoteStorage::FileWriteStreamWriteChunk(UGCFileWriteStreamHandle_t writeHandle, const void* pvData, int32 cubData)
{
    auto it = streams_.find(writeHandle);
    if (it == streams_.end()) return false;
    if (pvData && cubData > 0) {
        auto* p = (const uint8_t*)pvData;
        it->second.data.insert(it->second.data.end(), p, p + cubData);
    }
    return true;
}

bool StarSteamRemoteStorage::FileWriteStreamClose(UGCFileWriteStreamHandle_t writeHandle)
{
    auto it = streams_.find(writeHandle);
    if (it == streams_.end()) return false;
    Storage::get().write_remote_file(it->second.filename, it->second.data.data(), it->second.data.size());
    streams_.erase(it);
    return true;
}

bool StarSteamRemoteStorage::FileWriteStreamCancel(UGCFileWriteStreamHandle_t writeHandle)
{
    streams_.erase(writeHandle);
    return true;
}

bool StarSteamRemoteStorage::FileExists(const char* pchFile)
{
    if (!pchFile) return false;
    return Storage::get().remote_file_exists(pchFile);
}

bool StarSteamRemoteStorage::FilePersisted(const char* pchFile) { STAR_UNREFERENCED(pchFile); return true; }

int32 StarSteamRemoteStorage::GetFileSize(const char* pchFile)
{
    if (!pchFile) return 0;
    int64_t sz = Storage::get().remote_file_size(pchFile);
    if (sz < 0) return 0;
    return (int32)sz;
}

int64 StarSteamRemoteStorage::GetFileTimestamp(const char* pchFile)
{
    if (!pchFile) return 0;
    std::string path = Storage::get().remote_path(pchFile);
    try {
        auto ftime = std::filesystem::last_write_time(path);

        auto sys = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
        );
        return (int64)std::chrono::system_clock::to_time_t(sys);
    } catch (...) { return 0; }
}

ERemoteStoragePlatform StarSteamRemoteStorage::GetSyncPlatforms(const char* pchFile)
{
    STAR_UNREFERENCED(pchFile);
    return k_ERemoteStoragePlatformAll;
}

int32 StarSteamRemoteStorage::GetFileCount()
{
    cached_filelist_ = Storage::get().list_remote_files();
    return (int32)cached_filelist_.size();
}

const char* StarSteamRemoteStorage::GetFileNameAndSize(int iFile, int32* pnFileSizeInBytes)
{
    if (iFile < 0 || iFile >= (int)cached_filelist_.size()) return nullptr;
    if (pnFileSizeInBytes) {
        *pnFileSizeInBytes = (int32)Storage::get().remote_file_size(cached_filelist_[iFile]);
    }
    return cached_filelist_[iFile].c_str();
}

bool StarSteamRemoteStorage::GetQuota(int32* pnTotalBytes, int32* puAvailableBytes)
{
    if (pnTotalBytes) *pnTotalBytes = 100 * 1024 * 1024;
    if (puAvailableBytes) *puAvailableBytes = 99 * 1024 * 1024;
    return true;
}

bool StarSteamRemoteStorage::IsCloudEnabledForAccount() { return true; }
bool StarSteamRemoteStorage::IsCloudEnabledForApp() { return true; }
void StarSteamRemoteStorage::SetCloudEnabledForApp(bool bEnabled) { STAR_UNREFERENCED(bEnabled); }

SteamAPICall_t StarSteamRemoteStorage::UGCDownload(UGCHandle_t hContent, uint32 unPriority)
{
    STAR_UNREFERENCED(unPriority);
    RemoteStorageDownloadUGCResult_t result{};
    result.m_eResult = k_EResultFail;
    result.m_hFile = hContent;
    return STAR_PostCallResult(RemoteStorageDownloadUGCResult_t::k_iCallback, &result, sizeof(result));
}

bool StarSteamRemoteStorage::GetUGCDownloadProgress(UGCHandle_t hContent, int32* pnBytesDownloaded, int32* pnBytesExpected)
{
    STAR_UNREFERENCED(hContent);
    if (pnBytesDownloaded) *pnBytesDownloaded = 0;
    if (pnBytesExpected) *pnBytesExpected = 0;
    return false;
}

bool StarSteamRemoteStorage::GetUGCDetails(UGCHandle_t hContent, AppId_t* pnAppID, char** ppchName, int32* pnFileSizeInBytes, CSteamID* pSteamIDOwner)
{
    STAR_UNREFERENCED(hContent);
    if (pnAppID) *pnAppID = 0;
    if (ppchName) *ppchName = nullptr;
    if (pnFileSizeInBytes) *pnFileSizeInBytes = 0;
    if (pSteamIDOwner) *pSteamIDOwner = k_steamIDNil;
    return false;
}

int32 StarSteamRemoteStorage::UGCRead(UGCHandle_t hContent, void* pvData, int32 cubDataToRead, uint32 cOffset, EUGCReadAction eAction) { STAR_UNREFERENCED(hContent); STAR_UNREFERENCED(pvData); STAR_UNREFERENCED(cubDataToRead); STAR_UNREFERENCED(cOffset); STAR_UNREFERENCED(eAction); return 0; }
int32 StarSteamRemoteStorage::GetCachedUGCCount() { return 0; }
UGCHandle_t StarSteamRemoteStorage::GetCachedUGCHandle(int32 iCachedContent) { STAR_UNREFERENCED(iCachedContent); return k_UGCHandleInvalid; }

SteamAPICall_t StarSteamRemoteStorage::PublishWorkshopFile(const char* pchFile, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags, EWorkshopFileType eWorkshopFileType) { STAR_UNREFERENCED(pchFile); STAR_UNREFERENCED(pchPreviewFile); STAR_UNREFERENCED(nConsumerAppId); STAR_UNREFERENCED(pchTitle); STAR_UNREFERENCED(pchDescription); STAR_UNREFERENCED(eVisibility); STAR_UNREFERENCED(pTags); STAR_UNREFERENCED(eWorkshopFileType); RemoteStoragePublishFileResult_t r{}; r.m_eResult = k_EResultFail; return STAR_PostCallResult(RemoteStoragePublishFileResult_t::k_iCallback, &r, sizeof(r)); }
PublishedFileUpdateHandle_t StarSteamRemoteStorage::CreatePublishedFileUpdateRequest(PublishedFileId_t unPublishedFileId) { STAR_UNREFERENCED(unPublishedFileId); return k_PublishedFileUpdateHandleInvalid; }
bool StarSteamRemoteStorage::UpdatePublishedFileFile(PublishedFileUpdateHandle_t h, const char* f) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(f); return false; }
bool StarSteamRemoteStorage::UpdatePublishedFilePreviewFile(PublishedFileUpdateHandle_t h, const char* f) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(f); return false; }
bool StarSteamRemoteStorage::UpdatePublishedFileTitle(PublishedFileUpdateHandle_t h, const char* t) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(t); return false; }
bool StarSteamRemoteStorage::UpdatePublishedFileDescription(PublishedFileUpdateHandle_t h, const char* d) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(d); return false; }
bool StarSteamRemoteStorage::UpdatePublishedFileVisibility(PublishedFileUpdateHandle_t h, ERemoteStoragePublishedFileVisibility v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(v); return false; }
bool StarSteamRemoteStorage::UpdatePublishedFileTags(PublishedFileUpdateHandle_t h, SteamParamStringArray_t* t) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(t); return false; }
SteamAPICall_t StarSteamRemoteStorage::CommitPublishedFileUpdate(PublishedFileUpdateHandle_t h) { STAR_UNREFERENCED(h); RemoteStorageUpdatePublishedFileResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageUpdatePublishedFileResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::GetPublishedFileDetails(PublishedFileId_t f, uint32 s) { STAR_UNREFERENCED(f); STAR_UNREFERENCED(s); RemoteStorageGetPublishedFileDetailsResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageGetPublishedFileDetailsResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::DeletePublishedFile(PublishedFileId_t f) { STAR_UNREFERENCED(f); RemoteStorageDeletePublishedFileResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageDeletePublishedFileResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::EnumerateUserPublishedFiles(uint32 s) { STAR_UNREFERENCED(s); RemoteStorageEnumerateUserPublishedFilesResult_t r{}; r.m_eResult=k_EResultOK; r.m_nResultsReturned=0; r.m_nTotalResultCount=0; return STAR_PostCallResult(RemoteStorageEnumerateUserPublishedFilesResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::SubscribePublishedFile(PublishedFileId_t f) { STAR_UNREFERENCED(f); RemoteStorageSubscribePublishedFileResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageSubscribePublishedFileResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::EnumerateUserSubscribedFiles(uint32 s) { STAR_UNREFERENCED(s); RemoteStorageEnumerateUserSubscribedFilesResult_t r{}; r.m_eResult=k_EResultOK; r.m_nResultsReturned=0; r.m_nTotalResultCount=0; return STAR_PostCallResult(RemoteStorageEnumerateUserSubscribedFilesResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::UnsubscribePublishedFile(PublishedFileId_t f) { STAR_UNREFERENCED(f); RemoteStorageUnsubscribePublishedFileResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageUnsubscribePublishedFileResult_t::k_iCallback, &r, sizeof(r)); }
bool StarSteamRemoteStorage::UpdatePublishedFileSetChangeDescription(PublishedFileUpdateHandle_t h, const char* d) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(d); return false; }
SteamAPICall_t StarSteamRemoteStorage::GetPublishedItemVoteDetails(PublishedFileId_t f) { STAR_UNREFERENCED(f); RemoteStorageGetPublishedItemVoteDetailsResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageGetPublishedItemVoteDetailsResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::UpdateUserPublishedItemVote(PublishedFileId_t f, bool v) { STAR_UNREFERENCED(f); STAR_UNREFERENCED(v); RemoteStorageUpdateUserPublishedItemVoteResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageUpdateUserPublishedItemVoteResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::GetUserPublishedItemVoteDetails(PublishedFileId_t f) { STAR_UNREFERENCED(f); RemoteStorageGetPublishedItemVoteDetailsResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageGetPublishedItemVoteDetailsResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::EnumerateUserSharedWorkshopFiles(CSteamID s, uint32 i, SteamParamStringArray_t* r, SteamParamStringArray_t* e) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(i); STAR_UNREFERENCED(r); STAR_UNREFERENCED(e); RemoteStorageEnumerateUserPublishedFilesResult_t res{}; res.m_eResult=k_EResultOK; res.m_nResultsReturned=0; return STAR_PostCallResult(RemoteStorageEnumerateUserPublishedFilesResult_t::k_iCallback, &res, sizeof(res)); }
SteamAPICall_t StarSteamRemoteStorage::PublishVideo(EWorkshopVideoProvider vp, const char* va, const char* vi, const char* pf, AppId_t ai, const char* t, const char* d, ERemoteStoragePublishedFileVisibility v, SteamParamStringArray_t* tags) { STAR_UNREFERENCED(vp); STAR_UNREFERENCED(va); STAR_UNREFERENCED(vi); STAR_UNREFERENCED(pf); STAR_UNREFERENCED(ai); STAR_UNREFERENCED(t); STAR_UNREFERENCED(d); STAR_UNREFERENCED(v); STAR_UNREFERENCED(tags); RemoteStoragePublishFileResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStoragePublishFileResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::SetUserPublishedFileAction(PublishedFileId_t f, EWorkshopFileAction a) { STAR_UNREFERENCED(f); STAR_UNREFERENCED(a); RemoteStorageSetUserPublishedFileActionResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageSetUserPublishedFileActionResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::EnumeratePublishedFilesByUserAction(EWorkshopFileAction a, uint32 s) { STAR_UNREFERENCED(a); STAR_UNREFERENCED(s); RemoteStorageEnumeratePublishedFilesByUserActionResult_t r{}; r.m_eResult=k_EResultOK; r.m_nResultsReturned=0; return STAR_PostCallResult(RemoteStorageEnumeratePublishedFilesByUserActionResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::EnumeratePublishedWorkshopFiles(EWorkshopEnumerationType e, uint32 s, uint32 c, uint32 d, SteamParamStringArray_t* t, SteamParamStringArray_t* u) { STAR_UNREFERENCED(e); STAR_UNREFERENCED(s); STAR_UNREFERENCED(c); STAR_UNREFERENCED(d); STAR_UNREFERENCED(t); STAR_UNREFERENCED(u); RemoteStorageEnumerateWorkshopFilesResult_t r{}; r.m_eResult=k_EResultOK; r.m_nResultsReturned=0; return STAR_PostCallResult(RemoteStorageEnumerateWorkshopFilesResult_t::k_iCallback, &r, sizeof(r)); }
SteamAPICall_t StarSteamRemoteStorage::UGCDownloadToLocation(UGCHandle_t h, const char* l, uint32 p) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(l); STAR_UNREFERENCED(p); RemoteStorageDownloadUGCResult_t r{}; r.m_eResult=k_EResultFail; return STAR_PostCallResult(RemoteStorageDownloadUGCResult_t::k_iCallback, &r, sizeof(r)); }

int32 StarSteamRemoteStorage::UGCRead(UGCHandle_t h, void* pvData, int32 cubDataToRead) { return UGCRead(h, pvData, cubDataToRead, 0, k_EUGCRead_ContinueReadingUntilFinished); }
int32 StarSteamRemoteStorage::UGCRead(UGCHandle_t h, void* pvData, int32 cubDataToRead, uint32 cOffset) { return UGCRead(h, pvData, cubDataToRead, cOffset, k_EUGCRead_ContinueReadingUntilFinished); }
SteamAPICall_t StarSteamRemoteStorage::UGCDownload(UGCHandle_t h) { return UGCDownload(h, 0); }
bool StarSteamRemoteStorage::GetUGCDownloadProgress(UGCHandle_t h, uint32* pDownloaded, uint32* pTotal) { if (pDownloaded) *pDownloaded = 0; if (pTotal) *pTotal = 0; STAR_UNREFERENCED(h); return false; }
SteamAPICall_t StarSteamRemoteStorage::GetPublishedFileDetails(PublishedFileId_t f) { return GetPublishedFileDetails(f, 0); }
bool StarSteamRemoteStorage::GetQuota(uint64* pnTotalBytes, uint64* puAvailableBytes) { if (pnTotalBytes) *pnTotalBytes = 100ull * 1024 * 1024; if (puAvailableBytes) *puAvailableBytes = 100ull * 1024 * 1024; return true; }

SteamAPICall_t StarSteamRemoteStorage::PublishFile(const char* f, const char* pf, AppId_t a, const char* t, const char* d, ERemoteStoragePublishedFileVisibility v, SteamParamStringArray_t* tags)
{
    STAR_UNREFERENCED(f); STAR_UNREFERENCED(pf); STAR_UNREFERENCED(a); STAR_UNREFERENCED(t); STAR_UNREFERENCED(d); STAR_UNREFERENCED(v); STAR_UNREFERENCED(tags);
    RemoteStoragePublishFileResult_t r{}; r.m_eResult = k_EResultFail;
    return STAR_PostCallResult(RemoteStoragePublishFileResult_t::k_iCallback, &r, sizeof(r));
}
SteamAPICall_t StarSteamRemoteStorage::PublishWorkshopFile(const char* f, const char* pf, AppId_t a, const char* t, const char* d, SteamParamStringArray_t* tags)
{
    STAR_UNREFERENCED(f); STAR_UNREFERENCED(pf); STAR_UNREFERENCED(a); STAR_UNREFERENCED(t); STAR_UNREFERENCED(d); STAR_UNREFERENCED(tags);
    RemoteStoragePublishFileResult_t r{}; r.m_eResult = k_EResultFail;
    return STAR_PostCallResult(RemoteStoragePublishFileResult_t::k_iCallback, &r, sizeof(r));
}
SteamAPICall_t StarSteamRemoteStorage::UpdatePublishedFile(RemoteStorageUpdatePublishedFileRequest_t req)
{
    STAR_UNREFERENCED(req);
    RemoteStorageUpdatePublishedFileResult_t r{}; r.m_eResult = k_EResultFail;
    return STAR_PostCallResult(RemoteStorageUpdatePublishedFileResult_t::k_iCallback, &r, sizeof(r));
}

SteamAPICall_t StarSteamRemoteStorage::PublishVideo(const char* url, const char* pf, AppId_t a, const char* t, const char* d, ERemoteStoragePublishedFileVisibility v, SteamParamStringArray_t* tags)
{
    STAR_UNREFERENCED(url); STAR_UNREFERENCED(pf); STAR_UNREFERENCED(a); STAR_UNREFERENCED(t); STAR_UNREFERENCED(d); STAR_UNREFERENCED(v); STAR_UNREFERENCED(tags);
    RemoteStoragePublishFileResult_t r{}; r.m_eResult = k_EResultFail;
    return STAR_PostCallResult(RemoteStoragePublishFileResult_t::k_iCallback, &r, sizeof(r));
}

int32 StarSteamRemoteStorage::GetLocalFileChangeCount() { return 0; }
const char* StarSteamRemoteStorage::GetLocalFileChange(int iFile, ERemoteStorageLocalFileChange* pEChangeType, ERemoteStorageFilePathType* pEFilePathType)
{
    STAR_UNREFERENCED(iFile);
    if (pEChangeType) *pEChangeType = k_ERemoteStorageLocalFileChange_Invalid;
    if (pEFilePathType) *pEFilePathType = k_ERemoteStorageFilePathType_Invalid;
    return "";
}

bool StarSteamRemoteStorage::BeginFileWriteBatch() { return true; }
bool StarSteamRemoteStorage::EndFileWriteBatch() { return true; }
