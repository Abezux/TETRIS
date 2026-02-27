#include <raylib.h>
using namespace std;

enum Block {BarBlock, BoxBlock, TBlock, LBlock, JBlock, ZBlock, SBlock};
enum Orientation {Up, Right, Down, Left};

struct ActiveBlock {
    Block block;
    Orientation orientation;
    int x;
    int y;
    Color color;
};

const int ROWS = 20;
const int COLS = 10;

const int BOARD_WIDTH = 300;
const int BOARD_HEIGHT = 600;

const int CELL_WIDTH = BOARD_WIDTH / COLS;
const int CELL_HEIGHT = BOARD_HEIGHT / ROWS;
const int INFO_AREA=250;

const Color WINDOW_BG_COLOR = WHITE;
const Color GRID_LINE_COLOR = LIGHTGRAY;
const Color LOCKED_CELL_COLOR = DARKGRAY;



int cellInfo[ROWS][COLS] = {0};

void drawGrid();
void drawLockedCells();

void spawnBarBlock(ActiveBlock &block);


void drawBarBlock(ActiveBlock block);


bool canBarGoDown(ActiveBlock block);
bool canBarGoLeft(ActiveBlock block);
bool canBarGoRight(ActiveBlock block);

bool canBarRotate(ActiveBlock block);

void lockBarBlock(ActiveBlock block);
void playGame(ActiveBlock &block, float &fallTime, float fallDelay);



int main()
{
    InitWindow(BOARD_WIDTH +INFO_AREA , BOARD_HEIGHT, "Tetris");
    SetTargetFPS(60);

    ActiveBlock block;
    spawnBarBlock(block);

    float fallTime = 0.0f;           
    const float FALL_DELAY = 0.5f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        playGame(block, fallTime, FALL_DELAY);
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
void lockBarBlock(ActiveBlock block)
{
    int x = block.x;
    int y = block.y;

    if(block.orientation==Up|| block.orientation==Down){
        for(int i=0;i<4;i++){
            cellInfo[y][x + i] = 1; 
        }
    }
    else { 
        for(int i=0;i<4;i++){
            cellInfo[y + i][x] = 1;
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
void spawnBarBlock(ActiveBlock &block){
    block.block=BarBlock;
    block.orientation= static_cast<Orientation> (GetRandomValue(0,3));
    block.x=3;
    block.y=0;
    block.color=SKYBLUE;
}
void drawBarBlock(ActiveBlock block){
    int x = block.x;
    int y= block.y;
    if(block.orientation == Up || block.orientation == Down){
        for (int i=0;i<4;i++){
            DrawRectangle((x+i)*CELL_WIDTH,y*CELL_HEIGHT,CELL_WIDTH,CELL_HEIGHT,block.color);
        }
    }
    else if(block.orientation==Right|| block.orientation == Left){
        for (int i=0;i<4;i++){
            DrawRectangle(x*CELL_WIDTH,(y+i)*CELL_HEIGHT,CELL_WIDTH,CELL_HEIGHT,block.color);
        }
    }
}
bool canBarGoDown(ActiveBlock block){
    int x=block.x;
    int y=block.y;
    if(block.orientation==Up|| block.orientation==Down){
        if(y+1>=ROWS) return false;
        for (int i=0;i<4;i++){
            if (cellInfo[y+1][x+i]==1) return false;
        }
    }
    else {
        if (y + 4 >= ROWS) return false;
        if (cellInfo[y + 4][x] == 1) return false;
    }
    return true;
}
bool canBarGoLeft(ActiveBlock block){
    int x=block.x;
    int y=block.y;
    if(block.orientation==Up|| block.orientation==Down){
        if(x-1<0) return false;
        for(int i=0;i<4;i++){
            if(cellInfo[y][x-1+i]==1) return false;
        }
    }
    else {
        if (x - 1 < 0) return false;
        for (int i = 0; i < 4; i++){
            if (cellInfo[y + i][x - 1] == 1) return false;
        }
    }
    return true;
 }

bool canBarGoRight(ActiveBlock block){
    
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) 
    {
        if (x + 4 >= COLS) return false;
        for (int i = 0; i < 4; i++)
            if (cellInfo[y][x + i + 1] == 1) return false;
    }
    else 
    {
        if (x + 1 >= COLS) return false;
        for (int i = 0; i < 4; i++)
            if (cellInfo[y + i][x + 1] == 1) return false;
    }
    return true;

}
bool canBarRotate(ActiveBlock block)
{
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) 
    {
        if (y + 4 > ROWS) return false; 
        for (int i = 0; i < 4; i++)
            if (cellInfo[y + i][x] == 1) return false; 
    }
    else 
    {
        if (x + 4 > COLS) return false; 
        for (int i = 0; i < 4; i++)
            if (cellInfo[y][x + i] == 1) return false; 
    }
    return true;
}
void playGame(ActiveBlock &block, float &fallTime, float fallDelay){
    
    if (IsKeyPressed(KEY_LEFT) && canBarGoLeft(block)) block.x--;
    if (IsKeyPressed(KEY_RIGHT) && canBarGoRight(block)) block.x++;
    if (IsKeyPressed(KEY_UP) && canBarRotate(block))
    {
        if (block.orientation == Up || block.orientation == Down)
            block.orientation = Right;
        else
            block.orientation = Up;
    }

    
    fallTime += GetFrameTime();
    if (fallTime >= fallDelay)
    {
        if (canBarGoDown(block))
            block.y++;              
        else
        {
            lockBarBlock(block);
            spawnBarBlock(block);   
        }
        fallTime = 0.0f;            
    }
    
    drawBarBlock(block);
}