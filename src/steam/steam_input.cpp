#include "steam/steam_input.h"

StarSteamInput& StarSteamInput::get() { static StarSteamInput i; return i; }

bool StarSteamInput::Init(bool bExplicitlyCallRunFrame) { STAR_UNREFERENCED(bExplicitlyCallRunFrame); return true; }
bool StarSteamInput::Shutdown() { return true; }
bool StarSteamInput::SetInputActionManifestFilePath(const char* p) { STAR_UNREFERENCED(p); return true; }
void StarSteamInput::RunFrame(bool b) { STAR_UNREFERENCED(b); }
bool StarSteamInput::BWaitForData(bool bWaitForever, uint32 unTimeout) { STAR_UNREFERENCED(bWaitForever); STAR_UNREFERENCED(unTimeout); return false; }
bool StarSteamInput::BNewDataAvailable() { return false; }
int StarSteamInput::GetConnectedControllers(InputHandle_t* handlesOut) { STAR_UNREFERENCED(handlesOut); return 0; }
void StarSteamInput::EnableDeviceCallbacks() {}
void StarSteamInput::EnableActionEventCallbacks(SteamInputActionEventCallbackPointer p) { STAR_UNREFERENCED(p); }
InputActionSetHandle_t StarSteamInput::GetActionSetHandle(const char* n) { STAR_UNREFERENCED(n); return 0; }
void StarSteamInput::ActivateActionSet(InputHandle_t h, InputActionSetHandle_t a) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(a); }
InputActionSetHandle_t StarSteamInput::GetCurrentActionSet(InputHandle_t h) { STAR_UNREFERENCED(h); return 0; }
void StarSteamInput::ActivateActionSetLayer(InputHandle_t h, InputActionSetHandle_t a) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(a); }
void StarSteamInput::DeactivateActionSetLayer(InputHandle_t h, InputActionSetHandle_t a) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(a); }
void StarSteamInput::DeactivateAllActionSetLayers(InputHandle_t h) { STAR_UNREFERENCED(h); }
int StarSteamInput::GetActiveActionSetLayers(InputHandle_t h, InputActionSetHandle_t* out) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(out); return 0; }
InputDigitalActionHandle_t StarSteamInput::GetDigitalActionHandle(const char* n) { STAR_UNREFERENCED(n); return 0; }
InputDigitalActionData_t StarSteamInput::GetDigitalActionData(InputHandle_t h, InputDigitalActionHandle_t d) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(d); InputDigitalActionData_t r{}; return r; }
int StarSteamInput::GetDigitalActionOrigins(InputHandle_t h, InputActionSetHandle_t a, InputDigitalActionHandle_t d, EInputActionOrigin* o) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(a); STAR_UNREFERENCED(d); STAR_UNREFERENCED(o); return 0; }
const char* StarSteamInput::GetStringForDigitalActionName(InputDigitalActionHandle_t h) { STAR_UNREFERENCED(h); return ""; }
InputAnalogActionHandle_t StarSteamInput::GetAnalogActionHandle(const char* n) { STAR_UNREFERENCED(n); return 0; }
InputAnalogActionData_t StarSteamInput::GetAnalogActionData(InputHandle_t h, InputAnalogActionHandle_t a) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(a); InputAnalogActionData_t r{}; return r; }
int StarSteamInput::GetAnalogActionOrigins(InputHandle_t h, InputActionSetHandle_t a, InputAnalogActionHandle_t an, EInputActionOrigin* o) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(a); STAR_UNREFERENCED(an); STAR_UNREFERENCED(o); return 0; }
const char* StarSteamInput::GetGlyphPNGForActionOrigin(EInputActionOrigin e, ESteamInputGlyphSize s, uint32 f) { STAR_UNREFERENCED(e); STAR_UNREFERENCED(s); STAR_UNREFERENCED(f); return ""; }
const char* StarSteamInput::GetGlyphSVGForActionOrigin(EInputActionOrigin e, uint32 f) { STAR_UNREFERENCED(e); STAR_UNREFERENCED(f); return ""; }
const char* StarSteamInput::GetGlyphForActionOrigin_Legacy(EInputActionOrigin e) { STAR_UNREFERENCED(e); return ""; }
const char* StarSteamInput::GetStringForActionOrigin(EInputActionOrigin e) { STAR_UNREFERENCED(e); return ""; }
const char* StarSteamInput::GetStringForAnalogActionName(InputAnalogActionHandle_t h) { STAR_UNREFERENCED(h); return ""; }
void StarSteamInput::StopAnalogActionMomentum(InputHandle_t h, InputAnalogActionHandle_t a) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(a); }
InputMotionData_t StarSteamInput::GetMotionData(InputHandle_t h) { STAR_UNREFERENCED(h); InputMotionData_t r{}; return r; }
void StarSteamInput::TriggerVibration(InputHandle_t h, unsigned short l, unsigned short r) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(l); STAR_UNREFERENCED(r); }
void StarSteamInput::TriggerVibrationExtended(InputHandle_t h, unsigned short l, unsigned short r, unsigned short lt, unsigned short rt) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(l); STAR_UNREFERENCED(r); STAR_UNREFERENCED(lt); STAR_UNREFERENCED(rt); }
void StarSteamInput::TriggerSimpleHapticEvent(InputHandle_t h, EControllerHapticLocation loc, uint8 i, char g, uint8 oi, char og) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(loc); STAR_UNREFERENCED(i); STAR_UNREFERENCED(g); STAR_UNREFERENCED(oi); STAR_UNREFERENCED(og); }
void StarSteamInput::SetLEDColor(InputHandle_t h, uint8 r, uint8 g, uint8 b, unsigned int f) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(r); STAR_UNREFERENCED(g); STAR_UNREFERENCED(b); STAR_UNREFERENCED(f); }
void StarSteamInput::Legacy_TriggerHapticPulse(InputHandle_t h, ESteamControllerPad p, unsigned short d) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(d); }
void StarSteamInput::Legacy_TriggerRepeatedHapticPulse(InputHandle_t h, ESteamControllerPad p, unsigned short d, unsigned short o, unsigned short r, unsigned int f) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); STAR_UNREFERENCED(d); STAR_UNREFERENCED(o); STAR_UNREFERENCED(r); STAR_UNREFERENCED(f); }
bool StarSteamInput::ShowBindingPanel(InputHandle_t h) { STAR_UNREFERENCED(h); return false; }
ESteamInputType StarSteamInput::GetInputTypeForHandle(InputHandle_t h) { STAR_UNREFERENCED(h); return k_ESteamInputType_Unknown; }
InputHandle_t StarSteamInput::GetControllerForGamepadIndex(int n) { STAR_UNREFERENCED(n); return 0; }
int StarSteamInput::GetGamepadIndexForController(InputHandle_t h) { STAR_UNREFERENCED(h); return -1; }
const char* StarSteamInput::GetStringForXboxOrigin(EXboxOrigin e) { STAR_UNREFERENCED(e); return ""; }
const char* StarSteamInput::GetGlyphForXboxOrigin(EXboxOrigin e) { STAR_UNREFERENCED(e); return ""; }
EInputActionOrigin StarSteamInput::GetActionOriginFromXboxOrigin(InputHandle_t h, EXboxOrigin e) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(e); return k_EInputActionOrigin_None; }
EInputActionOrigin StarSteamInput::TranslateActionOrigin(ESteamInputType t, EInputActionOrigin e) { STAR_UNREFERENCED(t); STAR_UNREFERENCED(e); return k_EInputActionOrigin_None; }
bool StarSteamInput::GetDeviceBindingRevision(InputHandle_t h, int* maj, int* min) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(maj); STAR_UNREFERENCED(min); return false; }
uint32 StarSteamInput::GetRemotePlaySessionID(InputHandle_t h) { STAR_UNREFERENCED(h); return 0; }
uint16 StarSteamInput::GetSessionInputConfigurationSettings() { return 0; }
void StarSteamInput::SetDualSenseTriggerEffect(InputHandle_t h, const ScePadTriggerEffectParam* p) { STAR_UNREFERENCED(h); STAR_UNREFERENCED(p); }
