#include "UI.hpp"
#include <string>

UI::UI() {}

void UI::drawPanel(int x, int y, int width, int height, const char* title) const {
    // Glassmorphism card background
    DrawRectangleRounded(
        Rectangle{ (float)x, (float)y, (float)width, (float)height },
        0.08f, 6, UITheme::PanelBackground
    );
    // Glowing border outline
    DrawRectangleRoundedLines(
        Rectangle{ (float)x, (float)y, (float)width, (float)height },
        0.08f, 6, 2.0f, UITheme::PanelBorder
    );

    if (title && title[0] != '\0') {
        DrawText(title, x + 16, y + 12, 16, UITheme::TextSecondary);
    }
}

void UI::drawPiecePreview(const Piece& piece, int centerX, int centerY) const {
    if (piece.getType() == BlockType::None) return;

    auto cells = piece.getCellPositionsAt({0, 0}, RotationState::R0);
    Color color = GetBlockColor(piece.getType());

    // Compute bounding box to center piece
    int minR = 4, maxR = -1, minC = 4, maxC = -1;
    for (const auto& pos : cells) {
        if (pos.row < minR) minR = pos.row;
        if (pos.row > maxR) maxR = pos.row;
        if (pos.col < minC) minC = pos.col;
        if (pos.col > maxC) maxC = pos.col;
    }

    float pWidth = (maxC - minC + 1) * 20.0f;
    float pHeight = (maxR - minR + 1) * 20.0f;

    float startX = centerX - pWidth / 2.0f;
    float startY = centerY - pHeight / 2.0f;

    for (const auto& pos : cells) {
        float drawX = startX + (pos.col - minC) * 20.0f;
        float drawY = startY + (pos.row - minR) * 20.0f;

        DrawRectangle((int)drawX, (int)drawY, 18, 18, color);
        DrawRectangleLinesEx(Rectangle{ drawX, drawY, 18.0f, 18.0f }, 1.5f, ColorAlpha(WHITE, 0.4f));
    }
}

void UI::drawHUD(const ScoreManager& scoreMgr, const Piece& holdPiece, const std::vector<Piece>& nextQueue, bool canHold) const {
    // Left Panel: HOLD
    int leftX = 40;
    int leftY = BOARD_OFFSET_Y;
    int leftW = 160;

    drawPanel(leftX, leftY, leftW, 140, "HOLD");
    if (canHold) {
        drawPiecePreview(holdPiece, leftX + leftW / 2, leftY + 80);
    } else {
        // Locked hold indicator
        drawPiecePreview(holdPiece, leftX + leftW / 2, leftY + 80);
    }

    // Left Panel: STATS / SCORE
    int scoreY = leftY + 160;
    drawPanel(leftX, scoreY, leftW, 260, "SCORE");
    DrawText(std::to_string(scoreMgr.getScore()).c_str(), leftX + 16, scoreY + 40, 24, UITheme::AccentNeon);

    DrawText("HIGH SCORE", leftX + 16, scoreY + 80, 14, UITheme::TextSecondary);
    DrawText(std::to_string(scoreMgr.getHighScore()).c_str(), leftX + 16, scoreY + 100, 20, UITheme::AccentGold);

    DrawText("LEVEL", leftX + 16, scoreY + 140, 14, UITheme::TextSecondary);
    DrawText(std::to_string(scoreMgr.getLevel()).c_str(), leftX + 16, scoreY + 160, 20, UITheme::TextPrimary);

    DrawText("LINES", leftX + 16, scoreY + 200, 14, UITheme::TextSecondary);
    DrawText(std::to_string(scoreMgr.getLines()).c_str(), leftX + 16, scoreY + 220, 20, UITheme::TextPrimary);

    // Right Panel: NEXT QUEUE (shows next 3 pieces)
    int rightX = BOARD_OFFSET_X + BOARD_COLS * CELL_SIZE + 40;
    int rightY = BOARD_OFFSET_Y;
    int rightW = 160;

    drawPanel(rightX, rightY, rightW, 360, "NEXT");
    for (size_t i = 0; i < nextQueue.size() && i < 3; ++i) {
        drawPiecePreview(nextQueue[i], rightX + rightW / 2, rightY + 65 + (int)i * 95);
    }
}

void UI::drawHeader() const {
    DrawText("TETRIS", BOARD_OFFSET_X, 10, 24, UITheme::AccentNeon);
}

void UI::drawControlsHint() const {
    int hintY = BOARD_OFFSET_Y + BOARD_ROWS * CELL_SIZE + 15;
    DrawText("Controls: [< >] Move  [^] Rotate  [v] Soft Drop  [Space] Hard Drop  [C] Hold  [P] Pause", BOARD_OFFSET_X - 60, hintY, 13, UITheme::TextSecondary);
}

void UI::drawGameOverScreen(int finalScore, int highScore) const {
    DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, ColorAlpha(BLACK, 0.8f));

    int boxW = 380;
    int boxH = 260;
    int boxX = WINDOW_WIDTH / 2 - boxW / 2;
    int boxY = WINDOW_HEIGHT / 2 - boxH / 2;

    drawPanel(boxX, boxY, boxW, boxH, "");

    DrawText("GAME OVER", boxX + 100, boxY + 35, 32, Color{ 255, 60, 80, 255 });
    
    std::string scoreStr = "Final Score: " + std::to_string(finalScore);
    DrawText(scoreStr.c_str(), boxX + 80, boxY + 95, 20, UITheme::TextPrimary);

    std::string highStr = "Best Score: " + std::to_string(highScore);
    DrawText(highStr.c_str(), boxX + 85, boxY + 130, 18, UITheme::AccentGold);

    DrawText("Press [R] to Play Again", boxX + 90, boxY + 185, 16, UITheme::AccentNeon);
}

void UI::drawPauseOverlay() const {
    DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, ColorAlpha(BLACK, 0.6f));
    DrawText("PAUSED", WINDOW_WIDTH / 2 - 70, WINDOW_HEIGHT / 2 - 20, 36, UITheme::AccentNeon);
    DrawText("Press [P] to Resume", WINDOW_WIDTH / 2 - 90, WINDOW_HEIGHT / 2 + 30, 16, UITheme::TextSecondary);
}
