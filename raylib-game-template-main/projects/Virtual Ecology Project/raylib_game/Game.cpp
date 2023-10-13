#include "Header.h"
#include <vector> 
#include "Agent.cpp"
#include "Food.cpp"
#include "ChaserAgent.cpp"


using namespace std;

#define CHASER_STARTING_POP 5
#define WANDERER_STARTING_POP 5



int main(void)
{

    const int xDim = 1600, yDim = 900;
    const float dotRadius = 5.0f;
    InitWindow(xDim, yDim, "Virtual Ecology");
    SetTargetFPS(60);

    vector<Agent> agents;
    for (int i = 0; i < CHASER_STARTING_POP; i++) {
        //agents.push_back(ChaserAgent{ {0, 0}, {0, 0}, {0, 0}, {0, 0}, 0, 0, 0, 0, 0, 0 });
    }
    





    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        





        EndDrawing();
    }

    CloseWindow();

    return 0;
}