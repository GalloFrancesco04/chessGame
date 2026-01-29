# Chess Game (C++)

This project is a didactic chess game developed in C++17 using the SFML graphics library. I created it as a personal exercise to practice object-oriented programming, modern C++ patterns, and to learn how to structure a medium-sized graphical application from scratch.

## Features

- Full chessboard with piece sprites and coordinate labels
- Mouse-based piece selection and movement
- Turn management and move highlighting
- Complete move validation for all chess pieces
- Modular code

## Project Structure

- `src/` — Implementation files (game loop, rendering, move validation)
- `include/` — Header files (Board, Game, enums, Square, moveValidator)
- `assets/` — Spritesheet and font (copied automatically to build directory)
- `CMakeLists.txt` — Build configuration (uses FetchContent for SFML)

## Build & Run

### Prerequisites

- C++17 compatible compiler (MSVC, GCC, or Clang)
- CMake ≥ 3.10
- Internet connection (SFML is downloaded automatically)

### Windows

```powershell
# Configure the project
mkdir build
cd build
cmake ..

# Build in Release mode
cmake --build . --config Release

# Run the game
.\Release\chess.exe
```

### Linux / macOS

```bash
# Configure and build
mkdir build
cd build
cmake ..
make

# Run the game
./chess
```

**Note:** CMake automatically handles SFML download, DLL copying (Windows), and asset deployment.

## How It Works

- **Game Loop:**
  The `Game` class manages the main loop, event handling, and rendering.
- **Board Representation:**
  The `Board` class holds an 8×8 array of `Square` structs, each with a `Piece` and `Color`.
- **Move Validation:**
  The `moveValidator` class checks if a move is legal.
- **User Interaction:**
  Click to select a piece, then click a destination square. Only valid moves are allowed.

## What I Learned / Next Steps

- How to structure a C++ project with clear module boundaries
- How to use SFML for 2D graphics and input
- How to use CMake and FetchContent for dependencies

**TODO:**

- Add: castling, en passant, promotion, check/checkmate detection
- Improve UI/UX (move hints, animations, score, resolution)
- Add AI or multiplayer

## License

This project is for educational and personal use only.
