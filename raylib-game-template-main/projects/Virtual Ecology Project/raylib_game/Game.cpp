#include "Header.h"

int main(void)
{
    const int xDim = 1920, yDim = 1080;
    InitWindow(xDim, yDim, "raylib [core] example - basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}