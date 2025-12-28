# Chess Game (C++/SFML)

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

1. **Dependencies:**

   - C++17 compiler (tested with GCC)
   - CMake ≥ 3.10
   - Internet connection (for automatic SFML download)

2. **Build:**

   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run:**
   ```sh
   ./chess
   ```

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
- Improve UI/UX (move hints, animations, score)
- Add AI or multiplayer

## License

This project is for educational and personal use only.
