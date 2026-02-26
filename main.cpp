#include <raylib.h>

const int ROWS = 20;
const int COLS = 10;

const int BOARD_WIDTH = 300;
const int BOARD_HEIGHT = 600;

const int CELL_WIDTH = BOARD_WIDTH / COLS;
const int CELL_HEIGHT = BOARD_HEIGHT / ROWS;
const int INFO_AREA=250;

int cellInfo[ROWS][COLS] = {0};

void drawGrid();
void drawLockedCells();

int main()
{
    InitWindow(BOARD_WIDTH +INFO_AREA , BOARD_HEIGHT, "Tetris Structure");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawLockedCells();
        drawGrid();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void drawLockedCells()
{
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            if (cellInfo[y][x] == 1)
            {
                DrawRectangle(
                    x * CELL_WIDTH,
                    y * CELL_HEIGHT,
                    CELL_WIDTH,
                    CELL_HEIGHT,
                    DARKGRAY
                );
            }
        }
    }
}

void drawGrid()
{
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            DrawRectangleLines(
                x * CELL_WIDTH,
                y * CELL_HEIGHT,
                CELL_WIDTH,
                CELL_HEIGHT,
                LIGHTGRAY
            );
        }
    }
}