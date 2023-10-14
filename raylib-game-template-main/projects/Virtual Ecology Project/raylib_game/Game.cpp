#include "Header.h"
#include "Agent.cpp"
#include "Food.cpp"
#include "ChaserAgent.cpp"
#include "WanderingAgent.cpp"





using namespace std;

#define CHASER_STARTING_POP 5
#define WANDERING_STARTING_POP 5
#define FOOD_PER_ROUND 50


const int xDim = 1600, yDim = 900;
vector<Agent> agents;
vector<Food> food;


int main(void)
{

    InitWindow(xDim, yDim, "Virtual Ecology");
    SetTargetFPS(60);

    generateFood();


    for (int i = 0; i < CHASER_STARTING_POP; i++)
        agents.push_back(ChaserAgent{ Vector2{(float)GetRandomValue(0, xDim), (float)GetRandomValue(0, yDim)} });
    for (int i = 0; i < WANDERING_STARTING_POP; i++)
        agents.push_back(WanderingAgent{ Vector2{(float)GetRandomValue(0, xDim), (float)GetRandomValue(0, yDim)} });



    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        /*
            generate food
            generate wanderers+chasers
            wait
            kill last/buff others

            respawn all
        */











        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void generateFood() {
    for (int i = 0; i < FOOD_PER_ROUND; i++)
        food.push_back(Food{ Vector2{(float)GetRandomValue(0, xDim), (float)GetRandomValue(0, yDim)} });
}

void drawFood() {
    for (Food f : food)
        DrawCircle(f.location.x, f.location.y, f.radius, RED);
}

void evolve() {

}

void drawAgents() {
    for (Agent agent : agents)
        agent.draw();
}

