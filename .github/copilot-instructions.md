## Quick goal
Help contributors and automated coding agents become productive fast in this repository by documenting the project's architecture, build/test workflows, and code conventions.

## Big-picture architecture (what to know first)
- Three logical components:
  - `chess_shared` (library) — core game logic and data structures. Examples: `src/Shared/Game/BoardState.h`, `src/Shared/Utils/Vec2.h`.
  - `chess_client` (executable) — SDL-based UI, renderer, texture manager and Entities. Look at `src/Client/Client.cpp`, `src/Client/Window/SDLWindow.h`, `src/Client/Renderers/SDLRenderer.*`, `src/Client/Textures/SDLTextureMgr.*`.
  - `chess_server` (executable) — currently a stub; server code lives under `src/Server`.

Integration: both client and server link against `chess_shared` (see top-level `CMakeLists.txt`). The client integrates with SDL3 and SDL3_image (or a vendored SDL under `vendored/SDL` when `ChessProject_Vendored` is ON).

## Build / test / debug (concrete commands for Windows PowerShell)
- Generate Visual Studio solution and build (x64 example):
```powershell
mkdir build; cmake -S . -B build -G "Visual Studio 17 2022" -A x64; cmake --build build --config RelWithDebInfo
```
- Alternatively open the generated solution `build/ChessProject.sln` in Visual Studio.
- Run tests (Catch2) from build directory:
```powershell
cmake --build build --config RelWithDebInfo --target chess_tests
cd build\RelWithDebInfo
.\chess_tests.exe
# or use ctest from build:
cd build; ctest -C RelWithDebInfo --output-on-failure
```
- Important CMake options:
  - `-DChessProject_Vendored=ON` to build using `vendored/SDL` instead of system SDL packages.
  - Project uses C++23 (see `CMakeLists.txt`) and treats warnings as errors for MSVC (`/W4 /WX`).

## Project-specific conventions & patterns
- Interfaces are prefixed with `I` (e.g., `IWindow`, `ITextureMgr`, `IRenderer`, `ITexture`). Implementations often use a provider prefix like `SDLWindow`, `SDLTextureMgr`, `SDLRenderer`.
- Include guards use the `__H_<NAME>` pattern (see many headers).
- Resource ownership uses `std::unique_ptr` and custom deleters for SDL pointers (see `SDLWindow.h` with `SDLWindowDeleter` / `SDLRendererDeleter`). Follow these RAII patterns when adding SDL resources.
- Entities/renderables implement an `IDrawable` interface and are managed by the window/scene. Example: `src/Client/Entities/Piece.*` and `src/Client/Entities/Board.*`.
- Code style: project prefers small header include footprints, explicit `std::` usage, and modern C++ idioms.

## Integration & external dependencies
- System dependencies: SDL3, SDL3_image, Catch2 (testing). CMake `find_package` is used in `CMakeLists.txt`.
- Assets are under `images/` (e.g. `images/pieces/*`). Note: some code uses absolute paths for textures (see `src/Client/Client.cpp`) — update to relative or configurable paths when changing asset code.
- `chess_shared` is the single source of truth for game state and is linked into both client and server; be cautious when changing public types (provide tests).

## Small examples (copy/paste friendly)
- Load/run the client (after build):
  - From Visual Studio: run `chess_client` project.
  - From build output directory (example path): `build\RelWithDebInfo\chess_client.exe`.
- Add a new drawable entity:
  - Implement `IDrawable` in `src/Client/Entities/YourEntity.*`.
  - Construct/attach via the window API (see `Client.cpp` using `m_window->AddChild<Board>();` and `m_window->AddChild<Piece>(*texture, Vec2(x,y));`).

## Pitfalls & checks for AI edits
- This repo builds with warnings-as-errors; avoid introducing new warnings (MSVC `/WX`).
- Keep C++ standard and ABI stable: project uses C++23. Update `CMakeLists.txt` accordingly if you change language features.
- Tests are wired with Catch2 and `catch_discover_tests`; run them after changing `chess_shared` logic.
- Avoid hard-coded absolute paths (there are some in `Client.cpp`) — prefer using `images/` relative paths or CMake-configured resource paths.

## Where to look for more context (key files/folders)
- `CMakeLists.txt` — global build, vendored flag, dependencies.
- `src/Shared` — core game code and data structures (BoardState, utils).
- `src/Client` — UI, renderers, textures, entities (`Window/`, `Renderers/`, `Textures/`, `Entities/`).
- `images/` — graphical assets.
- `Tests/` and `CMakeLists.txt` sections for test wiring.

## If something is unclear
- Ask which executable or platform you intend to run (Visual Studio vs. command-line CMake) and whether SDL will be picked from system packages or `vendored/SDL`.

---
Please review — I can tighten examples, add CI notes, or merge this into an existing `copilot-instructions.md` if you have one to preserve older guidance.

## Input & event flow (mouse / UI)
- `SDLWindow::CheckForInput()` is the central event loop for input. It polls SDL events and currently handles:
  - `SDL_EVENT_MOUSE_BUTTON_DOWN`: computes a board square from the mouse position using hard-coded offsets and tile size (see `src/Client/Window/SDLWindow.cpp`). The constants used are:
    - X_OFFSET = 576.0f, Y_OFFSET = 156.0f, TILE_SIZE = 96.0f
    - The code computes adjusted coordinates then row/col via integer division and prints them to stdout. Use these constants when integrating mouse-to-board logic or replace with configurable values.
  - `SDL_EVENT_MOUSE_BUTTON_UP`: placeholder for drop/placement logic (currently empty).
  - `SDL_EVENT_QUIT`: sets `m_running = false`.

## Caveats & discovered issues (actionable)
- IDrawable children storage: `IWindow` stores children as `std::vector<std::unique_ptr<IDrawable>>` (good), but `IDrawable` itself declares `std::vector<IDrawable> m_children;` (object-by-value). This risks slicing and unintended copying—prefer `std::vector<std::unique_ptr<IDrawable>>` if nested drawables are needed.
- `ITexture` lacks a virtual destructor. `ITextureMgr` stores `std::unique_ptr<ITexture>`; ensure `ITexture` has a virtual destructor before polymorphic deletion to avoid undefined behavior.
- Renderer color bug: `SDLRenderer::DrawRect` sets color with `colour.R, colour.G, colour.G` (G used twice) and alpha `uint8_t(1)`. Confirm correct channels and use proper alpha (0-255).
- Absolute asset paths: `src/Client/Client.cpp` contains absolute paths to `images/` (user-specific). Replace with relative paths or a CMake-configured resource path for portability.
- `SDLWindow::Destroy()` is empty — resources rely on RAII wrappers, but if additional teardown is required (audio, subsystems), add it here.

If you'd like, I can (1) fix the `ITexture` destructor and add a small unit test for texture management, (2) convert `IDrawable` child storage to pointer-based ownership, and (3) make the board offsets configurable via `WindowCreationArgs` or a small `ViewportConfig` struct.
