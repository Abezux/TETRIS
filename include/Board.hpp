#ifndef BOARD_HPP
#define BOARD_HPP

#include "Common.hpp"
#include "Piece.hpp"
#include <vector>

class Board {
public:
    Board();

    void reset();
    bool isValidPosition(const Piece& piece) const;
    bool isValidPosition(const std::vector<Position>& cells) const;

    bool lockPiece(const Piece& piece);
    int checkAndClearLines(std::vector<int>& clearedRowIndices);
    
    Cell getCell(int r, int c) const;
    void drawGrid() const;
    void drawBoardCells() const;
    void drawGhostPiece(const Piece& activePiece) const;

    Position getGhostPosition(const Piece& activePiece) const;

private:
    Cell grid[BOARD_ROWS][BOARD_COLS];

    bool isRowFull(int row) const;
    void clearRow(int row);
    void shiftRowsDown(int startRow);
};

#endif // BOARD_HPP
