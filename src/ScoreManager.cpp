#include "ScoreManager.hpp"
#include <fstream>
#include <cmath>
#include <algorithm>

ScoreManager::ScoreManager() {
    loadHighScore();
    reset();
}

void ScoreManager::reset() {
    score = 0;
    linesCleared = 0;
    level = 1;
    comboCount = -1;
    backToBack = false;
    popups.clear();
}

void ScoreManager::addLinesCleared(int lines, bool isTSpin, bool hardDropped) {
    if (lines <= 0 && !isTSpin) {
        comboCount = -1; // Reset combo if no line cleared
        return;
    }

    comboCount++;
    int baseScore = 0;
    std::string text = "";
    Color popupColor = UITheme::TextPrimary;

    if (isTSpin) {
        if (lines == 0) { baseScore = 100 * level; text = "T-SPIN!"; popupColor = Color{ 200, 100, 255, 255 }; }
        else if (lines == 1) { baseScore = 800 * level; text = "T-SPIN SINGLE!"; popupColor = Color{ 220, 120, 255, 255 }; }
        else if (lines == 2) { baseScore = 1200 * level; text = "T-SPIN DOUBLE!"; popupColor = Color{ 240, 140, 255, 255 }; }
        else if (lines == 3) { baseScore = 1600 * level; text = "T-SPIN TRIPLE!"; popupColor = Color{ 255, 160, 255, 255 }; }
    } else {
        switch (lines) {
            case 1: baseScore = 100 * level; text = "SINGLE!"; popupColor = UITheme::TextSecondary; break;
            case 2: baseScore = 300 * level; text = "DOUBLE!"; popupColor = Color{ 100, 200, 255, 255 }; break;
            case 3: baseScore = 500 * level; text = "TRIPLE!"; popupColor = Color{ 255, 200, 100, 255 }; break;
            case 4: baseScore = 800 * level; text = "TETRIS!"; popupColor = UITheme::AccentGold; break;
        }
    }

    // Back to Back bonus (for Tetris or T-Spin)
    bool isDifficult = (lines == 4 || isTSpin);
    if (isDifficult) {
        if (backToBack) {
            baseScore = static_cast<int>(baseScore * 1.5f);
            triggerPopup("B2B " + text, UITheme::AccentGold);
        } else {
            triggerPopup(text, popupColor);
        }
        backToBack = true;
    } else if (lines > 0) {
        backToBack = false;
        triggerPopup(text, popupColor);
    }

    // Combo bonus
    if (comboCount > 0) {
        baseScore += 50 * comboCount * level;
        triggerPopup("COMBO x" + std::to_string(comboCount), UITheme::AccentNeon);
    }

    score += baseScore;
    linesCleared += lines;
    level = (linesCleared / 10) + 1;

    if (score > highScore) {
        highScore = score;
        saveHighScore();
    }
}

void ScoreManager::addSoftDropPoints(int points) {
    score += points;
    if (score > highScore) {
        highScore = score;
        saveHighScore();
    }
}

void ScoreManager::addHardDropPoints(int distance) {
    score += distance * 2;
    if (score > highScore) {
        highScore = score;
        saveHighScore();
    }
}

float ScoreManager::getFallDelay() const {
    // Official Tetris gravity formula (in seconds per cell)
    float speed = std::pow(0.8f - ((level - 1) * 0.007f), level - 1);
    return std::max(0.05f, speed);
}

void ScoreManager::loadHighScore() {
    highScore = 0;
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
}

void ScoreManager::saveHighScore() {
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}

void ScoreManager::triggerPopup(const std::string& text, Color color) {
    popups.push_back(ActionPopup{ text, color, 1.2f, 1.2f, (float)BOARD_OFFSET_Y + 200 });
}

void ScoreManager::updatePopups(float dt) {
    for (auto it = popups.begin(); it != popups.end();) {
        it->timer -= dt;
        it->posY -= 30.0f * dt; // Float upwards
        if (it->timer <= 0) {
            it = popups.erase(it);
        } else {
            ++it;
        }
    }
}

void ScoreManager::drawPopups() const {
    for (const auto& popup : popups) {
        float alpha = popup.timer / popup.maxTimer;
        Color col = ColorAlpha(popup.color, alpha);
        int textWidth = MeasureText(popup.text.c_str(), 24);
        int posX = BOARD_OFFSET_X + (BOARD_COLS * CELL_SIZE) / 2 - textWidth / 2;
        DrawText(popup.text.c_str(), posX, (int)popup.posY, 24, col);
    }
}
