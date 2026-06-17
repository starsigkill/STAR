#pragma once
#include "core/star_common.h"
#include "steam/isteamcontroller003.h"

class StarSteamController : public ISteamController003 {
public:
    static StarSteamController& get();
    bool Init() override;
    bool Shutdown() override;
    void RunFrame() override;
    int GetConnectedControllers(ControllerHandle_t* handlesOut) override;
    bool ShowBindingPanel(ControllerHandle_t controllerHandle) override;
    ControllerActionSetHandle_t GetActionSetHandle(const char* pszActionSetName) override;
    void ActivateActionSet(ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle) override;
    ControllerActionSetHandle_t GetCurrentActionSet(ControllerHandle_t controllerHandle) override;
    ControllerDigitalActionHandle_t GetDigitalActionHandle(const char* pszActionName) override;
    ControllerDigitalActionData_t GetDigitalActionData(ControllerHandle_t controllerHandle, ControllerDigitalActionHandle_t digitalActionHandle) override;
    int GetDigitalActionOrigins(ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerDigitalActionHandle_t digitalActionHandle, EControllerActionOrigin* originsOut) override;
    ControllerAnalogActionHandle_t GetAnalogActionHandle(const char* pszActionName) override;
    ControllerAnalogActionData_t GetAnalogActionData(ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t analogActionHandle) override;
    int GetAnalogActionOrigins(ControllerHandle_t controllerHandle, ControllerActionSetHandle_t actionSetHandle, ControllerAnalogActionHandle_t analogActionHandle, EControllerActionOrigin* originsOut) override;
    void StopAnalogActionMomentum(ControllerHandle_t controllerHandle, ControllerAnalogActionHandle_t eAction) override;
    void TriggerHapticPulse(ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec) override;
    void TriggerRepeatedHapticPulse(ControllerHandle_t controllerHandle, ESteamControllerPad eTargetPad, unsigned short usDurationMicroSec, unsigned short usOffMicroSec, unsigned short unRepeat, unsigned int nFlags) override;
private:
    StarSteamController() = default;
};
