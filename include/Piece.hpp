#ifndef PIECE_HPP
#define PIECE_HPP

#include "Common.hpp"
#include <vector>

class Piece {
public:
    Piece();
    Piece(BlockType type);

    BlockType getType() const { return type; }
    RotationState getRotation() const { return rotation; }
    Position getPosition() const { return position; }

    void setPosition(int row, int col) { position.row = row; position.col = col; }
    void setRotation(RotationState rot) { rotation = rot; }

    std::vector<Position> getCellPositions() const;
    std::vector<Position> getCellPositionsAt(Position pos, RotationState rot) const;

    void rotateClockwise();
    void rotateCounterClockwise();
    void move(int rowOffset, int colOffset);

    static std::vector<Position> GetWallKicks(BlockType type, RotationState currentRot, RotationState targetRot);

private:
    BlockType type;
    RotationState rotation;
    Position position; // Top-left position on the board grid
};

#endif // PIECE_HPP
