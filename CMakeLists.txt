cmake_minimum_required(VERSION 3.16)
project(STAR VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# ---- FetchContent for third-party libraries ----
include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.90.4
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
    minhook
    GIT_REPOSITORY https://github.com/TsudaKageyu/minhook.git
    GIT_TAG        master
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(minhook)

FetchContent_Declare(
    vulkan_headers
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
    GIT_TAG        v1.3.268
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(vulkan_headers)

# ---- ImGui library ----
set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    list(APPEND IMGUI_SOURCES ${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.cpp)
endif()
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${vulkan_headers_SOURCE_DIR}/include
)
target_compile_definitions(imgui PUBLIC UNICODE IMGUI_IMPL_VULKAN_NO_PROTOTYPES)

# ---- MinHook library ----
add_library(minhook_lib STATIC
    ${minhook_SOURCE_DIR}/src/buffer.c
    ${minhook_SOURCE_DIR}/src/hook.c
    ${minhook_SOURCE_DIR}/src/trampoline.c
    ${minhook_SOURCE_DIR}/src/hde/hde32.c
    ${minhook_SOURCE_DIR}/src/hde/hde64.c
)
target_include_directories(minhook_lib PUBLIC ${minhook_SOURCE_DIR}/include)

# ---- STAR source files ----
set(STAR_SOURCES
    src/core/art_stamp.cpp
    src/core/callbacks.cpp
    src/core/config.cpp
    src/core/settings.cpp
    src/core/star_api.cpp
    src/core/storage.cpp
    src/overlay/overlay.cpp
    src/steam/steam_applist.cpp
    src/steam/steam_apps.cpp
    src/steam/steam_client.cpp
    src/steam/steam_controller.cpp
    src/steam/steam_friends.cpp
    src/steam/steam_game_server.cpp
    src/steam/steam_game_server_stats.cpp
    src/steam/steam_html_surface.cpp
    src/steam/steam_http.cpp
    src/steam/steam_input.cpp
    src/steam/steam_inventory.cpp
    src/steam/steam_matchmaking.cpp
    src/steam/steam_matchmaking_servers.cpp
    src/steam/steam_music.cpp
    src/steam/steam_music_remote.cpp
    src/steam/steam_networking.cpp
    src/steam/steam_remote_storage.cpp
    src/steam/steam_screenshots.cpp
    src/steam/steam_ugc.cpp
    src/steam/steam_unified_messages.cpp
    src/steam/steam_user.cpp
    src/steam/steam_user_stats.cpp
    src/steam/steam_utils.cpp
    src/steam/steam_video.cpp
)

add_library(star SHARED ${STAR_SOURCES})

target_compile_definitions(star PRIVATE
    STAR_API_EXPORTS
    STEAM_API_EXPORTS
    STEAM_API_FUNCTIONS_IMPL  # makes S_API = extern "C" __declspec(dllexport),
                              # matching the extern "C" definitions in star_api.cpp
                              # (without it S_API is empty -> C++ linkage -> C2732)
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    _CRT_SECURE_NO_WARNINGS
    IMGUI_IMPL_VULKAN_NO_PROTOTYPES
)

target_include_directories(star PRIVATE
    ${CMAKE_SOURCE_DIR}/sdk
    ${CMAKE_SOURCE_DIR}/src
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${vulkan_headers_SOURCE_DIR}/include
    ${minhook_SOURCE_DIR}/include
)

target_link_libraries(star PRIVATE
    imgui
    minhook_lib
    nlohmann_json::nlohmann_json
    d3d11
    d3d12
    dxgi
    d3dcompiler
    d3d9
    opengl32
    bcrypt
    ws2_32
    winmm
)

# Set output name and linker flags based on architecture
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set_target_properties(star PROPERTIES OUTPUT_NAME "steam_api64")
else()
    set_target_properties(star PROPERTIES OUTPUT_NAME "steam_api")
endif()

# DEF file for clean exports (no LIBRARY line → no LNK4070 mismatch on x64)
# /NODEFAULTLIB:LIBCMT silences LNK4098 from the static-CRT deps (minhook/imgui)
set_target_properties(star PROPERTIES
    LINK_FLAGS "/SUBSYSTEM:WINDOWS /DEF:${CMAKE_SOURCE_DIR}/steam_api.def"
)

if(MSVC)
    target_compile_options(star PRIVATE /W3 /MP)
    target_link_options(star PRIVATE $<$<CONFIG:Debug>:/MAP>)
    # Debug info in release for debugging if needed
    target_compile_options(star PRIVATE $<$<CONFIG:Release>:/Zi>)
endif()

# ---- star_setup TUI (PyInstaller exe) ----------------------------------------
option(BUILD_SETUP_TOOL "Build the star_setup TUI executable (requires Python & PyInstaller)" OFF)

if(BUILD_SETUP_TOOL)
    find_program(PYTHON_EXECUTABLE NAMES python python3 REQUIRED)

    add_custom_target(star_setup_exe ALL
        COMMAND ${PYTHON_EXECUTABLE} -m PyInstaller
                --onefile
                --console
                --name star_setup
                --collect-all textual
                --collect-all rich
                --hidden-import PIL
                --hidden-import PIL.Image
                --distpath "${CMAKE_BINARY_DIR}/$<CONFIG>"
                --workpath "${CMAKE_BINARY_DIR}/pyinstaller_work"
                --noconfirm
                "${CMAKE_SOURCE_DIR}/tools/star_setup.py"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/tools"
        COMMENT "Building star_setup.exe with PyInstaller"
        VERBATIM
    )
endif()

