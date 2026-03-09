#include "Board.hpp"

Board::Board() {
    reset();
}

void Board::reset() {
    for (int r = 0; r < BOARD_ROWS; ++r) {
        for (int c = 0; c < BOARD_COLS; ++c) {
            grid[r][c].occupied = false;
            grid[r][c].type = BlockType::None;
            grid[r][c].color = { 0, 0, 0, 0 };
        }
    }
}

bool Board::isValidPosition(const Piece& piece) const {
    return isValidPosition(piece.getCellPositions());
}

bool Board::isValidPosition(const std::vector<Position>& cells) const {
    for (const auto& pos : cells) {
        if (pos.col < 0 || pos.col >= BOARD_COLS) return false;
        if (pos.row >= BOARD_ROWS) return false;
        if (pos.row >= 0 && grid[pos.row][pos.col].occupied) return false;
    }
    return true;
}

bool Board::isTouchingFloor(const Piece& piece) const {
    Piece testPiece = piece;
    testPiece.move(1, 0); // Move 1 step down
    return !isValidPosition(testPiece);
}

bool Board::lockPiece(const Piece& piece) {
    bool toppedOut = false;
    for (const auto& pos : piece.getCellPositions()) {
        if (pos.row < 0) {
            toppedOut = true;
        } else if (pos.row < BOARD_ROWS && pos.col >= 0 && pos.col < BOARD_COLS) {
            grid[pos.row][pos.col].occupied = true;
            grid[pos.row][pos.col].type = piece.getType();
            grid[pos.row][pos.col].color = GetBlockColor(piece.getType());
        }
    }
    return toppedOut;
}

int Board::checkAndClearLines(std::vector<int>& clearedRowIndices) {
    clearedRowIndices.clear();
    for (int r = BOARD_ROWS - 1; r >= 0; --r) {
        if (isRowFull(r)) {
            clearedRowIndices.push_back(r);
        }
    }

    for (int row : clearedRowIndices) {
        clearRow(row);
        shiftRowsDown(row);
    }

    return static_cast<int>(clearedRowIndices.size());
}

bool Board::isRowFull(int row) const {
    for (int c = 0; c < BOARD_COLS; ++c) {
        if (!grid[row][c].occupied) return false;
    }
    return true;
}

void Board::clearRow(int row) {
    for (int c = 0; c < BOARD_COLS; ++c) {
        grid[row][c].occupied = false;
        grid[row][c].type = BlockType::None;
    }
}

void Board::shiftRowsDown(int startRow) {
    for (int r = startRow; r > 0; --r) {
        for (int c = 0; c < BOARD_COLS; ++c) {
            grid[r][c] = grid[r - 1][c];
        }
    }
    for (int c = 0; c < BOARD_COLS; ++c) {
        grid[0][c].occupied = false;
        grid[0][c].type = BlockType::None;
    }
}

Cell Board::getCell(int r, int c) const {
    if (r >= 0 && r < BOARD_ROWS && c >= 0 && c < BOARD_COLS) {
        return grid[r][c];
    }
    return Cell{};
}

Position Board::getGhostPosition(const Piece& activePiece) const {
    Piece ghost = activePiece;
    while (isValidPosition(ghost.getCellPositions())) {
        ghost.move(1, 0);
    }
    ghost.move(-1, 0); // Backtrack 1 step
    return ghost.getPosition();
}

void Board::drawGrid() const {
    // Draw outer frame glowing border
    DrawRectangleRoundedLines(
        Rectangle{ (float)BOARD_OFFSET_X - 4, (float)BOARD_OFFSET_Y - 4, BOARD_COLS * CELL_SIZE + 8, BOARD_ROWS * CELL_SIZE + 8 },
        0.02f, 4, 3, UITheme::PanelBorder
    );

    // Board background
    DrawRectangle(BOARD_OFFSET_X, BOARD_OFFSET_Y, BOARD_COLS * CELL_SIZE, BOARD_ROWS * CELL_SIZE, UITheme::BoardBackground);

    // Inner Grid Lines
    for (int c = 0; c <= BOARD_COLS; ++c) {
        DrawLine(BOARD_OFFSET_X + c * CELL_SIZE, BOARD_OFFSET_Y, BOARD_OFFSET_X + c * CELL_SIZE, BOARD_OFFSET_Y + BOARD_ROWS * CELL_SIZE, UITheme::GridLine);
    }
    for (int r = 0; r <= BOARD_ROWS; ++r) {
        DrawLine(BOARD_OFFSET_X, BOARD_OFFSET_Y + r * CELL_SIZE, BOARD_OFFSET_X + BOARD_COLS * CELL_SIZE, BOARD_OFFSET_Y + r * CELL_SIZE, UITheme::GridLine);
    }
}

void Board::drawBoardCells() const {
    for (int r = 0; r < BOARD_ROWS; ++r) {
        for (int c = 0; c < BOARD_COLS; ++c) {
            if (grid[r][c].occupied) {
                int posX = BOARD_OFFSET_X + c * CELL_SIZE;
                int posY = BOARD_OFFSET_Y + r * CELL_SIZE;
                Color col = grid[r][c].color;

                // Main filled cell
                DrawRectangle(posX + 1, posY + 1, CELL_SIZE - 2, CELL_SIZE - 2, col);
                // Inner bevel highlight
                DrawRectangleLinesEx(Rectangle{ (float)posX + 1, (float)posY + 1, (float)CELL_SIZE - 2, (float)CELL_SIZE - 2 }, 2.0f, ColorAlpha(WHITE, 0.3f));
            }
        }
    }
}

void Board::drawGhostPiece(const Piece& activePiece) const {
    Position ghostPos = getGhostPosition(activePiece);
    auto cells = activePiece.getCellPositionsAt(ghostPos, activePiece.getRotation());
    Color color = GetBlockColor(activePiece.getType());

    // Pulsing alpha for ghost piece
    float alphaPulse = 0.4f + 0.15f * sinf(GetTime() * 4.0f);

    for (const auto& pos : cells) {
        if (pos.row >= 0) {
            int posX = BOARD_OFFSET_X + pos.col * CELL_SIZE;
            int posY = BOARD_OFFSET_Y + pos.row * CELL_SIZE;

            // Translucent glowing outline ghost piece
            DrawRectangleLinesEx(
                Rectangle{ (float)posX + 2, (float)posY + 2, (float)CELL_SIZE - 4, (float)CELL_SIZE - 4 },
                2.5f, ColorAlpha(color, alphaPulse + 0.2f)
            );
            DrawRectangle(posX + 4, posY + 4, CELL_SIZE - 8, CELL_SIZE - 8, ColorAlpha(color, alphaPulse * 0.4f));
        }
    }
}
