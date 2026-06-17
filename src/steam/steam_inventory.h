#pragma once
#include "core/star_common.h"
#include "steam/isteaminventory.h"

class StarSteamInventory : public ISteamInventory {
public:
    static StarSteamInventory& get();
    EResult GetResultStatus(SteamInventoryResult_t resultHandle) override;
    bool GetResultItems(SteamInventoryResult_t resultHandle, SteamItemDetails_t* pOutItemsArray, uint32* punOutItemsArraySize) override;
    bool GetResultItemProperty(SteamInventoryResult_t resultHandle, uint32 unItemIndex, const char* pchPropertyName, char* pchValueBuffer, uint32* punValueBufferSizeOut) override;
    uint32 GetResultTimestamp(SteamInventoryResult_t resultHandle) override;
    bool CheckResultSteamID(SteamInventoryResult_t resultHandle, CSteamID steamIDExpected) override;
    void DestroyResult(SteamInventoryResult_t resultHandle) override;
    bool GetAllItems(SteamInventoryResult_t* pResultHandle) override;
    bool GetItemsByID(SteamInventoryResult_t* pResultHandle, const SteamItemInstanceID_t* pInstanceIDs, uint32 unCountInstanceIDs) override;
    bool SerializeResult(SteamInventoryResult_t resultHandle, void* pOutBuffer, uint32* punOutBufferSize) override;
    bool DeserializeResult(SteamInventoryResult_t* pOutResultHandle, const void* pBuffer, uint32 unBufferSize, bool bRESERVED_MUST_BE_FALSE) override;
    bool GenerateItems(SteamInventoryResult_t* pResultHandle, const SteamItemDef_t* pArrayItemDefs, const uint32* punArrayQuantity, uint32 unArrayLength) override;
    bool GrantPromoItems(SteamInventoryResult_t* pResultHandle) override;
    bool AddPromoItem(SteamInventoryResult_t* pResultHandle, SteamItemDef_t itemDef) override;
    bool AddPromoItems(SteamInventoryResult_t* pResultHandle, const SteamItemDef_t* pArrayItemDefs, uint32 unArrayLength) override;
    bool ConsumeItem(SteamInventoryResult_t* pResultHandle, SteamItemInstanceID_t itemConsume, uint32 unQuantity) override;
    bool ExchangeItems(SteamInventoryResult_t* pResultHandle, const SteamItemDef_t* pArrayGenerate, const uint32* punArrayGenerateQuantity, uint32 unArrayGenerateLength, const SteamItemInstanceID_t* pArrayDestroy, const uint32* punArrayDestroyQuantity, uint32 unArrayDestroyLength) override;
    bool TransferItemQuantity(SteamInventoryResult_t* pResultHandle, SteamItemInstanceID_t itemIdSource, uint32 unQuantity, SteamItemInstanceID_t itemIdDest) override;
    void SendItemDropHeartbeat() override;
    bool TriggerItemDrop(SteamInventoryResult_t* pResultHandle, SteamItemDef_t dropListDefinition) override;
    bool TradeItems(SteamInventoryResult_t* pResultHandle, CSteamID steamIDTradePartner, const SteamItemInstanceID_t* pArrayGive, const uint32* pArrayGiveQuantity, uint32 nArrayGiveLength, const SteamItemInstanceID_t* pArrayGet, const uint32* pArrayGetQuantity, uint32 nArrayGetLength) override;
    bool LoadItemDefinitions() override;
    bool GetItemDefinitionIDs(SteamItemDef_t* pItemDefIDs, uint32* punItemDefIDsArraySize) override;
    bool GetItemDefinitionProperty(SteamItemDef_t iDefinition, const char* pchPropertyName, char* pchValueBuffer, uint32* punValueBufferSizeOut) override;
    SteamAPICall_t RequestEligiblePromoItemDefinitionsIDs(CSteamID steamID) override;
    bool GetEligiblePromoItemDefinitionIDs(CSteamID steamID, SteamItemDef_t* pItemDefIDs, uint32* punItemDefIDsArraySize) override;
    SteamAPICall_t StartPurchase(const SteamItemDef_t* pArrayItemDefs, const uint32* punArrayQuantity, uint32 unArrayLength) override;
    SteamAPICall_t RequestPrices() override;
    uint32 GetNumItemsWithPrices() override;
    bool GetItemsWithPrices(SteamItemDef_t* pArrayItemDefs, uint64* pCurrentPrices, uint64* pBasePrices, uint32 unArrayLength) override;
    bool GetItemPrice(SteamItemDef_t iDefinition, uint64* pCurrentPrice, uint64* pBasePrice) override;
    SteamInventoryUpdateHandle_t StartUpdateProperties() override;
    bool RemoveProperty(SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName) override;
    bool SetProperty(SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, const char* pchPropertyValue) override;
    bool SetProperty(SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, bool bValue) override;
    bool SetProperty(SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, int64 nValue) override;
    bool SetProperty(SteamInventoryUpdateHandle_t handle, SteamItemInstanceID_t nItemID, const char* pchPropertyName, float flValue) override;
    bool SubmitUpdateProperties(SteamInventoryUpdateHandle_t handle, SteamInventoryResult_t* pResultHandle) override;
    bool InspectItem(SteamInventoryResult_t* pResultHandle, const char* pchItemToken) override;
private:
    StarSteamInventory() = default;
    static const SteamInventoryResult_t kValidResult = 1;
};
