@echo off
setlocal enabledelayedexpansion

echo ====================================================
echo Building STAR x86 and x64 Release targets...
echo ====================================================

set ROOT_DIR=%~dp0
set DIST_DIR=%ROOT_DIR%dist

echo [1/4] Configuring 32-bit (x86) build...
cmake -B "%ROOT_DIR%build" -A Win32 -DBUILD_SETUP_TOOL=OFF
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake configuration failed for 32-bit build.
    exit /b %ERRORLEVEL%
)

echo [2/4] Compiling 32-bit (x86) DLL...
cmake --build "%ROOT_DIR%build" --config Release
if %ERRORLEVEL% neq 0 (
    echo ERROR: Compilation failed for 32-bit build.
    exit /b %ERRORLEVEL%
)

echo [3/4] Configuring 64-bit (x64) build...
cmake -B "%ROOT_DIR%build64" -A x64 -DBUILD_SETUP_TOOL=OFF
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake configuration failed for 64-bit build.
    exit /b %ERRORLEVEL%
)

echo [4/4] Compiling 64-bit (x64) DLL...
cmake --build "%ROOT_DIR%build64" --config Release
if %ERRORLEVEL% neq 0 (
    echo ERROR: Compilation failed for 64-bit build.
    exit /b %ERRORLEVEL%
)

echo.
echo Packaging build DLLs to dist/...
if not exist "%DIST_DIR%" mkdir "%DIST_DIR%"

copy /Y "%ROOT_DIR%build\Release\steam_api.dll" "%DIST_DIR%\steam_api.dll"
if %ERRORLEVEL% neq 0 (
    echo ERROR: Failed to copy 32-bit steam_api.dll to dist.
    exit /b %ERRORLEVEL%
)

copy /Y "%ROOT_DIR%build64\Release\steam_api64.dll" "%DIST_DIR%\steam_api64.dll"
if %ERRORLEVEL% neq 0 (
    echo ERROR: Failed to copy 64-bit steam_api64.dll to dist.
    exit /b %ERRORLEVEL%
)

echo ====================================================
echo Build completed successfully!
echo Output DLLs are available in:
echo   - %DIST_DIR%\steam_api.dll   (32-bit)
echo   - %DIST_DIR%\steam_api64.dll (64-bit)
echo ====================================================
