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



int cellInfo[ROWS][COLS] = {0};

void drawGrid();
void drawLockedCells();

void spawnBarBlock(ActiveBlock &block);
void spawnBoxBlock(ActiveBlock &block);
void spawnTBlock(ActiveBlock &block);
void spawnLBlock(ActiveBlock &block);
void spawnRandomBlock(ActiveBlock &block);

void drawBarBlock(ActiveBlock block);
void drawBoxBlock(ActiveBlock block);
void drawTBlock(ActiveBlock block);
void drawLBlock(ActiveBlock block);

bool canBarGoDown(ActiveBlock block);
bool canBoxGoDown(ActiveBlock block);
bool canTGoDown(ActiveBlock block);
bool canLGoDown(ActiveBlock block);

bool canBarGoLeft(ActiveBlock block);
bool canBoxGoLeft(ActiveBlock block);
bool canTGoLeft(ActiveBlock block);
bool canLGoLeft(ActiveBlock block);

bool canBarGoRight(ActiveBlock block);
bool canBoxGoRight(ActiveBlock block);
bool canTGoRight(ActiveBlock block);
bool canLGoRight(ActiveBlock block);

bool canBarRotate(ActiveBlock block);
bool canBoxRotate(ActiveBlock block);
bool canTRotate(ActiveBlock block);
bool canLRotate(ActiveBlock block);

void lockBarBlock(ActiveBlock block);
void lockBoxBlock(ActiveBlock block);
void lockTBlock(ActiveBlock block);
void lockLBlock(ActiveBlock block);

void playGame(ActiveBlock &block, float &fallTime, float fallDelay);



int main()
{
    InitWindow(BOARD_WIDTH +INFO_AREA , BOARD_HEIGHT, "Tetris");
    SetTargetFPS(60);

    
    ActiveBlock block;
    spawnRandomBlock(block);

    float fallTime = 0.0f;           
    const float FALL_DELAY = 0.2f;

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
    block.orientation= static_cast<Orientation> (GetRandomValue(0,3));
    block.x=3;
    block.y=0;
    block.color=SKYBLUE;
}
void spawnBoxBlock(ActiveBlock &block){
    block.block=BoxBlock;
    block.orientation= Up;
    block.x=4;
    block.y=0;
    block.color=RED;
}
void spawnTBlock(ActiveBlock &block){
    block.block=TBlock;
    block.orientation= static_cast<Orientation> (GetRandomValue(0,3));
    block.x=4;
    block.y=0;
    block.color=GREEN;
}

void spawnRandomBlock(ActiveBlock &block){
    int random = GetRandomValue(0, 2); 
    switch (random)
    {
        case 0:spawnBarBlock(block);
            break;
        case 1:spawnBoxBlock(block);
            break;
        case 2:spawnTBlock(block);
            break;
    }
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
void playGame(ActiveBlock &block, float &fallTime, float fallDelay){
    
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
        default:break;
        //other blocks later
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
    default:break;
    //other blocks later
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
        default:break;
    }
    spawnRandomBlock(block); 
    
} 
    fallTime = 0.0f;         
    }
    
    switch (block.block){
    case BarBlock:drawBarBlock(block);break;
    case BoxBlock:drawBoxBlock(block);break;
    case TBlock:drawTBlock(block);break;
    default:break;
}
        drawLockedCells();
        drawGrid();
}