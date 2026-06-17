#include "steam/steam_inventory.h"
#include "core/callbacks.h"
#include "steam/isteaminventory.h"

StarSteamInventory& StarSteamInventory::get() { static StarSteamInventory i; return i; }

EResult StarSteamInventory::GetResultStatus(SteamInventoryResult_t r) { return (r == kValidResult) ? k_EResultOK : k_EResultFail; }
bool StarSteamInventory::GetResultItems(SteamInventoryResult_t r, SteamItemDetails_t* p, uint32* n) { STAR_UNREFERENCED(r); if(n) *n=0; STAR_UNREFERENCED(p); return false; }
bool StarSteamInventory::GetResultItemProperty(SteamInventoryResult_t r, uint32 i, const char* n, char* v, uint32* s) { STAR_UNREFERENCED(r); STAR_UNREFERENCED(i); STAR_UNREFERENCED(n); STAR_UNREFERENCED(v); if(s) *s=0; return false; }
uint32 StarSteamInventory::GetResultTimestamp(SteamInventoryResult_t r) { STAR_UNREFERENCED(r); return 0; }
bool StarSteamInventory::CheckResultSteamID(SteamInventoryResult_t r, CSteamID s) { STAR_UNREFERENCED(r); STAR_UNREFERENCED(s); return false; }
void StarSteamInventory::DestroyResult(SteamInventoryResult_t r) { STAR_UNREFERENCED(r); }

bool StarSteamInventory::GetAllItems(SteamInventoryResult_t* pResultHandle)
{
    if (pResultHandle) *pResultHandle = kValidResult;
    SteamInventoryResultReady_t cb{}; cb.m_handle=kValidResult; cb.m_result=k_EResultOK;
    STAR_DispatchCallback(SteamInventoryResultReady_t::k_iCallback, &cb, sizeof(cb));
    return true;
}

bool StarSteamInventory::GetItemsByID(SteamInventoryResult_t* p, const SteamItemInstanceID_t* ids, uint32 n) { STAR_UNREFERENCED(ids); STAR_UNREFERENCED(n); if(p) *p=kValidResult; return true; }
bool StarSteamInventory::SerializeResult(SteamInventoryResult_t r, void* b, uint32* s) { STAR_UNREFERENCED(r); STAR_UNREFERENCED(b); if(s) *s=0; return false; }
bool StarSteamInventory::DeserializeResult(SteamInventoryResult_t* p, const void* b, uint32 s, bool r) { STAR_UNREFERENCED(b); STAR_UNREFERENCED(s); STAR_UNREFERENCED(r); if(p) *p=k_SteamInventoryResultInvalid; return false; }
bool StarSteamInventory::GenerateItems(SteamInventoryResult_t* p, const SteamItemDef_t* d, const uint32* q, uint32 n) { STAR_UNREFERENCED(d); STAR_UNREFERENCED(q); STAR_UNREFERENCED(n); if(p) *p=k_SteamInventoryResultInvalid; return false; }
bool StarSteamInventory::GrantPromoItems(SteamInventoryResult_t* p) { if(p) *p=k_SteamInventoryResultInvalid; return false; }
bool StarSteamInventory::AddPromoItem(SteamInventoryResult_t* p, SteamItemDef_t d) { STAR_UNREFERENCED(d); if(p) *p=k_SteamInventoryResultInvalid; return false; }
bool StarSteamInventory::AddPromoItems(SteamInventoryResult_t* p, const SteamItemDef_t* d, uint32 n) { STAR_UNREFERENCED(d); STAR_UNREFERENCED(n); if(p) *p=k_SteamInventoryResultInvalid; return false; }
bool StarSteamInventory::ConsumeItem(SteamInventoryResult_t* p, SteamItemInstanceID_t i, uint32 q) { STAR_UNREFERENCED(i); STAR_UNREFERENCED(q); if(p) *p=k_SteamInventoryResultInvalid; return false; }
bool StarSteamInventory::ExchangeItems(SteamInventoryResult_t* p, const SteamItemDef_t* g, const uint32* gq, uint32 gl, const SteamItemInstanceID_t* d, const uint32* dq, uint32 dl) { STAR_UNREFERENCED(g); STAR_UNREFERENCED(gq); STAR_UNREFERENCED(gl); STAR_UNREFERENCED(d); STAR_UNREFERENCED(dq); STAR_UNREFERENCED(dl); if(p) *p=k_SteamInventoryResultInvalid; return false; }
bool StarSteamInventory::TransferItemQuantity(SteamInventoryResult_t* p, SteamItemInstanceID_t s, uint32 q, SteamItemInstanceID_t d) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(q); STAR_UNREFERENCED(d); if(p) *p=k_SteamInventoryResultInvalid; return false; }
void StarSteamInventory::SendItemDropHeartbeat() {}
bool StarSteamInventory::TriggerItemDrop(SteamInventoryResult_t* p, SteamItemDef_t d) { STAR_UNREFERENCED(d); if(p) *p=k_SteamInventoryResultInvalid; return false; }
bool StarSteamInventory::TradeItems(SteamInventoryResult_t* p, CSteamID s, const SteamItemInstanceID_t* g, const uint32* gq, uint32 gl, const SteamItemInstanceID_t* ge, const uint32* geq, uint32 gel) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(g); STAR_UNREFERENCED(gq); STAR_UNREFERENCED(gl); STAR_UNREFERENCED(ge); STAR_UNREFERENCED(geq); STAR_UNREFERENCED(gel); if(p) *p=k_SteamInventoryResultInvalid; return false; }

bool StarSteamInventory::LoadItemDefinitions()
{
    SteamInventoryDefinitionUpdate_t cb{};
    STAR_DispatchCallback(SteamInventoryDefinitionUpdate_t::k_iCallback, &cb, sizeof(cb));
    return true;
}

bool StarSteamInventory::GetItemDefinitionIDs(SteamItemDef_t* p, uint32* n) { if(n) *n=0; STAR_UNREFERENCED(p); return false; }
bool StarSteamInventory::GetItemDefinitionProperty(SteamItemDef_t d, const char* n, char* v, uint32* s) { STAR_UNREFERENCED(d); STAR_UNREFERENCED(n); STAR_UNREFERENCED(v); if(s) *s=0; return false; }
SteamAPICall_t StarSteamInventory::RequestEligiblePromoItemDefinitionsIDs(CSteamID s) { STAR_UNREFERENCED(s); SteamInventoryEligiblePromoItemDefIDs_t r{}; r.m_result=k_EResultOK; r.m_numEligiblePromoItemDefs=0; return STAR_PostCallResult(SteamInventoryEligiblePromoItemDefIDs_t::k_iCallback, &r, sizeof(r)); }
bool StarSteamInventory::GetEligiblePromoItemDefinitionIDs(CSteamID s, SteamItemDef_t* p, uint32* n) { STAR_UNREFERENCED(s); STAR_UNREFERENCED(p); if(n) *n=0; return false; }
SteamAPICall_t StarSteamInventory::StartPurchase(const SteamItemDef_t* d, const uint32* q, uint32 n) { STAR_UNREFERENCED(d); STAR_UNREFERENCED(q); STAR_UNREFERENCED(n); return k_uAPICallInvalid; }
SteamAPICall_t StarSteamInventory::RequestPrices() { return k_uAPICallInvalid; }
uint32 StarSteamInventory::GetNumItemsWithPrices() { return 0; }
bool StarSteamInventory::GetItemsWithPrices(SteamItemDef_t* d, uint64* cp, uint64* bp, uint32 n) { STAR_UNREFERENCED(d); STAR_UNREFERENCED(cp); STAR_UNREFERENCED(bp); STAR_UNREFERENCED(n); return false; }
bool StarSteamInventory::GetItemPrice(SteamItemDef_t d, uint64* cp, uint64* bp) { STAR_UNREFERENCED(d); if(cp) *cp=0; if(bp) *bp=0; return false; }
SteamInventoryUpdateHandle_t StarSteamInventory::StartUpdateProperties() { return k_SteamInventoryUpdateHandleInvalid; }
bool StarSteamInventory::RemoveProperty(SteamInventoryUpdateHandle_t h, SteamItemInstanceID_t id, const char* n) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(id); STAR_UNREFERENCED(n); return false; }
bool StarSteamInventory::SetProperty(SteamInventoryUpdateHandle_t h, SteamItemInstanceID_t id, const char* n, const char* v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(id); STAR_UNREFERENCED(n); STAR_UNREFERENCED(v); return false; }
bool StarSteamInventory::SetProperty(SteamInventoryUpdateHandle_t h, SteamItemInstanceID_t id, const char* n, bool v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(id); STAR_UNREFERENCED(n); STAR_UNREFERENCED(v); return false; }
bool StarSteamInventory::SetProperty(SteamInventoryUpdateHandle_t h, SteamItemInstanceID_t id, const char* n, int64 v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(id); STAR_UNREFERENCED(n); STAR_UNREFERENCED(v); return false; }
bool StarSteamInventory::SetProperty(SteamInventoryUpdateHandle_t h, SteamItemInstanceID_t id, const char* n, float v) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(id); STAR_UNREFERENCED(n); STAR_UNREFERENCED(v); return false; }
bool StarSteamInventory::SubmitUpdateProperties(SteamInventoryUpdateHandle_t h, SteamInventoryResult_t* p) { STAR_UNREFERENCED(h); if(p) *p=k_SteamInventoryResultInvalid; return false; }
bool StarSteamInventory::InspectItem(SteamInventoryResult_t* p, const char* t) { STAR_UNREFERENCED(t); if(p) *p=k_SteamInventoryResultInvalid; return false; }
