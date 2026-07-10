# unity steam integration patching

For Unity games that ship with Steamworks.NET support but have Steam integration disabled in their build configuration (common in DRM-free releases from itch.io, GOG, or standalone launchers). 

In these builds, the game's internal SteamManager is configured with nable = false, causing it to exit early on startup. As a result, the game never calls SteamAPI.Init() and never loads steam_api64.dll, preventing achievements and the STAR overlay from working.

This document explains how to patch the game to force-enable Steam integration.

---

## how it works

Unity games using the standard Steamworks.NET package rely on a script named SteamManager. At startup, its Awake() method checks the nable field:

`csharp
protected virtual void Awake() {
    if (!enable) {
        return; // Exits early, disabling Steam completely
    }
    ...
`

Since the C# assembly is compiled into a DLL (such as Assembly-CSharp.dll or <GameName>Assembly.dll), we can bypass this early return by binary-patching the compiled Common Intermediate Language (CIL) bytecode.

### The CIL Byte Modification

The compiler translates if (!enable) return; to the following CIL sequence:

`il
ldarg.0             // 02
ldfld bool enable   // 7B [4-byte token]
brtrue.s skip_ret   // 2D 01
ret                 // 2A
`

By replacing this 9-byte pattern with instructions that always branch past the et statement, we bypass the early exit:

`il
ldc.i4.1            // 17
brtrue.s skip_ret   // 2D 01
ret                 // 2A
nop, nop, nop, ...  // 00 00 00 00 00 (padding to match length)
`

This forces SteamManager.Awake() to continue executing, initializing SteamAPI.Init() and loading STAR's steam_api64.dll.

---

## automated patching

A Python utility is provided in the repository to automate this entire process.

### Prerequisite

Create a steam_appid.txt containing your game's App ID in the game's root directory (next to the main game executable). This is required by Steamworks.NET to initialize the Steam API.

### Usage

Run the patch script and pass it either the game's root directory or the path directly to the target assembly DLL:

`ash
python tools/patch_unity_steam.py "D:\Games\My Unity Game"
`

The script will:
1. Walk the directory to locate the target assembly DLL (e.g., Assembly-CSharp.dll or <GameName>Assembly.dll).
2. Safely compile a temporary C# helper using the system's built-in csc.exe to resolve dependency references and locate the exact metadata token for the nable field (as token numbers vary per game compilation).
3. Search and replace the byte pattern in the target DLL.
4. Save a backup of the original assembly (appending .bak to the filename).

---

## manual patching (alternative)

If you prefer to patch manually:
1. Open the game's Managed folder (usually located at <GameName>_Data\Managed\).
2. Open Assembly-CSharp.dll or <GameName>Assembly.dll using a .NET decompiler like **dnSpy** or **ILSpy**.
3. Search for the SteamManager class and open the Awake method.
4. Right-click inside Awake and select **Edit Method Body...** (in dnSpy).
5. Locate the instruction checking nable at the beginning of the method.
6. Change the instruction loading the nable field to push a constant 1 (true) onto the stack, or remove the branch condition entirely so it never hits the et opcode.
7. Save the modified module.
