# Tetris C++

A lightweight, arcade-style 2D Tetris game implemented in C++ using Raylib.

[![C++](https://img.shields.io/badge/C%2B%2B-14%2F17-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Raylib](https://img.shields.io/badge/Raylib-4.5+-red)](https://www.raylib.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE.txt)

---

## About

A classic 2D Tetris implementation featuring grid manipulation, standard tetromino shapes (I, O, T, L, J, Z, S), rotation states, collision detection, line clearing, score & high-score tracking, and instant soft drops. Built with Raylib to provide responsive 60 FPS graphics and straightforward cross-platform compilation.

## Project Structure

```text
Tetris/
├── main.cpp                  # Main game loop, rendering, collision, and logic
├── Makefile                  # Build script for Linux, macOS, and Windows
├── LICENSE.txt               # MIT License file
├── tetris_pieces.jpg         # Tetromino rotation matrix reference chart
└── TGM_Legend_Tetra_SRS.png  # SRS rotation reference diagram
```

## Getting Started

### Prerequisites

- C++ compiler supporting C++14 or higher (`g++`, `clang++`, or MinGW)
- `make` build utility
- [Raylib](https://www.raylib.com/) (v4.5 or later)

### Build & Run

#### Linux / macOS
```bash
# Build the project
make

# Run the game
./game
```

#### Windows (with w64devkit / MinGW)
```bash
# Build using mingw32-make
mingw32-make

# Run the game
game.exe
```

### Controls

- <kbd>←</kbd> / <kbd>→</kbd> : Move piece left / right
- <kbd>↑</kbd> : Rotate piece
- <kbd>↓</kbd> : Soft drop
- <kbd>R</kbd> : Restart game on Game Over

## License

This project is licensed under the [MIT License](LICENSE.txt).
