#include "steam/steam_controller.h"
StarSteamController& StarSteamController::get() { static StarSteamController i; return i; }
bool StarSteamController::Init() { return true; }
bool StarSteamController::Shutdown() { return true; }
void StarSteamController::RunFrame() {}
int StarSteamController::GetConnectedControllers(ControllerHandle_t* h) { STAR_UNREFERENCED(h); return 0; }
bool StarSteamController::ShowBindingPanel(ControllerHandle_t h) { STAR_UNREFERENCED(h); return false; }
ControllerActionSetHandle_t StarSteamController::GetActionSetHandle(const char* n) { STAR_UNREFERENCED(n); return 0; }
void StarSteamController::ActivateActionSet(ControllerHandle_t c, ControllerActionSetHandle_t a) { STAR_UNREFERENCED(c); STAR_UNREFERENCED(a); }
ControllerActionSetHandle_t StarSteamController::GetCurrentActionSet(ControllerHandle_t c) { STAR_UNREFERENCED(c); return 0; }
ControllerDigitalActionHandle_t StarSteamController::GetDigitalActionHandle(const char* n) { STAR_UNREFERENCED(n); return 0; }
ControllerDigitalActionData_t StarSteamController::GetDigitalActionData(ControllerHandle_t c, ControllerDigitalActionHandle_t d) { STAR_UNREFERENCED(c); STAR_UNREFERENCED(d); ControllerDigitalActionData_t r{}; return r; }
int StarSteamController::GetDigitalActionOrigins(ControllerHandle_t c, ControllerActionSetHandle_t a, ControllerDigitalActionHandle_t d, EControllerActionOrigin* o) { STAR_UNREFERENCED(c); STAR_UNREFERENCED(a); STAR_UNREFERENCED(d); STAR_UNREFERENCED(o); return 0; }
ControllerAnalogActionHandle_t StarSteamController::GetAnalogActionHandle(const char* n) { STAR_UNREFERENCED(n); return 0; }
ControllerAnalogActionData_t StarSteamController::GetAnalogActionData(ControllerHandle_t c, ControllerAnalogActionHandle_t a) { STAR_UNREFERENCED(c); STAR_UNREFERENCED(a); ControllerAnalogActionData_t r{}; return r; }
int StarSteamController::GetAnalogActionOrigins(ControllerHandle_t c, ControllerActionSetHandle_t a, ControllerAnalogActionHandle_t an, EControllerActionOrigin* o) { STAR_UNREFERENCED(c); STAR_UNREFERENCED(a); STAR_UNREFERENCED(an); STAR_UNREFERENCED(o); return 0; }
void StarSteamController::StopAnalogActionMomentum(ControllerHandle_t c, ControllerAnalogActionHandle_t a) { STAR_UNREFERENCED(c); STAR_UNREFERENCED(a); }
void StarSteamController::TriggerHapticPulse(ControllerHandle_t c, ESteamControllerPad p, unsigned short d) { STAR_UNREFERENCED(c); STAR_UNREFERENCED(p); STAR_UNREFERENCED(d); }
void StarSteamController::TriggerRepeatedHapticPulse(ControllerHandle_t c, ESteamControllerPad p, unsigned short d, unsigned short o, unsigned short r, unsigned int f) { STAR_UNREFERENCED(c); STAR_UNREFERENCED(p); STAR_UNREFERENCED(d); STAR_UNREFERENCED(o); STAR_UNREFERENCED(r); STAR_UNREFERENCED(f); }
