#include "Header.h"
#include "Agent.cpp"
#include "Food.cpp"
#include "ChaserAgent.cpp"
#include "WanderingAgent.cpp"





using namespace std;
using namespace chrono;

#define CHASER_STARTING_POP 5
#define WANDERING_STARTING_POP 5
#define FOOD_PER_ROUND 50


const int xDim = 1600, yDim = 900, evolutionScreenTime = 5, simRunTime = 20;
auto simStartTime = high_resolution_clock::now();
bool simulating;

vector<Agent> agents;
vector<Food> food;


int main(void)
{

    InitWindow(xDim, yDim, "Virtual Ecology");
    SetTargetFPS(60);

    generateFood();


    for (int i = 1; i <= CHASER_STARTING_POP; i++)
        agents.push_back(ChaserAgent{ Vector2{(float)GetRandomValue(0, xDim), (float)GetRandomValue(0, yDim)} });
    for (int i = 1; i <= WANDERING_STARTING_POP; i++)
        agents.push_back(WanderingAgent{ Vector2{(float)GetRandomValue(0, xDim), (float)GetRandomValue(0, yDim)} });



    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        int currentRunTime = duration_cast<seconds>(high_resolution_clock::now() - simStartTime).count();

        if (currentRunTime > simRunTime + evolutionScreenTime) {     //start new sim
            simStartTime = high_resolution_clock::now();
            generateFood();
            simulating = true;
        }
        else if (currentRunTime > simRunTime) {    //draw spash screen showing the stat changes/killing/mutations
            if (simulating) {
                simulating = false;
                evolve();
            }
            drawSplash();
        }
        else {      //simulating
            drawFood();
            drawAgents();
        }



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
        DrawCircle(f.location.x, f.location.y, f.radius, BLACK);
}

void evolve() {
    int f;
}

void drawAgents() {
    for (Agent agent : agents)  
        agent.draw();
}

void drawSplash() {
    //draw ranking, who died, who mutated etc.
}

