#ifndef GAME_HPP
#define GAME_HPP

#include "Common.hpp"
#include "Board.hpp"
#include "Piece.hpp"
#include "ScoreManager.hpp"
#include "UI.hpp"
#include "ParticleSystem.hpp"
#include "AudioManager.hpp"
#include <vector>

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    GameState currentState;
    GameMode currentMode;

    Board board;
    Piece currentPiece;
    Piece holdPiece;
    bool canHold;
    
    std::vector<Piece> nextQueue;

    ScoreManager scoreMgr;
    UI ui;
    ParticleSystem particleSys;
    AudioManager audioMgr;

    float fallTimer;
    float lockTimer;
    bool isLocking;

    // DAS (Delayed Auto Shift) & ARR (Auto Repeat Rate) timers
    float moveTimer;
    float dasTimer;

    void handleInput();
    void update(float dt);
    void render();

    void spawnPiece();
    void refillNextQueue();
    BlockType getRandomBlockType();
    
    void performHold();
    void performHardDrop();
    void restartGame();

    std::vector<BlockType> bag;
    void generate7Bag();
};

#endif // GAME_HPP
