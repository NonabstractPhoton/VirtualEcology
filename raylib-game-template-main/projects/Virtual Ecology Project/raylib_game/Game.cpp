#include "Header.h"

using namespace std;

int main(void)
{
    const int xDim = 1600, yDim = 900;
    const float dotRadius = 5.0f;
    InitWindow(xDim, yDim, "Virtual Ecology");
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