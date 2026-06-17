# setup guide

Everything you need to get STAR running with a game.

---

## file layout

```
game.exe
steam_api64.dll       <- rename to match whatever the game expects
STAR/
  steam_appid.txt     <- the app ID, nothing else
  identity.star       <- your fake Steam identity
  game.star           <- game-specific config
  languages.star      <- (optional) supported languages
  overlay.star        <- (optional) overlay toggle
  achievements.json   <- (optional) achievement definitions
  icons/              <- (optional) achievement icon PNGs
```

x64 game? Use `steam_api64.dll`. x86? Use `steam_api.dll`. Check the existing DLL name in the game folder if unsure.

---

## steam_appid.txt

Just the number. No spaces, no quotes.

```
480
```

That's it. STAR also checks the game directory for `steam_appid.txt` as a fallback if it can't find one in `STAR/`. App ID is in the store URL (`store.steampowered.com/app/<ID>/`) or on SteamDB.

---

## identity.star

```ini
display_name = YourName
xuid = 76561198000000000
locale = english
```

`xuid` is your Steam ID (64-bit). Has to be greater than `76561190000000000` or it gets ignored and STAR uses a default. Get yours from steamid.io.

`locale` controls what `GetCurrentGameLanguage()` returns to the game. Use Steam language names: `english`, `french`, `german`, `schinese`, `tchinese`, `japanese`, `koreana`, `spanish`, `latam`, `portuguese`, `brazilian`, `russian`, `thai`, `bulgarian`, `czech`, `danish`, `dutch`, `finnish`, `greek`, `hungarian`, `italian`, `norwegian`, `polish`, `romanian`, `swedish`, `turkish`, `ukrainian`, `vietnamese`.

---

## game.star

```ini
beta = false
branch = public
dlc.unlock_all = false

; individual DLC entries (app ID = display name)
dlc.1234560 = Some DLC Name
dlc.1234561 = Another DLC
```

`dlc.unlock_all = true` makes `BIsDlcInstalled()` return true for everything. Or list specific DLC app IDs. DLC IDs are on SteamDB under the game's DLC tab.

---

## languages.star

```ini
[languages]
english = 1
french = 1
german = 1
```

Controls what `GetAvailableGameLanguages()` returns. If the locale in `identity.star` isn't in this list, STAR falls back to the first entry and logs a warning. File is optional, if missing only the configured locale is reported.

---

## overlay.star

```ini
enabled = true
```

`false` disables the overlay completely. No hooks, no ImGui, nothing. Useful if the game crashes on inject or you just don't need it.

---

## achievements.json

```json
[
  {
    "name": "ACH_WIN_ONE_GAME",
    "displayName": "Winner",
    "description": "Win your first game.",
    "icon": "icons/win.png",
    "icongray": "icons/win_gray.png",
    "hidden": "0"
  }
]
```

| field | required | notes |
|-------|----------|-------|
| `name` | yes | must match what the game passes to `SetAchievement()` |
| `displayName` | no | shown in overlay, falls back to `name` |
| `description` | no | shown under the name |
| `icon` | no | path relative to `STAR/`, shown when unlocked |
| `icongray` | no | path relative to `STAR/`, shown when locked |
| `hidden` | no | `"1"` hides name and desc until unlocked |

Icons load as PNGs. Missing icons show a placeholder box in the overlay.

---

## finding achievement names

The `name` field has to exactly match what the game passes to `SetAchievement()`. Wrong name = nothing ever unlocks. To find them:

- SteamDB, game's achievements tab, look at the API name column
- Search the game's files for strings like `ACH_` or common prefixes
- Run with STAR, check `STAR/star.log` for `SetAchievement` calls after triggering something in-game

---

## logs

`STAR/star.log` is created automatically next to the DLL.

Things to look for:

```
STAR loaded                              <- DLL attached
Settings dir: C:\...\STAR               <- found the config folder
App ID: 480                             <- picked up the app ID
Settings loaded: app_id=480 name='...'  <- config parsed OK
DX11 hooked / DX9 hooked / etc.        <- which graphics API got hooked
ImGui ready                             <- overlay is live
SetAchievement: ACH_WIN_ONE_GAME        <- game tried to unlock this
```

---

## common issues

**Game crashes immediately**
Wrong DLL bitness. x86 game needs `steam_api.dll`, x64 needs `steam_api64.dll`. Check the filename of the original DLL you replaced.

**Achievements don't unlock**
Check the log for `SetAchievement` calls. If they show up but nothing happens in the overlay, the `name` in `achievements.json` doesn't match. If they don't show up at all, the game might not be triggering them yet, or the app ID is 0 (check the log).

**Overlay doesn't appear**
Check for `DX11 hooked` / `DX9 hooked` / etc. in the log. If missing, MinHook didn't find the graphics API entry point. Make sure `overlay.star` has `enabled = true` and try the other DLL bitness.

**Stats don't persist between sessions**
Storage is keyed by app ID. If app ID is 0 in the log, fix your `steam_appid.txt`.

**Reset everything**
Delete `%APPDATA%\STAR\<AppID>\<SteamID>\`.
