# Modern Tetris C++ (Professional Edition)

A feature-rich, high-performance 2D Tetris game implemented in modern C++17 using Raylib with sleek neon glassmorphism UI, SRS wall kicks, particle explosions, action popups, and multiple game modes.

[![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Raylib](https://img.shields.io/badge/Raylib-5.0-red)](https://www.raylib.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE.txt)

---

## 🌟 Key Features

* **Standard SRS Rotation & Wall Kicks**: Official Super Rotation System logic with wall kicks for competitive maneuvers.
* **Ghost Piece (Drop Shadow)**: Real-time animated drop silhouette preview.
* **Hard Drop & Soft Drop**: Instant piece drops with screen feedback and customizable drop points.
* **Hold Piece System**: Swap out piece for emergency use (`C` or `Shift`).
* **Next Piece Queue**: 7-Bag Randomizer showing the upcoming 3 to 5 pieces.
* **Particle FX & Screen Shake**: Visual particle bursts on line clears and hard drops.
* **Combo & Action Popups**: Text popups for *"DOUBLE!"*, *"TRIPLE!"*, *"TETRIS!"*, *"T-SPIN!"*, and *"B2B"*.
* **Multiple Game Modes**:
  * **Marathon**: Classic progressive speed challenge.
  * **Sprint (40-Lines)**: Speedrun line clearing mode.
  * **Ultra (2-Minute)**: High score attack in 120 seconds.
  * **Zen**: Unlimited relaxed practice mode.
* **Persistent High Scores**: Automatic local saving of scores and stats.

---

## 📁 Project Structure

```text
Tetris/
├── CMakeLists.txt             # Multi-platform CMake build script
├── Makefile                   # Fast Make compilation script
├── include/
│   ├── Common.hpp             # Grid size, color schemes, theme constants
│   ├── Piece.hpp              # Tetromino shapes, rotation states & SRS wall kicks
│   ├── Board.hpp              # Grid collision detection & row clearing
│   ├── ParticleSystem.hpp     # Particle explosion visual engine
│   ├── AudioManager.hpp       # Sound effects & BGM player interface
│   ├── ScoreManager.hpp       # High score disk saving, combo & level math
│   ├── UI.hpp                 # Glassmorphic side panels, HUD & overlays
│   └── Game.hpp               # Main game state loop and input handler
├── src/                       # Object implementations (.cpp)
├── vendor/raylib/             # Bundled Raylib 5.0 precompiled library
├── main.cpp                   # Clean application launcher
└── README.md
```

---

## 🚀 Quick Start (Zero Setup Needed)

### Prerequisites
- C++17 compliant compiler (`g++` or `clang++`)
- `make` or `cmake`

### Build & Run

#### Linux / macOS
```bash
# Build using Makefile (uses bundled Raylib 5.0)
make

# Run the game
./game
```

#### Using CMake (Cross-Platform)
```bash
mkdir build && cd build
cmake ..
make
./Tetris
```

---

## 🎮 Game Controls

| Action | Key |
|--------|-----|
| Move Left / Right | <kbd>←</kbd> / <kbd>→</kbd> |
| Rotate Clockwise | <kbd>↑</kbd> |
| Soft Drop | <kbd>↓</kbd> |
| Hard Drop (Instant) | <kbd>Space</kbd> |
| Hold Piece | <kbd>C</kbd> or <kbd>Left Shift</kbd> |
| Pause Game | <kbd>P</kbd> |
| Restart (Game Over) | <kbd>R</kbd> |

---

## 📄 License

Distributed under the [MIT License](LICENSE.txt).
