#ifndef COMMON_HPP
#define COMMON_HPP

#include <raylib.h>
#include <vector>
#include <string>

// Grid Dimensions
constexpr int BOARD_ROWS = 20;
constexpr int BOARD_COLS = 10;
constexpr int CELL_SIZE = 32; // 32x32 pixels per cell -> 320x640 board

// UI Layout Dimensions
constexpr int BOARD_OFFSET_X = 240; // Centered board area
constexpr int BOARD_OFFSET_Y = 40;
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 720;

// Game Enums
enum class BlockType {
    None = 0,
    I,
    O,
    T,
    L,
    J,
    Z,
    S
};

enum class RotationState {
    R0 = 0,
    R90,
    R180,
    R270
};

enum class GameState {
    Menu,
    Playing,
    Pause,
    GameOver,
    Settings,
    Stats
};

enum class GameMode {
    Marathon,   // Classic progressive speed
    Sprint40,   // Clear 40 lines speedrun
    Ultra2Min,  // 2 Minute score attack
    Zen         // Endless relaxed
};

enum class ThemeType {
    NeonCyber,
    RetroArcade,
    Minimalist
};

// Position Structure
struct Position {
    int row;
    int col;
};

// Board Cell
struct Cell {
    bool occupied = false;
    BlockType type = BlockType::None;
    Color color = { 0, 0, 0, 0 };
};

// Standard Tetromino Colors (Modern Guideline & Neon)
inline Color GetBlockColor(BlockType type) {
    switch (type) {
        case BlockType::I: return Color{ 0, 240, 240, 255 };   // Cyan
        case BlockType::O: return Color{ 240, 240, 0, 255 };   // Yellow
        case BlockType::T: return Color{ 160, 0, 240, 255 };   // Purple
        case BlockType::L: return Color{ 240, 160, 0, 255 };   // Orange
        case BlockType::J: return Color{ 0, 0, 240, 255 };     // Blue
        case BlockType::Z: return Color{ 240, 0, 0, 255 };     // Red
        case BlockType::S: return Color{ 0, 240, 0, 255 };     // Green
        default: return Color{ 40, 40, 50, 255 };
    }
}

// UI Color Palette (Glassmorphism & Neon)
namespace UITheme {
    constexpr Color BackgroundDark  = Color{ 15, 18, 28, 255 };
    constexpr Color BoardBackground = Color{ 22, 27, 42, 240 };
    constexpr Color GridLine        = Color{ 45, 55, 75, 180 };
    constexpr Color PanelBackground = Color{ 28, 35, 54, 220 };
    constexpr Color PanelBorder     = Color{ 0, 240, 240, 120 };
    constexpr Color TextPrimary     = Color{ 240, 245, 255, 255 };
    constexpr Color TextSecondary   = Color{ 140, 155, 185, 255 };
    constexpr Color AccentNeon      = Color{ 0, 240, 240, 255 };
    constexpr Color AccentGold      = Color{ 255, 215, 0, 255 };
}

#endif // COMMON_HPP
