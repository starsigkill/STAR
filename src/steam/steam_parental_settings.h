#pragma once
#include "core/star_common.h"
#include "steam/isteamparentalsettings.h"

class StarSteamParentalSettings : public ISteamParentalSettings
{
public:
    static StarSteamParentalSettings& get() { static StarSteamParentalSettings s; return s; }

    bool BIsParentalLockEnabled() override { return false; }
    bool BIsParentalLockLocked() override { return false; }
    bool BIsAppBlocked(AppId_t) override { return false; }
    bool BIsAppInBlockList(AppId_t) override { return false; }
    bool BIsFeatureBlocked(EParentalFeature) override { return false; }
    bool BIsFeatureInBlockList(EParentalFeature) override { return false; }
};
