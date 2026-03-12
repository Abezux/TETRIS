#ifndef UI_HPP
#define UI_HPP

#include "Common.hpp"
#include "Piece.hpp"
#include "ScoreManager.hpp"
#include <vector>

class UI {
public:
    UI();

    void drawHUD(const ScoreManager& scoreMgr, const Piece& holdPiece, const std::vector<Piece>& nextQueue, bool canHold) const;
    void drawHeader() const;
    void drawControlsHint() const;
    void drawGameOverScreen(int finalScore, int highScore) const;
    void drawPauseOverlay() const;

private:
    void drawPanel(int x, int y, int width, int height, const char* title) const;
    void drawPiecePreview(const Piece& piece, int centerX, int centerY) const;
};

#endif // UI_HPP
