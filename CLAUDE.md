# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

SpaghettiKart is a cross-platform port of Mario Kart 64 built on the libultraship framework. The project enables the classic N64 game to run on modern platforms (Windows, Linux, macOS, Nintendo Switch) with enhancements and modding support.

## Build System

The project uses CMake with platform-specific configurations.

### Build Commands

**Windows (PowerShell):**
```powershell
# Setup cmake project
cmake -S . -B "build/x64" -G "Visual Studio 17 2022" -T v143 -A x64

# Generate spaghetti.o2r (port-specific assets)
cmake --build .\build\x64 --target GenerateO2R

# Extract assets from ROM (requires baserom.us.z64)
cmake --build .\build\x64 --target ExtractAssets

# Compile project
cmake --build .\build\x64

# For Release builds add: --config Release
# For packaging add: -DCMAKE_BUILD_TYPE:STRING=Release during setup
```

**Linux/macOS:**
```bash
# Clone submodules (required on first build)
git submodule update --init

# Generate Ninja project
cmake -H. -Bbuild-cmake -GNinja

# Generate spaghetti.o2r
cmake --build build-cmake --target GenerateO2R

# Extract assets from ROM
cmake --build build-cmake --target ExtractAssets

# Compile project
cmake --build build-cmake

# For Release builds: cmake -H. -Bbuild-cmake -GNinja -DCMAKE_BUILD_TYPE=Release
```

### CMake Targets

- `ExtractAssets` - Extracts mk64.o2r and spaghetti.o2r from baserom.us.z64
- `GenerateO2R` - Generates only spaghetti.o2r from assets directory
- `clean` - Clean build artifacts

### Packaging

```bash
cd build-cmake  # or build/x64 on Windows
cpack -G ZIP    # Cross-platform
cpack -G DEB    # Linux Debian package
cpack -G External  # Linux AppImage
```

## Architecture

### High-Level Structure

SpaghettiKart consists of three main layers:

1. **Original Game Code (src/)** - Decompiled Mario Kart 64 C code
   - `src/racing/` - Core racing mechanics, physics, player control
   - `src/audio/` - Audio playback and sound system
   - `src/data/` - Game data structures
   - `src/ending/` - Ending sequences and podium
   - `src/buffers/` - Memory buffers and rendering
   - `src/networking/` - Multiplayer networking (SDL2_net)

2. **Port Layer (src/port/)** - Platform abstraction and libultraship integration
   - `Engine.cpp/h` - GameEngine singleton, integrates with libultraship
   - `Game.cpp/h` - Game-specific initialization and main loop
   - `SpaghettiGui.cpp` - ImGui-based UI enhancements
   - `interpolation/` - Frame interpolation for smooth rendering
   - `resource/` - Resource loading and management

3. **Enhancement Engine (src/engine/)** - C++ enhancement system
   - `World.h/cpp` - Main world container managing courses, actors, objects
   - `courses/` - Course-specific implementations (each track is a class)
   - `objects/` - Dynamic game objects (Lakitu, Thwomp, Penguin, etc.)
   - `actors/` - Static and animated level actors
   - `vehicles/` - Traffic vehicles (Train, Car, Bus, Truck, Boat)
   - `particles/` - Particle emitter system
   - `editor/` - In-game level editor system
   - `items/` - Item system implementation

### Key Design Patterns

**Course System:**
Each course inherits from `Course` base class and implements:
- `BeginPlay()` - Initialize course-specific objects
- `Tick()` - Per-frame update logic
- `Waypoints()` - AI waypoint logic
- `Properties()` - Course metadata (collision, water, checkpoints)

Example: `src/engine/courses/MarioRaceway.cpp`

**Actor/Object Split:**
- **AActor** (C++) - New enhancement system for static/dynamic actors
- **Actor** (C) - Original game actor system
- **OObject** (C++) - Course objects with tick/draw methods
- **Object** (C) - Original game object system

Conversion functions exist in `World` class to bridge between systems.

**World Singleton:**
`gWorldInstance` is the global World object managing all courses, actors, objects, and particles. Access via `World::GetWorld()` or directly.

### Asset System

**Asset Format:** .o2r (O2 Resource, not .otr)
- `mk64.o2r` - Game assets extracted from ROM
- `spaghetti.o2r` - Port-specific enhancements and additional content

**Torch Tool:**
Located in `torch/` submodule. Used for asset extraction and packing:
```bash
torch header -o baserom.us.z64  # Extract header
torch o2r baserom.us.z64        # Generate mk64.o2r
torch pack assets spaghetti.o2r o2r  # Pack custom assets
```

**Asset Loading:**
- `LOAD_ASSET(path)` macro for runtime asset loading
- Assets loaded through libultraship's resource system
- `ResourceGetDataByName()` for raw asset access

### Libultraship Integration

Libultraship is a submodule providing:
- Cross-platform window/rendering (OpenGL, DirectX11, Metal)
- Input abstraction (SDL2)
- Resource/archive management
- ImGui integration
- Audio system (samples: 432-448, 2 channels)
- Fast3D graphics interpreter

Key classes:
- `GameEngine::Instance` - Singleton managing libultraship context
- `Ship::Context` - Main libultraship context
- `Fast::Interpreter` - Graphics command processor

## Code Standards

**Language Standards:**
- C++20 for C++ code
- C11 for C code

**Style:**
- The original game code (src/) mostly uses C with some C++ enhancements
- New enhancement code (src/engine/) is C++
- Port layer (src/port/) is C++

**Platform Definitions:**
- `VERSION_US=1` - US version of the game
- `NON_MATCHING=1` - Allow non-matching code
- `ENABLE_RUMBLE=1` - Rumble support
- `F3DEX_GBI=1` - Fast3D microcode

## Modding System

The game supports several modding types:

1. **Texture Packs** - Replace game textures (most textures supported)
2. **Custom Tracks** - Add new courses (advanced, uses fast64 Blender plugin)
3. **Custom Audio** - Replace music sequences (not samples/SFX yet)
4. **Custom Characters** - Replace existing characters (no new characters yet)

**Mod Location:** Place .o2r or .zip mods in `mods/` directory

**Future Plans:** WebAssembly scripting with component model for Rust/C/C++/Python/JS mods

## Testing and Debugging

**No formal test suite exists.** Testing is manual through playtesting.

**Debug Builds:**
```bash
cmake -H. -Bbuild-cmake -GNinja -DCMAKE_BUILD_TYPE=Debug
cmake --build build-cmake
```

**Useful Debug Features:**
- Collision viewer: `src/enhancements/collision_viewer.c`
- Moon jump enhancement: `src/enhancements/moon_jump.c`
- Freecam: `src/enhancements/freecam/`
- Editor system: `src/engine/editor/` (in-game level editing)

**Address Sanitizer** (commented out in CMakeLists.txt line 76-77):
```cmake
# Uncomment to enable:
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
```

## Important Files

- `CMakeLists.txt` - Main build configuration
- `vcpkg.json` - Windows dependencies (vcpkg auto-bootstraps)
- `config.yml` - Runtime configuration
- `yamls/` - Asset definition files
- `src/main.c` - Game entry point
- `src/port/Engine.cpp` - Engine initialization
- `src/port/Game.cpp` - Game loop and course management
- `src/engine/World.cpp` - World management and object lifecycle

## Platform-Specific Notes

**Windows:**
- Uses vcpkg for dependencies (auto-installed via cmake)
- DirectX 11 is default renderer
- Visual Studio 2022 with v143 toolset required

**Linux:**
- OpenGL renderer
- Requires: gcc/clang, SDL2, libpng, libzip, nlohmann-json, tinyxml2, spdlog, boost, libogg, libvorbis
- AppImage packaging supported

**macOS:**
- Metal renderer (default)
- Requires Xcode or xcode-tools
- Homebrew for dependencies
- Universal binary support (arm64 + x86_64)

**Nintendo Switch:**
- DevkitPro toolchain required
- Special libultraship branch: `nx/main-nx`
- Generates .nro executable

## Common Issues

1. **Submodule not initialized:** Run `git submodule update --init`
2. **Missing baserom.us.z64:** Required for ExtractAssets target. Hash: `579C48E211AE952530FFC8738709F078D5DD215E`
3. **Out of memory during build:** Add `-j4` to cmake build command
4. **Graphics backend crash:** Change backend in Settings menu or edit `spaghettify.cfg.json`

## Development Workflow

1. Clone with submodules: `git clone --recursive`
2. Obtain US ROM (baserom.us.z64) and verify SHA-1
3. Run ExtractAssets to generate .o2r files
4. Build project
5. Make code changes
6. Rebuild (incremental)
7. Test in-game

For new courses: Extend `Course` class, add to `World::Courses` in `World.cpp`, implement BeginPlay/Tick/Waypoints.

For new objects: Extend `OObject`, add to course's BeginPlay, implement Tick/Draw methods.
