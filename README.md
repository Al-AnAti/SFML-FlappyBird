# Flappy Bird (SFML)

A Flappy Bird clone written in C++20 using [SFML 2.6](https://www.sfml-dev.org/).

## Controls

| Key     | Action                  |
|---------|-------------------------|
| `Space` | Flap                    |
| `R`     | Restart after game over |
| `Esc`   | Quit                    |

The pipes speed up every 5 points. Your best score is saved to `score.txt` next to the game.

## Project layout

```
SFML-FlappyBird/
├── assets/
│   ├── fonts/        # Fonts used for the score and game-over text
│   └── textures/     # Sprites
├── src/              # Game source code
│   ├── main.cpp
│   ├── Game.*        # Window, main loop, collisions
│   ├── Bird.*        # Player movement
│   ├── Pipe.*        # Pipe spawning and scrolling
│   └── Score.*       # Score and high score
└── CMakeLists.txt
```

## Building

You need CMake 3.28 or newer and a C++20 compiler. SFML is downloaded and built automatically the first time you configure, so you don't need to install it.

```bash
cmake -B build
cmake --build build --config Release
```

The game ends up in `build/bin/` (or `build/bin/Release/` with Visual Studio), with the `assets` folder copied next to it. Run it from that folder.

### Visual Studio

Open the project folder with **File → Open → Folder**. Visual Studio detects `CMakeLists.txt`; pick `FlappyBird.exe` as the startup item and press F5. This needs the **C++ CMake tools for Windows** component, which you can add from the Visual Studio Installer.

### Using an installed SFML

To use an SFML 2.6 that's already on your system instead of downloading it:

```bash
cmake -B build -DFLAPPYBIRD_FETCH_SFML=OFF
```

On Linux, building SFML from source needs its system dependencies first. See the [SFML build guide](https://www.sfml-dev.org/tutorials/2.6/compile-with-cmake.php).

### Making a release folder

```bash
cmake --install build --config Release --prefix dist
```

This puts the executable and `assets/` in `dist/`, ready to zip and share.
