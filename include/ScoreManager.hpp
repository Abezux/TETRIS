#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

#include "Common.hpp"
#include <string>

struct ActionPopup {
    std::string text;
    Color color;
    float timer;     // Remaining duration in seconds
    float maxTimer;  // Initial duration
    float posY;      // Vertical floating position
};

class ScoreManager {
public:
    ScoreManager();

    void reset();
    void addLinesCleared(int lines, bool isTSpin = false, bool hardDropped = false);
    void addSoftDropPoints(int points);
    void addHardDropPoints(int distance);

    int getScore() const { return score; }
    int getHighScore() const { return highScore; }
    int getLines() const { return linesCleared; }
    int getLevel() const { return level; }
    int getCombo() const { return comboCount; }
    bool isBackToBack() const { return backToBack; }

    float getFallDelay() const;

    void loadHighScore();
    void saveHighScore();

    void updatePopups(float dt);
    void drawPopups() const;

private:
    int score;
    int highScore;
    int linesCleared;
    int level;
    int comboCount;
    bool backToBack;

    std::vector<ActionPopup> popups;

    void triggerPopup(const std::string& text, Color color);
};

#endif // SCOREMANAGER_HPP
