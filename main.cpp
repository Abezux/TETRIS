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

const Color WINDOW_BG_COLOR = BLACK;
const Color GRID_LINE_COLOR = LIGHTGRAY;
const Color LOCKED_CELL_COLOR = DARKGRAY;


int score = 0;
bool isGameOver = false;
int cellInfo[ROWS][COLS] = {0};

void drawGrid();
void drawLockedCells();

void spawnBarBlock(ActiveBlock &block);
void spawnBoxBlock(ActiveBlock &block);
void spawnTBlock(ActiveBlock &block);
void spawnLBlock(ActiveBlock &block);
void spawnJBlock(ActiveBlock &block);
void spawnZBlock(ActiveBlock &block);
void spawnRandomBlock(ActiveBlock &block);

void drawBarBlock(ActiveBlock block);
void drawBoxBlock(ActiveBlock block);
void drawTBlock(ActiveBlock block);
void drawLBlock(ActiveBlock block);
void drawJBlock(ActiveBlock block);
void drawZBlock(ActiveBlock block);

bool canBarGoDown(ActiveBlock block);
bool canBoxGoDown(ActiveBlock block);
bool canTGoDown(ActiveBlock block);
bool canLGoDown(ActiveBlock block);
bool canJGoDown(ActiveBlock block);
bool canZGoDown(ActiveBlock block);

bool canBarGoLeft(ActiveBlock block);
bool canBoxGoLeft(ActiveBlock block);
bool canTGoLeft(ActiveBlock block);
bool canLGoLeft(ActiveBlock block);
bool canJGoLeft(ActiveBlock block);
bool canZGoLeft(ActiveBlock block);

bool canBarGoRight(ActiveBlock block);
bool canBoxGoRight(ActiveBlock block);
bool canTGoRight(ActiveBlock block);
bool canLGoRight(ActiveBlock block);
bool canJGoRight(ActiveBlock block);
bool canZGoRight(ActiveBlock block);

bool canBarRotate(ActiveBlock block);
bool canBoxRotate(ActiveBlock block);
bool canTRotate(ActiveBlock block);
bool canLRotate(ActiveBlock block);
bool canJRotate(ActiveBlock block);
bool canZRotate(ActiveBlock block);

void lockBarBlock(ActiveBlock block);
void lockBoxBlock(ActiveBlock block);
void lockTBlock(ActiveBlock block);
void lockLBlock(ActiveBlock block);
void lockJBlock(ActiveBlock block);
void lockZBlock(ActiveBlock block);

void playGame(ActiveBlock &block, float &fallTime, float fallDelay);



int main()
{
    InitWindow(BOARD_WIDTH +INFO_AREA , BOARD_HEIGHT, "Tetris");
    SetTargetFPS(60);

    
    ActiveBlock block;
    spawnRandomBlock(block);

    float fallTime = 0.0f;           
    const float FALL_DELAY = 0.1f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WINDOW_BG_COLOR);
        playGame(block, fallTime, FALL_DELAY);
        
   
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
                    LOCKED_CELL_COLOR
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
void lockBoxBlock(ActiveBlock block)
{
    int x = block.x;
    int y = block.y;
    for (int row = 0; row < 2; row++)
    {
        for (int col = 0; col < 2; col++)
        {
            cellInfo[y + row][x + col] = 1;
        }
    }
}
void lockTBlock(ActiveBlock block){
    int x =block.x;
    int y=block.y;
    switch(block.orientation){
        case Up:
            cellInfo[y][x+1] = 1;
            for(int col=0;col<3;col++){
                cellInfo[y+1][x+col] =1;
            }break;
        case Right:
            cellInfo[y+1][x + 1] =1;
            for(int row=0;row<3;row++){
                  cellInfo[y+row][x] =1;
            }break;
        case Left:
            cellInfo[y+1][x] =1;
            for(int row=0;row<3;row++){
                  cellInfo[y+row][x+1] =1;
            }break;
        case Down:
            cellInfo[y+1][x+1] =1;
            for(int col=0;col<3;col++){
                  cellInfo[y][x+col] =1;
            }break;

}}
void lockLBlock(ActiveBlock block) {

    int x = block.x;
    int y = block.y;

    switch(block.orientation) {

        case Up:
            for(int row = 0; row < 3; row++)
                cellInfo[y + row][x] = 1;

            cellInfo[y + 2][x + 1] = 1;
            break;

        case Right:
            for(int col = 0; col < 3; col++)
                cellInfo[y][x + col] = 1;

            cellInfo[y + 1][x] = 1;
            break;

        case Down:
            for(int row = 0; row < 3; row++)
                cellInfo[y + row][x + 1] = 1;

            cellInfo[y][x] = 1;
            break;

        case Left:
            for(int col = 0; col < 3; col++)
                cellInfo[y + 1][x + col] = 1;

            cellInfo[y][x + 2] = 1;
            break;
    }
}
void lockJBlock(ActiveBlock block)
{
    int x = block.x;
    int y = block.y;

    switch(block.orientation)
    {
        case Up:
            for(int row = 0; row < 3; row++){
                cellInfo[y + row][x + 1] = 1;
            }
            cellInfo[y + 2][x] = 1;
            break;

        case Right:
            for(int col = 0; col < 3; col++){
                cellInfo[y + 2][x + col] = 1;
            }
            cellInfo[y + 1][x] = 1;
            break;

        case Down:
            for(int row = 0; row < 3; row++){
                cellInfo[y + row][x] = 1;
            }
            cellInfo[y][x + 1] = 1;
            break;

        case Left:
            for(int col = 0; col < 3; col++){
                cellInfo[y + 1][x + col] = 1;
            }
            cellInfo[y+2][x+2] = 1;
            break;
    }
}
void lockZBlock(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {
        cellInfo[y][x] = 1;
        cellInfo[y][x + 1] = 1;
        cellInfo[y + 1][x + 1] = 1;
        cellInfo[y + 1][x + 2] = 1;
    } else {
        cellInfo[y][x + 2] = 1;
        cellInfo[y + 1][x + 1] = 1;
        cellInfo[y + 1][x + 2] = 1;
        cellInfo[y + 2][x + 1] = 1;
    }
}
void lockSBlock(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {
        cellInfo[y][x + 1] = 1;
        cellInfo[y][x + 2] = 1;
        cellInfo[y + 1][x] = 1;
        cellInfo[y + 1][x + 1] = 1;
    } 
    else {
        cellInfo[y][x] = 1;
        cellInfo[y + 1][x] = 1;
        cellInfo[y + 1][x + 1] = 1;
        cellInfo[y + 2][x + 1] = 1;
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
                GRID_LINE_COLOR
                
            );
        }
    }
}


void spawnBarBlock(ActiveBlock &block){
    block.block=BarBlock;
    block.orientation= Up;
    block.x=3;
    block.y=0;
    block.color=SKYBLUE;
}
void spawnBoxBlock(ActiveBlock &block){
    block.block=BoxBlock;
    block.orientation= Up;
    block.x=4;
    block.y=0;
    block.color=YELLOW;
}
void spawnTBlock(ActiveBlock &block){
    block.block=TBlock;
    block.orientation= Up;
    block.x=3;
    block.y=0;
    block.color=PURPLE;
}
void spawnLBlock(ActiveBlock &block){
 block.block = LBlock;
    block.orientation = Left;
    block.x = 3;            
    block.y = 0;            
    block.color = ORANGE;
}
void spawnJBlock(ActiveBlock &block){
   block.block = JBlock;
    block.orientation = Up;
    block.x = 3;
    block.y = 0;
    block.color = DARKBLUE;
}
void spawnZBlock(ActiveBlock &block) {
    block.block = ZBlock;
    block.orientation = Up;
    block.x = 3;
    block.y = 0;
    block.color = RED;
}
void spawnSBlock(ActiveBlock &block) {
    block.block = SBlock; 
    block.orientation = Up;
    block.x = 4;
    block.y = 0;
    block.color = GREEN; 
}

void spawnRandomBlock(ActiveBlock &block){
    int random = GetRandomValue(0, 6); 
    switch (random)
    {
        case 0:spawnBarBlock(block);
            break;
        case 1:spawnBoxBlock(block);
            break;
        case 2:spawnTBlock(block);
            break;
        case 3:spawnLBlock(block);
            break;
        case 4:spawnJBlock(block);
            break;
        case 5:spawnZBlock(block);
            break;
        case 6:spawnSBlock(block);
            break;
    }
     // If the spot we just spawned in is already occupied, Game Over!
    if (cellInfo[block.y][block.x] == 1) {
        isGameOver = true;}
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
void drawBoxBlock(ActiveBlock block)
{
    int x = block.x;
    int y = block.y;

    for (int row = 0; row < 2; row++)
    {
        for (int col = 0; col < 2; col++)
        {
            DrawRectangle(
                (x + col) * CELL_WIDTH,
                (y + row) * CELL_HEIGHT,
                CELL_WIDTH,
                CELL_HEIGHT,
                block.color
            );
        }
    }
}
void drawTBlock(ActiveBlock block){
    int x =block.x;
    int y=block.y;
    switch(block.orientation){
        case Up:
            DrawRectangle((x + 1) * CELL_WIDTH, (y) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
            for(int col=0;col<3;col++){
                DrawRectangle((x+col) * CELL_WIDTH, (y+1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
        }break;
        case Down:
             DrawRectangle((x + 1) * CELL_WIDTH, (y+1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
             for(int col=0;col<3;col++){
                   DrawRectangle((x+col) * CELL_WIDTH, (y) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
        }break;
        case Right:
            DrawRectangle((x + 1) * CELL_WIDTH, (y+1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
            for(int row=0;row<3;row++){
                   DrawRectangle((x) * CELL_WIDTH, (y+row) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
            }break;
        case Left:
             DrawRectangle((x) * CELL_WIDTH, (y+1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
             for(int row=0;row<3;row++){
                   DrawRectangle((x+1) * CELL_WIDTH, (y+row) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
            }break;
}}
void drawLBlock(ActiveBlock block){
    int x = block.x;
    int y = block.y;

    switch(block.orientation) {
        case Up:

        for(int row=0;row<3;row++){
            DrawRectangle(x * CELL_WIDTH, (y+row) * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT, block.color);
        }
        DrawRectangle((x + 1) * CELL_WIDTH, (y + 2) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color); 
        break;
        case Right:

         for(int col=0;col<3;col++){
            DrawRectangle((x + col) * CELL_WIDTH, y * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT, block.color);
        }
        DrawRectangle(x * CELL_WIDTH,       (y + 1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
        break;
        case Down:

        for(int row=0;row<3;row++){
            DrawRectangle((x + 1) * CELL_WIDTH, (y + row) * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT, block.color);
        }
        DrawRectangle(x * CELL_WIDTH, y * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
        break;
        case Left: 

        for(int col=0;col<3;col++){
            DrawRectangle((x + col) * CELL_WIDTH, (y + 1) * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT, block.color);
        }
        DrawRectangle((x + 2) * CELL_WIDTH, y * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT, block.color);
        break;
    }

}
void drawJBlock(ActiveBlock block)
{
    int x = block.x;
    int y = block.y;

    switch(block.orientation)
    {
        case Up:
            for(int row = 0; row < 3; row++){
                DrawRectangle((x + 1) * CELL_WIDTH,(y + row) * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT,block.color);
            }
            
                DrawRectangle(x * CELL_WIDTH,(y + 2) * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT,block.color);
            break;
        case Right:
            for(int col = 0; col < 3; col++){
                DrawRectangle((x + col) * CELL_WIDTH, (y+2) * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT,block.color);
            }
                DrawRectangle(x * CELL_WIDTH,(y + 1) * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT,block.color);
            break;
        case Down:
            for(int row = 0; row < 3; row++){
                DrawRectangle(x * CELL_WIDTH,(y + row) * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT,block.color);
            }
                DrawRectangle((x + 1) * CELL_WIDTH,y * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT,block.color);
            break;

        case Left:
            for(int col = 0; col < 3; col++){
                DrawRectangle((x + col) * CELL_WIDTH, (y + 1) * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT,block.color);
            }
                DrawRectangle((x+2) * CELL_WIDTH,(y+2) * CELL_HEIGHT,CELL_WIDTH, CELL_HEIGHT,block.color);
            break;
    }
}
void drawZBlock(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {
        DrawRectangle(x * CELL_WIDTH,       y * CELL_HEIGHT,       CELL_WIDTH, CELL_HEIGHT, block.color); 
        DrawRectangle((x + 1) * CELL_WIDTH, y * CELL_HEIGHT,       CELL_WIDTH, CELL_HEIGHT, block.color); 
        DrawRectangle((x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color); 
        DrawRectangle((x + 2) * CELL_WIDTH, (y + 1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color); 
    }
    else {
        DrawRectangle((x + 2) * CELL_WIDTH, y * CELL_HEIGHT,       CELL_WIDTH, CELL_HEIGHT, block.color);
        DrawRectangle((x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color); 
        DrawRectangle((x + 2) * CELL_WIDTH, (y + 1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color); 
        DrawRectangle((x + 1) * CELL_WIDTH, (y + 2) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color); 
    }
}
void drawSBlock(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {
        DrawRectangle((x + 1) * CELL_WIDTH, y * CELL_HEIGHT,       CELL_WIDTH, CELL_HEIGHT, block.color);
        DrawRectangle((x + 2) * CELL_WIDTH, y * CELL_HEIGHT,       CELL_WIDTH, CELL_HEIGHT, block.color);
        DrawRectangle(x * CELL_WIDTH,       (y + 1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
        DrawRectangle((x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
    }
    else {
        DrawRectangle(x * CELL_WIDTH,       y * CELL_HEIGHT,       CELL_WIDTH, CELL_HEIGHT, block.color);
        DrawRectangle(x * CELL_WIDTH,       (y + 1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
        DrawRectangle((x + 1) * CELL_WIDTH, (y + 1) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
        DrawRectangle((x + 1) * CELL_WIDTH, (y + 2) * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, block.color);
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
bool canBoxGoDown(ActiveBlock block)
{
    int x = block.x;
    int y = block.y;

    if (y + 2 >= ROWS) return false;
    for (int col = 0; col < 2; col++)
    {
        if (cellInfo[y + 2][x + col] == 1)
            return false;
    }

    return true;
}
bool canTGoDown(ActiveBlock block){
    int x = block.x;
    int y = block.y;
    switch (block.orientation){
        case Up:
            if(y+2>=ROWS) return false;
            for(int col=0;col<3;col++){
                if(cellInfo[y+2][x+col]==1) return false;
        }
        break;
        case Right:
            if (y + 3 >= ROWS) return false;
            if (cellInfo[y + 2][x + 1] == 1) return false; 
            if (cellInfo[y + 3][x] == 1) return false;     
            
        break;
        case Left:
            if (y + 3 >= ROWS) return false;
            if (cellInfo[y + 2][x] == 1) return false;      
            if (cellInfo[y + 3][x + 1] == 1) return false;  
            break;
        case Down:
            if (y + 2 >= ROWS) return false; 
            if (cellInfo[y + 2][x + 1] == 1) return false; 
            for (int col = 0; col < 3; col++) {
                if (cellInfo[y + 1][x + col] == 1) return false;}
            break; 
            }
        return true;
    }
bool canLGoDown(ActiveBlock block){
    int x = block.x;
    int y = block.y;

    switch (block.orientation) {
        case Up:
            if (y + 3 >= ROWS) return false;
            if (cellInfo[y + 3][x] == 1) return false;
            if (cellInfo[y + 3][x + 1] == 1) return false;
            break;
        case Right:
            if (y + 2 >= ROWS) return false;
            if (cellInfo[y + 2][x] == 1) return false;     
            if (cellInfo[y + 1][x + 1] == 1) return false; 
            if (cellInfo[y + 1][x + 2] == 1) return false; 
            break;

        case Down:
            if (y + 3 >= ROWS) return false;
            if (cellInfo[y + 1][x] == 1) return false;     
            if (cellInfo[y + 3][x + 1] == 1) return false;
            break;

        case Left:
            if (y + 2 >= ROWS) return false;
            if (cellInfo[y + 2][x] == 1) return false;
            if (cellInfo[y + 2][x + 1] == 1) return false;
            if (cellInfo[y + 2][x + 2] == 1) return false;
            break;
    }
return true;
    }
bool canJGoDown(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    switch(block.orientation) {
        case Up:
            if (y + 3 >= ROWS) return false; 
            if (cellInfo[y + 3][x] == 1) return false;
            if (cellInfo[y + 3][x+1] == 1) return false;
            break;

        case Right:
            if (y + 3 >= ROWS) return false;
            for (int col = 0; col < 3; col++)
                if (cellInfo[y + 3][x + col] == 1) return false;
            break;

        case Down:
            if (y + 3 >= ROWS) return false;
            if (cellInfo[y + 3][x] == 1) return false;
             if (cellInfo[y + 1][x+1] == 1) return false;
            break;

        case Left:
            if (y + 3 >= ROWS) return false;
            if (cellInfo[y + 2][x] == 1) return false;
            if (cellInfo[y + 2][x+1] == 1) return false;
            if (cellInfo[y + 3][x+2] == 1) return false;
            break;
    }

    return true;
}
bool canZGoDown(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {
        if (y + 2 >= ROWS) return false;
        if (cellInfo[y + 1][x] == 1) return false;     
        if (cellInfo[y + 2][x + 1] == 1) return false; 
        if (cellInfo[y + 2][x + 2] == 1) return false; 
    }
    else {
        if (y + 3 >= ROWS) return false;
        if (cellInfo[y + 2][x + 2] == 1) return false;
        if (cellInfo[y + 3][x + 1] == 1) return false; 
    }
    return true;
}
bool canSGoDown(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {
        if (y + 2 >= ROWS) return false; 
        
        if (cellInfo[y + 2][x] == 1) return false;     
        if (cellInfo[y + 2][x + 1] == 1) return false; 
        if (cellInfo[y + 1][x + 2] == 1) return false; 
    } 
    else {
        if (y + 3 >= ROWS) return false;

        if (cellInfo[y + 2][x] == 1) return false;     
        if (cellInfo[y + 3][x + 1] == 1) return false; 
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
bool canBoxGoLeft(ActiveBlock block)
{
    int x = block.x;
    int y = block.y;
    if (x - 1 < 0) return false;
    for (int row = 0; row < 2; row++)
    {
        if (cellInfo[y + row][x - 1] == 1)
            return false;
    }

    return true;
}
bool canTGoLeft(ActiveBlock block){
    int x = block.x;
    int y = block.y;

    switch(block.orientation) {
        case Up:
            if (x - 1 < 0) return false;
            if (cellInfo[y + 1][x - 1] == 1) return false;
            if (cellInfo[y][x] == 1) return false;
            break;
        case Down:
            if (x - 1 < 0) return false;
            if (cellInfo[y][x - 1] == 1) return false;
            if (cellInfo[y + 1][x] == 1) return false;
            break;
        case Right:
            if (x - 1 < 0) return false;
            for (int row = 0; row < 3; row++)
                if (cellInfo[y + row][x - 1] == 1) return false;
            break;
        case Left:
            if (x - 1 < 0) return false;
            if (cellInfo[y][x] == 1) return false;
            if (cellInfo[y + 1][x - 1] == 1) return false;
            if (cellInfo[y + 2][x] == 1) return false;
            break;
    }

    return true; 
}
bool canLGoLeft(ActiveBlock block){
    int x = block.x;
    int y = block.y;

    if (x - 1 < 0) return false; 

    switch (block.orientation) {
        case Up:
            if (cellInfo[y][x - 1] == 1) return false;
            if (cellInfo[y + 1][x - 1] == 1) return false;
            if (cellInfo[y + 2][x - 1] == 1) return false;
            break;

        case Right:
            if (cellInfo[y][x - 1] == 1) return false;
            if (cellInfo[y + 1][x - 1] == 1) return false;
            break;

        case Down:
            if (cellInfo[y][x - 1] == 1) return false;     
            if (cellInfo[y + 1][x] == 1) return false;     
            if (cellInfo[y + 2][x] == 1) return false;     
            break;

        case Left:
            if (cellInfo[y][x + 1] == 1) return false;     
            if (cellInfo[y + 1][x - 1] == 1) return false; 
            break;
    }
    return true;
}
bool canJGoLeft(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    switch(block.orientation) {
        case Up:
            if (x - 1 < 0) return false;
            for (int row = 0; row < 3; row++)
                if (cellInfo[y + row][x] == 1) return false;
            if (cellInfo[y + 2][x - 1] == 1) return false;
            break;

        case Right:
            if (x - 1 < 0) return false;
            if (cellInfo[y + 1][x - 1] == 1) return false;
            break;

        case Down:
            if (x - 1 < 0) return false;
            for (int row = 0; row < 3; row++)
                if (cellInfo[y + row][x - 1] == 1) return false;
            break;

        case Left:
            if (x - 1 < 0) return false;
            for (int col = 0; col < 3; col++)
                if (cellInfo[y + 1][x + col - 1] == 1) return false;
            if (cellInfo[y][x - 1] == 1) return false;
            break;
    }

    return true;
}
bool canZGoLeft(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {
        
        if (x - 1 < 0) return false;                   
        if (x < 0) return false;                       
        if (cellInfo[y][x - 1] == 1) return false;     
        if (cellInfo[y + 1][x] == 1) return false;     
    } 
    else {
        if (x + 1 < 0) return false;                   
        if (x < 0) return false;                       
        if (cellInfo[y][x + 1] == 1) return false;     
        if (cellInfo[y + 1][x] == 1) return false;   
    }
    return true;
}
bool canSGoLeft(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {
        
        if (x < 0) return false; 
        if (x - 1 < 0) return false; 
        if (cellInfo[y][x] == 1) return false;        
        if (cellInfo[y + 1][x - 1] == 1) return false; 
    } 
    else {
      
        if (x - 1 < 0) return false; 
        if (x < 0) return false;     

        if (cellInfo[y][x - 1] == 1) return false;     
        if (cellInfo[y + 1][x - 1] == 1) return false; 
        if (cellInfo[y + 2][x] == 1) return false;    
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
bool canBoxGoRight(ActiveBlock block)
{
    int x = block.x;
    int y = block.y;
    if (x + 2 >= COLS) return false;
    for (int row = 0; row < 2; row++)
    {
        if (cellInfo[y + row][x + 2] == 1)
            return false;
    }

    return true;
}
bool canTGoRight(ActiveBlock block){
    int x = block.x;
    int y = block.y;

    switch(block.orientation) {
        case Up:
            if (x + 3 >= COLS) return false;
            if (cellInfo[y + 1][x + 3] == 1) return false; 
            if (cellInfo[y][x + 2] == 1) return false;     
            break;
        case Down:
            if (x + 3 >= COLS) return false;
            if (cellInfo[y][x + 3] == 1) return false;     
            if (cellInfo[y + 1][x + 2] == 1) return false; 
            break;
        case Right:
        if (x + 2 >= COLS) return false; 
        if (cellInfo[y][x+1] == 1) return false;       
        if (cellInfo[y+1][x+2] == 1) return false;     
        if (cellInfo[y+2][x+1] == 1) return false;    
            break;
        case Left:
        if (x + 2 >= COLS) return false;
        if (cellInfo[y][x+2] == 1) return false;   
        if (cellInfo[y+1][x+2] == 1) return false;
        if (cellInfo[y+2][x+2] == 1) return false;
             break;
        }

    return true; 
}
bool canLGoRight(ActiveBlock block){
    int x = block.x;
    int y = block.y;

    switch (block.orientation) {
        case Up:
            if (x + 2 >= COLS) return false; 
            if (cellInfo[y][x + 1] == 1) return false;
            if (cellInfo[y + 1][x + 1] == 1) return false;
            if (cellInfo[y + 2][x + 2] == 1) return false; 
            break;

        case Right:
            if (x + 3 >= COLS) return false;
            if (cellInfo[y][x + 3] == 1) return false;
            if (cellInfo[y + 1][x + 1] == 1) return false;
            break;

        case Down:
            if (x + 2 >= COLS) return false;
            if (cellInfo[y][x + 2] == 1) return false;
            if (cellInfo[y + 1][x + 2] == 1) return false;
            if (cellInfo[y + 2][x + 2] == 1) return false;
            break;

        case Left:
            if (x + 3 >= COLS) return false;
            if (cellInfo[y][x + 3] == 1) return false;
            if (cellInfo[y + 1][x + 3] == 1) return false;
            break;
    }
    return true;
}
bool canJGoRight(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    switch(block.orientation) {
        case Up:
            if (x + 2 >= COLS) return false; 
            for (int row = 0; row < 3; row++)
                if (cellInfo[y + row][x + 2] == 1) return false;
            if (cellInfo[y + 2][x + 1] == 1) return false;
            break;

        case Right:
            if (x + 3 >= COLS) return false;
            for (int col = 0; col < 3; col++)
                if (cellInfo[y + 2][x + col] == 1) return false;
            if (cellInfo[y + 1][x + 2] == 1) return false;
            break;

        case Down:
            if (x + 2 >= COLS) return false;
            for (int row = 0; row < 3; row++)
                if (cellInfo[y + row][x + 1] == 1) return false;
            if (cellInfo[y][x + 1] == 1) return false;
            break;

        case Left:
            if (x + 3 >= COLS) return false;
            if (cellInfo[y + 1][x  + 1] == 1) return false;
            if (cellInfo[y+3][x + 3] == 1) return false;
            break;
    }

    return true;
}
bool canZGoRight(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {
        if (x + 2 >= COLS) return false;        
        if (x + 3 >= COLS) return false;        
        if (cellInfo[y][x + 2] == 1) return false;     
        if (cellInfo[y + 1][x + 3] == 1) return false; 
    } 
    else {
        if (x + 3 >= COLS) return false;        
        if (x + 2 >= COLS) return false;        
        if (cellInfo[y][x + 3] == 1) return false;    
        if (cellInfo[y + 1][x + 3] == 1) return false; 
        if (cellInfo[y + 2][x + 2] == 1) return false;
    }
    return true;
}
bool canSGoRight(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {
        if (x + 3 >= COLS) return false;
        if (x + 2 >= COLS) return false;
        if (cellInfo[y][x + 3] == 1) return false;  
        if (cellInfo[y + 1][x + 2] == 1) return false;
    } 
    else {
        if (x + 1 >= COLS) return false; 
        if (x + 2 >= COLS) return false;
        if (cellInfo[y][x + 1] == 1) return false;    
        if (cellInfo[y + 1][x + 2] == 1) return false; 
        if (cellInfo[y + 2][x + 2] == 1) return false; 
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
bool canBoxRotate(ActiveBlock block)
{
    return true;
}
bool canTRotate(ActiveBlock block) {
    int x = block.x;
    int y = block.y;
    switch(block.orientation){
         case Up:
            if (x < 0 || x + 1 >= COLS) return false;
            if (y + 2 >= ROWS) return false;
            if (cellInfo[y][x] || cellInfo[y+1][x] || cellInfo[y+1][x+1] || cellInfo[y+2][x]) return false;
            break;
        case Right:
            if (x < 0 || x + 2 >= COLS) return false;
            if (y + 2 >= ROWS) return false;
            if (cellInfo[y+1][x] || cellInfo[y+1][x+1] || cellInfo[y+1][x+2] || cellInfo[y+2][x+1]) return false;
            break;
        case Down:
            if (x < 0 || x + 1 >= COLS) return false;
            if (y + 2 >= ROWS) return false;
            if (cellInfo[y][x+1] || cellInfo[y+1][x] || cellInfo[y+1][x+1] || cellInfo[y+2][x+1]) return false;
            break;
        case Left:
            if (x < 0 || x + 2 >= COLS) return false;
            if (y + 1 >= ROWS) return false;
            if (cellInfo[y][x+1] || cellInfo[y+1][x] || cellInfo[y+1][x+1] || cellInfo[y+1][x+2]) return false;
            break; 
    }

    return true;
}
bool canLRotate(ActiveBlock block){
    int x = block.x;
    int y = block.y;
    switch (block.orientation) {
        case Left:
            if (y + 2 >= ROWS || x + 1 >= COLS) return false;
            if (cellInfo[y][x] == 1) return false;
            if (cellInfo[y + 1][x] == 1) return false;
            if (cellInfo[y + 2][x] == 1) return false;
            if (cellInfo[y + 2][x + 1] == 1) return false;
            break;

        case Up:
            if (y + 1 >= ROWS || x + 2 >= COLS) return false;
            if (cellInfo[y][x] == 1) return false;
            if (cellInfo[y][x + 1] == 1) return false;
            if (cellInfo[y][x + 2] == 1) return false;
            if (cellInfo[y + 1][x] == 1) return false;
            break;

        case Right:
            if (y + 2 >= ROWS || x + 1 >= COLS) return false;
            if (cellInfo[y][x] == 1) return false;
            if (cellInfo[y][x + 1] == 1) return false;
            if (cellInfo[y + 1][x + 1] == 1) return false;
            if (cellInfo[y + 2][x + 1] == 1) return false;
            break;

        case Down:
           
            if (y + 1 >= ROWS || x + 2 >= COLS) return false;
            if (cellInfo[y + 1][x] == 1) return false;
            if (cellInfo[y + 1][x + 1] == 1) return false;
            if (cellInfo[y + 1][x + 2] == 1) return false;
            if (cellInfo[y][x + 2] == 1) return false;
            break;
    }

    return true;
}
bool canJRotate(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    switch(block.orientation) {
        case Up:
            if (x + 2 >= COLS || y + 1 >= ROWS) return false;
            if (cellInfo[y + 2][x] == 1 || cellInfo[y + 2][x + 1] == 1 || cellInfo[y + 2][x + 2] == 1) return false;
            if (cellInfo[y + 1][x] == 1) return false;
            break;

        case Right:
            if (x + 1 >= COLS || y + 2 >= ROWS) return false;
            if (cellInfo[y][x + 1] == 1 || cellInfo[y + 1][x + 1] == 1 || cellInfo[y + 2][x + 1] == 1) return false;
            if (cellInfo[y][x] == 1) return false;
            break;

        case Down: 
            if (x + 2 >= COLS || y + 1 >= ROWS) return false;
            if (cellInfo[y][x] == 1 || cellInfo[y][x + 1] == 1 || cellInfo[y][x + 2] == 1) return false;
            if (cellInfo[y + 1][x + 2] == 1) return false;
            break;

        case Left: 
            if (x + 1 >= COLS || y + 2 >= ROWS) return false;
            if (cellInfo[y][x+1] == 1 || cellInfo[y + 1][x+1] == 1 || cellInfo[y + 2][x+1] == 1) return false;
            if (cellInfo[y + 2][x] == 1) return false;
            break;
    }

    return true;
}
bool canZRotate(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {

        if (x + 2 >= COLS || y + 2 >= ROWS) return false;
        if (cellInfo[y][x + 2] == 1) return false;
        if (cellInfo[y + 1][x + 1] == 1) return false;
        if (cellInfo[y + 1][x + 2] == 1) return false;
        if (cellInfo[y + 2][x + 1] == 1) return false;
    }
    else {
        if (x + 2 >= COLS || y + 1 >= ROWS) return false;
        if (cellInfo[y][x] == 1) return false;
        if (cellInfo[y][x + 1] == 1) return false;
        if (cellInfo[y + 1][x + 1] == 1) return false;
        if (cellInfo[y + 1][x + 2] == 1) return false;
    }
    return true;
}
bool canSRotate(ActiveBlock block) {
    int x = block.x;
    int y = block.y;

    if (block.orientation == Up || block.orientation == Down) {

        if (y + 2 >= ROWS) return false; 
        if (x + 1 >= COLS) return false; 

        if (cellInfo[y][x] == 1) return false;
        if (cellInfo[y + 1][x] == 1) return false;
        if (cellInfo[y + 1][x + 1] == 1) return false;
        if (cellInfo[y + 2][x + 1] == 1) return false;
    } 
    else {
        if (y + 1 >= ROWS) return false; 
        if (x + 2 >= COLS) return false; 

        if (cellInfo[y][x + 1] == 1) return false;
        if (cellInfo[y][x + 2] == 1) return false;
        if (cellInfo[y + 1][x] == 1) return false;
        if (cellInfo[y + 1][x + 1] == 1) return false;
    }
    return true;
}
void checkAndClearRows() {
    for (int y = ROWS - 1; y >= 0; y--) {
        bool isFull = true;
        for (int x = 0; x < COLS; x++) {
            if (cellInfo[y][x] == 0) {
                isFull = false;
                break;
            }
        }

        if (isFull) {
            // Shift all rows above this one down
            for (int ty = y; ty > 0; ty--) {
                for (int tx = 0; tx < COLS; tx++) {
                    cellInfo[ty][tx] = cellInfo[ty - 1][tx];
                }
            }
            // Clear the very top row
            for (int tx = 0; tx < COLS; tx++) cellInfo[0][tx] = 0;
            
            score += 100; // Increase score
            y++; // Check the same row index again because a new row shifted down
        }
    }
}
void resetGame(ActiveBlock &block) {
    // Clear the board
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) cellInfo[y][x] = 0;
    }
    score = 0;
    isGameOver = false;
    spawnRandomBlock(block);
}

void playGame(ActiveBlock &block, float &fallTime, float fallDelay){
    
    if (isGameOver) {
        int centerY = BOARD_HEIGHT / 2;
        int lineSpace = 50; // space between lines
        DrawText("GAME OVER",50, centerY - lineSpace, 40, RED);
        DrawText(TextFormat("Your score: %i", score),80, centerY, 30, YELLOW);
        DrawText("Press ENTER to Restart",40, centerY + lineSpace, 20, WHITE);
        
        if (IsKeyPressed(KEY_ENTER)) {
            resetGame(block);
        }
        return; // Stop running the rest of the logic
    }

    if (IsKeyPressed(KEY_LEFT)){
    bool canMove = false;

    switch (block.block){
        case BarBlock:
            canMove = canBarGoLeft(block);
            break;
        case BoxBlock:
            canMove = canBoxGoLeft(block);
            break;
        case TBlock:
            canMove= canTGoLeft(block);
            break;
        case LBlock:
            canMove= canLGoLeft(block);
            break;
        case JBlock:
            canMove= canJGoLeft(block);
            break;
        case ZBlock:
            canMove= canZGoLeft(block);
            break;
        case SBlock:
            canMove= canSGoLeft(block);
            break;
        default:break;
    }
    if (canMove)
        block.x--;
}
if (IsKeyPressed(KEY_RIGHT)){
    bool canMove = false;

    switch (block.block){
        case BarBlock:
            canMove = canBarGoRight(block);
            break;
        case BoxBlock:
            canMove = canBoxGoRight(block);
            break;
        case TBlock:
             canMove= canTGoRight(block);
            break;
        case LBlock:
             canMove= canLGoRight(block);
            break;
        case JBlock:
             canMove= canJGoRight(block);
            break;
        case ZBlock:
             canMove= canZGoRight(block);
            break;
        case SBlock:
             canMove= canSGoRight(block);
            break;
        default:break;
    }
    if (canMove)
        block.x++;
}


 if (IsKeyPressed(KEY_UP))
{
    bool canRotate = false;
    switch (block.block)
    {
        case BarBlock:
            canRotate = canBarRotate(block);
            break;
        case BoxBlock:
            canRotate = canBoxRotate(block);
            break;
        case TBlock:
             canRotate= canTRotate(block);
            break;
        case LBlock:
             canRotate= canLRotate(block);
            break;
        case JBlock:
             canRotate= canJRotate(block);
            break;
         case ZBlock:
             canRotate= canZRotate(block);
            break;
          case SBlock:
             canRotate= canSRotate(block);
            break;
    }

    if (canRotate)
    {
        
        switch (block.orientation)
        {
            case Up: block.orientation = Right; break;
            case Right: block.orientation = Down; break;
            case Down: block.orientation = Left; break;
            case Left: block.orientation = Up; break;
        }
    }
}
    
    fallTime += GetFrameTime();
    if (fallTime >= fallDelay){
        bool canMoveDown = false;

switch (block.block){
    case BarBlock:
        canMoveDown = canBarGoDown(block);
        break;
    case BoxBlock:
        canMoveDown = canBoxGoDown(block);
        break;
    case TBlock:
        canMoveDown= canTGoDown(block);
        break;
    case LBlock:
        canMoveDown= canLGoDown(block);
        break;
    case JBlock:
        canMoveDown= canJGoDown(block);
        break;
    case ZBlock:
        canMoveDown= canZGoDown(block);
        break;
     case SBlock:
        canMoveDown= canSGoDown(block);
        break;
}

if (canMoveDown)
{
    block.y++;
    
}
else
{
    switch (block.block){
        case BarBlock: lockBarBlock(block); break;
        case BoxBlock: lockBoxBlock(block); break;
        case TBlock: lockTBlock(block);break;
        case LBlock: lockLBlock(block);break;
        case JBlock: lockJBlock(block);break;
        case ZBlock: lockZBlock(block);break;
        case SBlock: lockSBlock(block);break;
        default:break;
    }
    checkAndClearRows();
    spawnRandomBlock(block); 
    
} 
    fallTime = 0.0f;         
    }
    
    switch (block.block){
    case BarBlock:drawBarBlock(block);break;
    case BoxBlock:drawBoxBlock(block);break;
    case TBlock:drawTBlock(block);break;
    case LBlock:drawLBlock(block);break;
    case JBlock:drawJBlock(block);break;
    case ZBlock:drawZBlock(block);break;
    case SBlock:drawSBlock(block);break;
    default:break;
}
        drawLockedCells();
        drawGrid();
        // Draw Score in the Info Area
        DrawText("SCORE:", BOARD_WIDTH + 20, 50, 20, WHITE);
        DrawText(TextFormat("%i", score), BOARD_WIDTH + 20, 80, 30, YELLOW);
}