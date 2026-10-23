cmake_minimum_required(VERSION 3.28)

project(FlappyBird
    VERSION 1.0.0
    DESCRIPTION "A Flappy Bird clone written in C++ with SFML"
    LANGUAGES CXX)

# ---------------------------------------------------------------------------
# Options
# ---------------------------------------------------------------------------
option(FLAPPYBIRD_FETCH_SFML "Download and build SFML instead of using an installed copy" ON)

# Put the executable in build/bin (or build/bin/<Config> for Visual Studio)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# ---------------------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------------------
if(FLAPPYBIRD_FETCH_SFML)
    include(FetchContent)

    # Static SFML means no DLLs to ship next to the game
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)
else()
    find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)
endif()

# ---------------------------------------------------------------------------
# Game executable
# ---------------------------------------------------------------------------
add_executable(FlappyBird
    src/main.cpp
    src/Game.cpp
    src/Game.h
    src/Bird.cpp
    src/Bird.h
    src/Pipe.cpp
    src/Pipe.h
    src/Score.cpp
    src/Score.h)

target_include_directories(FlappyBird PRIVATE src)
target_compile_features(FlappyBird PRIVATE cxx_std_20)
target_link_libraries(FlappyBird PRIVATE sfml-graphics)

if(MSVC)
    target_compile_options(FlappyBird PRIVATE /W3 /permissive-)
else()
    target_compile_options(FlappyBird PRIVATE -Wall -Wextra)
endif()

# Make FlappyBird the startup project when opening the generated .sln
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT FlappyBird)

# The game loads its files relative to the working directory, so run it
# from the folder that holds the executable and its assets.
set_target_properties(FlappyBird PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:FlappyBird>")

# ---------------------------------------------------------------------------
# Assets: copied next to the executable on every build
# ---------------------------------------------------------------------------
add_custom_target(FlappyBird_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:FlappyBird>/assets"
    COMMENT "Copying assets next to the executable")
add_dependencies(FlappyBird FlappyBird_assets)

# ---------------------------------------------------------------------------
# Install: `cmake --install build --prefix dist` gives a ready-to-zip folder
# ---------------------------------------------------------------------------
install(TARGETS FlappyBird RUNTIME DESTINATION .)
install(DIRECTORY assets DESTINATION .)
