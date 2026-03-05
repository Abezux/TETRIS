#include "Piece.hpp"

// Standard 4-rotation state matrices for all 7 blocks
static const int PIECE_SHAPES[8][4][4][4] = {
    // None
    { {{0}} },
    // I Block
    {
        {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
        {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}
    },
    // O Block
    {
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}
    },
    // T Block
    {
        {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}
    },
    // L Block
    {
        {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
        {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}
    },
    // J Block
    {
        {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}
    },
    // Z Block
    {
        {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
        {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
        {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
        {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}
    },
    // S Block
    {
        {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
        {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
        {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
        {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}
    }
};

// SRS Wall Kick offsets for J, L, S, T, Z pieces (row, col)
static const Position JLSTZ_KICKS[4][5] = {
    // 0->R (0->90), R->0
    { {0,0}, {0,-1}, {-1,-1}, {2,0}, {2,-1} },
    // R->2 (90->180), 2->R
    { {0,0}, {0,1}, {1,1}, {-2,0}, {-2,1} },
    // 2->L (180->270), L->2
    { {0,0}, {0,1}, {-1,1}, {2,0}, {2,1} },
    // L->0 (270->0), 0->L
    { {0,0}, {0,-1}, {1,-1}, {-2,0}, {-2,-1} }
};

// SRS Wall Kick offsets for I piece (row, col)
static const Position I_KICKS[4][5] = {
    // 0->R
    { {0,0}, {0,-2}, {0,1}, {1,-2}, {-2,1} },
    // R->2
    { {0,0}, {0,-1}, {0,2}, {-2,-1}, {1,2} },
    // 2->L
    { {0,0}, {0,2}, {0,-1}, {-1,2}, {2,-1} },
    // L->0
    { {0,0}, {0,1}, {0,-2}, {2,1}, {-1,-2} }
};

Piece::Piece() : Piece(BlockType::I) {}

Piece::Piece(BlockType type) : type(type), rotation(RotationState::R0), position({0, 3}) {}

std::vector<Position> Piece::getCellPositions() const {
    return getCellPositionsAt(position, rotation);
}

std::vector<Position> Piece::getCellPositionsAt(Position pos, RotationState rot) const {
    std::vector<Position> cells;
    int typeIdx = static_cast<int>(type);
    int rotIdx = static_cast<int>(rot);

    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            if (PIECE_SHAPES[typeIdx][rotIdx][r][c]) {
                cells.push_back({ pos.row + r, pos.col + c });
            }
        }
    }
    return cells;
}

void Piece::rotateClockwise() {
    int current = static_cast<int>(rotation);
    rotation = static_cast<RotationState>((current + 1) % 4);
}

void Piece::rotateCounterClockwise() {
    int current = static_cast<int>(rotation);
    rotation = static_cast<RotationState>((current + 3) % 4);
}

void Piece::move(int rowOffset, int colOffset) {
    position.row += rowOffset;
    position.col += colOffset;
}

std::vector<Position> Piece::GetWallKicks(BlockType type, RotationState currentRot, RotationState targetRot) {
    std::vector<Position> kicks;
    if (type == BlockType::O) {
        kicks.push_back({0, 0});
        return kicks;
    }

    int from = static_cast<int>(currentRot);
    int to = static_cast<int>(targetRot);

    int kickIdx = 0;
    if ((from == 0 && to == 1) || (from == 1 && to == 0)) kickIdx = 0;
    else if ((from == 1 && to == 2) || (from == 2 && to == 1)) kickIdx = 1;
    else if ((from == 2 && to == 3) || (from == 3 && to == 2)) kickIdx = 2;
    else if ((from == 3 && to == 0) || (from == 0 && to == 3)) kickIdx = 3;

    bool clockwise = ((from + 1) % 4 == to);

    for (int i = 0; i < 5; ++i) {
        Position offset;
        if (type == BlockType::I) {
            offset = I_KICKS[kickIdx][i];
        } else {
            offset = JLSTZ_KICKS[kickIdx][i];
        }

        if (!clockwise) {
            offset.row = -offset.row;
            offset.col = -offset.col;
        }
        kicks.push_back(offset);
    }
    return kicks;
}
