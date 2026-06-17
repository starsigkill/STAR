# STAR

```
  .-')    .-') _      ('-.     _  .-')
 ( OO ). (  OO) )    ( OO ).-.( \( -O )
(_)---\_)/     '._   / . --. / ,------.
/    _ | |'--...__)  | \-.  \  |   /`. '
\  :` `. '--.  .--'.-'-'  |  | |  /  | |
 '..`''.)   |  |    \| |_.'  | |  |_.' |
.-._)   \   |  |     |  .-.  | |  .  '.'
\       /   |  |     |  | |  | |  |\  \
 `-----'    `--'     `--' `--' `--' '--'
```

Steam API emulator. Drops in as `steam_api.dll` / `steam_api64.dll` and pretends to be Steam. Your game never knows the difference.

---

## what it does

- Implements the full Steamworks SDK: user, friends, stats, achievements, apps, networking, UGC, inventory, remote storage, the whole thing
- In-game overlay (Shift+Tab) built on ImGui, hooks whatever graphics API your game uses
- Animated achievement notifications slide in from the bottom-right when you unlock stuff
- Saves stats and achievements locally so they persist across sessions
- Reads all config from a `STAR/` folder next to the DLL

---

## setup

Drop the DLL next to the game executable. Create a `STAR/` folder there with your config files.

**Minimum viable setup:**

```
game.exe
steam_api64.dll   ← this thing
STAR/
  identity.star
  game.star
```

**`STAR/identity.star`**
```ini
display_name = YourName
xuid = 76561198000000000
locale = english
```

**`STAR/game.star`**
```ini
beta = false
branch = public
dlc.unlock_all = false
```

**`STAR/overlay.star`** (optional, overlay is on by default)
```ini
enabled = true
```

App ID is read from `STAR/steam_appid.txt` (or `steam_appid.txt` in the game directory as a fallback).

---

## achievements

Put an `achievements.json` in your `STAR/` folder:

```json
[
  {
    "name": "ACH_WIN_ONE_GAME",
    "displayName": "Winner",
    "description": "Win your first game.",
    "icon": "icons/ach_win.png",
    "hidden": "0"
  }
]
```

Icon paths are relative to the `STAR/` directory. You can unlock and reset achievements live from the overlay.

---

## overlay

`Shift+Tab` to toggle. Slides in from the right.

Shows your account info, achievement progress, and a scrollable list of every achievement with Unlock/Reset buttons per row. Hit "Test notify" to fire a fake achievement notification so you can see how it looks without actually unlocking anything.

Supports DX9, DX11, DX12, OpenGL, and Vulkan. Hooks the present call via MinHook, no game cooperation needed.

---

## building

Requires MSVC and CMake 3.16+. All dependencies pull in automatically via FetchContent.

**x64 (steam_api64.dll):**
```
cmake -B build64 -A x64
cmake --build build64 --config Release
```

**x86 (steam_api.dll):**
```
cmake -B build -A Win32
cmake --build build --config Release
```

Output lands in `build64/Release/steam_api64.dll` or `build/Release/steam_api.dll`.

---

## logs

`STAR/star.log` next to the DLL. Falls back to `%TEMP%/star.log` if that directory isn't writable. The log tells you what app ID loaded, how many achievements came in, and whether the overlay hooks fired correctly.

---

## config files

All `.star` files are INI-format. On first load, STAR stamps a small ASCII art header into each one. That's intentional, don't delete it unless you want it back.

| file | what it controls |
|------|-----------------|
| `identity.star` | display name, Steam ID, language |
| `game.star` | app ID, DLC config, beta branch |
| `languages.star` | list of languages the game claims to support |
| `overlay.star` | enable/disable the overlay |
| `achievements.json` | achievement definitions |

---

## misc

- `SteamAPI_IsSteamRunning()` always returns `true`. You're welcome.
- Networking interfaces exist but don't actually network anything.
- Inventory and UGC are stubs, they won't crash but won't do much.
- Game server stuff returns success and does nothing. Fine for most games.
