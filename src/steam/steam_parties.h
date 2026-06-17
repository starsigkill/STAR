#pragma once
#include "core/star_common.h"
#include "steam/isteammatchmaking.h"

class StarSteamParties : public ISteamParties
{
public:
    static StarSteamParties& get() { static StarSteamParties s; return s; }

    uint32 GetNumActiveBeacons() override { return 0; }
    PartyBeaconID_t GetBeaconByIndex(uint32) override { return 0; }
    bool GetBeaconDetails(PartyBeaconID_t, CSteamID*, SteamPartyBeaconLocation_t*, char* pch, int cch) override { if (pch && cch > 0) pch[0] = 0; return false; }
    SteamAPICall_t JoinParty(PartyBeaconID_t) override { return k_uAPICallInvalid; }
    bool GetNumAvailableBeaconLocations(uint32* puNumLocations) override { if (puNumLocations) *puNumLocations = 0; return false; }
    bool GetAvailableBeaconLocations(SteamPartyBeaconLocation_t*, uint32) override { return false; }
    SteamAPICall_t CreateBeacon(uint32, SteamPartyBeaconLocation_t*, const char*, const char*) override { return k_uAPICallInvalid; }
    void OnReservationCompleted(PartyBeaconID_t, CSteamID) override {}
    void CancelReservation(PartyBeaconID_t, CSteamID) override {}
    SteamAPICall_t ChangeNumOpenSlots(PartyBeaconID_t, uint32) override { return k_uAPICallInvalid; }
    bool DestroyBeacon(PartyBeaconID_t) override { return false; }
    bool GetBeaconLocationData(SteamPartyBeaconLocation_t, ESteamPartyBeaconLocationData, char* pch, int cch) override { if (pch && cch > 0) pch[0] = 0; return false; }
};
