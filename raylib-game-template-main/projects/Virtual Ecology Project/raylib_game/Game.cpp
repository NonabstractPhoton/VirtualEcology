#include "Header.h"
#include "Agent.cpp"
#include "Food.cpp"
#include "ChaserAgent.cpp"
#include "WanderingAgent.cpp"





using namespace std;
using namespace chrono;

#define CHASER_STARTING_POP 10
#define WANDERING_STARTING_POP 10
#define FOOD_PER_ROUND 500


const int evolutionScreenTime = 5, simRunTime = 5;
auto simStartTime = high_resolution_clock::now();
bool simulating = true;

vector<Agent*> agents;

vector<Food> food;

bool comparePtrToNode(Agent* a, Agent* b);



int main(void)
{

    InitWindow(XDIM, YDIM, "Virtual Ecology");
    SetTargetFPS(60);

    generateFood();




    agents.reserve(10);
    for (int i = 0; i < CHASER_STARTING_POP; i++) {
        agents.push_back(new chaseI);
    }
    for (int i = 0; i < WANDERING_STARTING_POP; i++) {
        agents.push_back(new wanderI);
    }



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
            updateAllAgents();
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
        food.push_back(Food{ Vector2{(float)GetRandomValue(0, XDIM), (float)GetRandomValue(0, YDIM)} });
}

void drawFood() {
    for (Food f : food)
        DrawCircle(f.location.x, f.location.y, 5, BLACK);
}

void evolve() {

    sort(agents.begin(), agents.end(), comparePtrToNode);
    
    agents.erase(agents.begin());   //removes the guy who eaten the least
}

void drawAgents() {
    for (Agent* ptr : agents) {
        if (ChaserAgent* j = dynamic_cast<ChaserAgent*>(ptr)) {
            j->draw();
        }
        else if (WanderingAgent* k = dynamic_cast<WanderingAgent*>(ptr)) {
            k->draw();
        }
    }
}

void drawSplash() {
    //draw ranking, who died, who mutated etc.
}

void updateAllAgents() {
    for (Agent* ptr : agents) {
        if (ChaserAgent* j = dynamic_cast<ChaserAgent*>(ptr))
            j->update(&food);
        else if (WanderingAgent* k = dynamic_cast<WanderingAgent*>(ptr))
            k->update(&food);
    }

}

bool comparePtrToNode(Agent* a, Agent* b) {
    //cout << a->foodEaten << "\t" << b->foodEaten << "\n";
    return (*a < *b); }
