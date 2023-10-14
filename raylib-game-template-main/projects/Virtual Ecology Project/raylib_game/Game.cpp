#include "Header.h"
#include <vector> 
#include "Agent.cpp"
#include "Food.cpp"
#include "ChaserAgent.cpp"
#include "WanderingAgent.cpp"



using namespace std;

#define CHASER_STARTING_POP 5
#define WANDERING_STARTING_POP 5
#define FOOD_PER_ROUND 50




int main(void)
{

    const int xDim = 1600, yDim = 900;
    const float dotRadius = 5.0f;
    InitWindow(xDim, yDim, "Virtual Ecology");
    SetTargetFPS(60);

    vector<Agent> agents;
    vector<Food> food;

    
    for (int i = 0; i < CHASER_STARTING_POP; i++)
        agents.push_back(ChaserAgent{ Vector2{(float)GetRandomValue(0, xDim), (float)GetRandomValue(0, yDim)} });
    for (int i = 0; i < WANDERING_STARTING_POP; i++)
        agents.push_back(WanderingAgent{ Vector2{(float)GetRandomValue(0, xDim), (float)GetRandomValue(0, yDim)} });

    for (int i = 0; i < FOOD_PER_ROUND; i++) 
        food.push_back(Food{ Vector2{(float)GetRandomValue(0, xDim), (float)GetRandomValue(0, yDim)} });
    

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        for (Agent agent : agents)
            agent.draw();
        for (Food f : food)
            DrawCircle(f.location.x, f.location.y, f.radius, RED);
        





        EndDrawing();
    }

    CloseWindow();

    return 0;
}