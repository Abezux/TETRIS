#include "Game.hpp"
#include <algorithm>
#include <random>
#include <chrono>

Game::Game() 
    : currentState(GameState::Playing), currentMode(GameMode::Marathon),
      canHold(true), fallTimer(0.0f), lockTimer(0.0f), isLocking(false),
      moveTimer(0.0f), dasTimer(0.0f) 
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris - Modern Edition");
    SetTargetFPS(60);
    audioMgr.init();

    restartGame();
}

Game::~Game() {
    audioMgr.cleanup();
    CloseWindow();
}

void Game::generate7Bag() {
    std::vector<BlockType> newBag = {
        BlockType::I, BlockType::O, BlockType::T, BlockType::L,
        BlockType::J, BlockType::Z, BlockType::S
    };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(newBag.begin(), newBag.end(), std::default_random_engine(seed));

    for (auto type : newBag) {
        bag.push_back(type);
    }
}

BlockType Game::getRandomBlockType() {
    if (bag.empty()) {
        generate7Bag();
    }
    BlockType type = bag.front();
    bag.erase(bag.begin());
    return type;
}

void Game::refillNextQueue() {
    while (nextQueue.size() < 5) {
        nextQueue.push_back(Piece(getRandomBlockType()));
    }
}

void Game::spawnPiece() {
    refillNextQueue();
    currentPiece = nextQueue.front();
    nextQueue.erase(nextQueue.begin());
    refillNextQueue();

    currentPiece.setPosition(0, 3);
    canHold = true;
    isLocking = false;
    lockTimer = 0.0f;

    if (!board.isValidPosition(currentPiece)) {
        currentState = GameState::GameOver;
        audioMgr.playSound(SoundEffect::GameOver);
    }
}

void Game::restartGame() {
    board.reset();
    scoreMgr.reset();
    bag.clear();
    nextQueue.clear();
    holdPiece = Piece(BlockType::None);

    currentState = GameState::Playing;
    spawnPiece();
}

void Game::performHold() {
    if (!canHold) return;

    audioMgr.playSound(SoundEffect::Hold);
    if (holdPiece.getType() == BlockType::None) {
        holdPiece = Piece(currentPiece.getType());
        spawnPiece();
    } else {
        Piece temp = holdPiece;
        holdPiece = Piece(currentPiece.getType());
        currentPiece = Piece(temp.getType());
        currentPiece.setPosition(0, 3);
    }
    canHold = false;
}

void Game::performHardDrop() {
    int dropDistance = board.hardDropPiece(currentPiece);
    scoreMgr.addHardDropPoints(dropDistance);
    
    // Spawn hard drop sparks
    particleSys.spawnHardDropParticles(currentPiece.getPosition().col, currentPiece.getPosition().row, GetBlockColor(currentPiece.getType()));
    audioMgr.playSound(SoundEffect::HardDrop);

    // Lock piece immediately
    bool toppedOut = board.lockPiece(currentPiece);
    if (toppedOut) {
        currentState = GameState::GameOver;
        audioMgr.playSound(SoundEffect::GameOver);
        return;
    }

    std::vector<int> clearedRows;
    int cleared = board.checkAndClearLines(clearedRows);
    if (cleared > 0) {
        scoreMgr.addLinesCleared(cleared);
        for (int r : clearedRows) {
            particleSys.spawnLineClearParticles(r, BOARD_COLS, GetBlockColor(currentPiece.getType()));
        }
        audioMgr.playSound((cleared == 4) ? SoundEffect::TetrisClear : SoundEffect::LineClear);
    }

    spawnPiece();
}

void Game::handleInput() {
    if (currentState == GameState::GameOver) {
        if (IsKeyPressed(KEY_R)) restartGame();
        return;
    }

    if (IsKeyPressed(KEY_P)) {
        currentState = (currentState == GameState::Playing) ? GameState::Pause : GameState::Playing;
    }

    if (currentState != GameState::Playing) return;

    // Movement (Left / Right)
    if (IsKeyPressed(KEY_LEFT)) {
        Piece test = currentPiece;
        test.move(0, -1);
        if (board.isValidPosition(test)) {
            currentPiece.move(0, -1);
            audioMgr.playSound(SoundEffect::Move);
        }
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        Piece test = currentPiece;
        test.move(0, 1);
        if (board.isValidPosition(test)) {
            currentPiece.move(0, 1);
            audioMgr.playSound(SoundEffect::Move);
        }
    }

    // Rotation (Up Arrow / SRS Wall Kick)
    if (IsKeyPressed(KEY_UP)) {
        RotationState targetRot = static_cast<RotationState>((static_cast<int>(currentPiece.getRotation()) + 1) % 4);
        auto kicks = Piece::GetWallKicks(currentPiece.getType(), currentPiece.getRotation(), targetRot);

        for (const auto& kick : kicks) {
            Piece test = currentPiece;
            test.rotateClockwise();
            test.move(kick.row, kick.col);
            if (board.isValidPosition(test)) {
                currentPiece = test;
                audioMgr.playSound(SoundEffect::Rotate);
                break;
            }
        }
    }

    // Soft Drop (Down Arrow)
    if (IsKeyDown(KEY_DOWN)) {
        Piece test = currentPiece;
        test.move(1, 0);
        if (board.isValidPosition(test)) {
            currentPiece.move(1, 0);
            scoreMgr.addSoftDropPoints(1);
            audioMgr.playSound(SoundEffect::SoftDrop);
        }
    }

    // Hard Drop (Space)
    if (IsKeyPressed(KEY_SPACE)) {
        performHardDrop();
    }

    // Hold Piece (C or Shift)
    if (IsKeyPressed(KEY_C) || IsKeyPressed(KEY_LEFT_SHIFT)) {
        performHold();
    }
}

void Game::update(float dt) {
    if (currentState != GameState::Playing) return;

    particleSys.update(dt);
    scoreMgr.updatePopups(dt);

    // Gravity step
    fallTimer += dt;
    float delay = scoreMgr.getFallDelay();

    if (fallTimer >= delay) {
        fallTimer = 0.0f;
        Piece test = currentPiece;
        test.move(1, 0);
        if (board.isValidPosition(test)) {
            currentPiece.move(1, 0);
            isLocking = false;
            lockTimer = 0.0f;
        } else {
            isLocking = true;
        }
    }

    // Lock delay grace period (0.5s)
    if (board.isTouchingFloor(currentPiece)) {
        isLocking = true;
        lockTimer += dt;
        if (lockTimer >= 0.5f) {
            bool toppedOut = board.lockPiece(currentPiece);
            if (toppedOut) {
                currentState = GameState::GameOver;
                audioMgr.playSound(SoundEffect::GameOver);
                return;
            }

            std::vector<int> clearedRows;
            int cleared = board.checkAndClearLines(clearedRows);
            if (cleared > 0) {
                scoreMgr.addLinesCleared(cleared);
                for (int r : clearedRows) {
                    particleSys.spawnLineClearParticles(r, BOARD_COLS, GetBlockColor(currentPiece.getType()));
                }
                audioMgr.playSound((cleared == 4) ? SoundEffect::TetrisClear : SoundEffect::LineClear);
            }

            spawnPiece();
        }
    } else {
        isLocking = false;
        lockTimer = 0.0f;
    }
}

void Game::render() {
    BeginDrawing();
    ClearBackground(UITheme::BackgroundDark);

    ui.drawHeader();
    board.drawGrid();
    board.drawBoardCells();

    if (currentState == GameState::Playing || currentState == GameState::Pause) {
        board.drawGhostPiece(currentPiece);

        // Draw Active Piece
        auto cells = currentPiece.getCellPositions();
        Color color = GetBlockColor(currentPiece.getType());
        for (const auto& pos : cells) {
            if (pos.row >= 0) {
                int posX = BOARD_OFFSET_X + pos.col * CELL_SIZE;
                int posY = BOARD_OFFSET_Y + pos.row * CELL_SIZE;
                DrawRectangle(posX + 1, posY + 1, CELL_SIZE - 2, CELL_SIZE - 2, color);
                DrawRectangleLinesEx(Rectangle{ (float)posX + 1, (float)posY + 1, (float)CELL_SIZE - 2, (float)CELL_SIZE - 2 }, 2.0f, WHITE);
            }
        }
    }

    particleSys.draw();
    scoreMgr.drawPopups();
    ui.drawHUD(scoreMgr, holdPiece, nextQueue, canHold);
    ui.drawControlsHint();

    if (currentState == GameState::Pause) {
        ui.drawPauseOverlay();
    } else if (currentState == GameState::GameOver) {
        ui.drawGameOverScreen(scoreMgr.getScore(), scoreMgr.getHighScore());
    }

    EndDrawing();
}

void Game::run() {
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        handleInput();
        update(dt);
        render();
    }
}
