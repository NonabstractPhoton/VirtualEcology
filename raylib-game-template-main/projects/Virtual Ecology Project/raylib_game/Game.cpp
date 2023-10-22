#include "Header.h"
#include "ChaserAgent.cpp"
#include "WanderingAgent.cpp"
#include "MutantAgent.cpp"
#include <string>
#include <sstream>


const float xOffset = XDIM / (float)20, yOffset = YDIM / (float)20;
auto simStartTime = high_resolution_clock::now();
bool simulating = true, mutating = true;

vector<Vector2> circlePos;
vector<float> circleRadii;
vector<float> foodEatenPerAgent;

vector<Vector2> startPos, endPos;

vector<Agent*> agents;
Agent deleted = { {0,0},0,0,0,0,0,0 };

vector<Food> food;

bool comparePtrToNode(Agent* a, Agent* b);  //can't include in header cus redefinition error
void drawCircles();




int main(void)
{

    InitWindow(XDIM, YDIM, "Virtual Ecology");
    SetTargetFPS(60);

    generateFood();




    agents.reserve(CHASER_STARTING_POP + WANDERING_STARTING_POP);
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

        if (currentRunTime > SIM_RUN_TIME + MUTATION_SCREEN_TIME + SPLASH_SCREEN_TIME) //start new sim
        {
            simStartTime = high_resolution_clock::now();
            delete agents[0];
            agents.erase(agents.begin());
            generateFood();
            simulating = true;
            foodEatenPerAgent.clear();
            circlePos.clear();
            circleRadii.clear();
            startPos.clear();
            endPos.clear();
            if ((int)agents.size() == 1)
            {
                CloseWindow();
                break;
            }
        }
        else if (currentRunTime > SIM_RUN_TIME + MUTATION_SCREEN_TIME) // show splash screen
        {
            if (mutating) {
                mutating = false;
                evolve();
            }
            drawSplash();
        }
        else if (currentRunTime > SIM_RUN_TIME) {    // show mutations
            if (simulating) {
                simulating = false;
                mutating = true;
                reproduce();
            }
            drawAgents();
            drawFood();
            drawCircles();
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
    food.erase(food.begin(), food.end());
    for (int i = 0; i < FOOD_PER_ROUND; i++)
        food.push_back(Food{ Vector2{(float)GetRandomValue(0, XDIM), (float)GetRandomValue(0, YDIM)} });
}

void drawFood() {
    for (Food f : food)
        DrawCircle(f.location.x, f.location.y, 5, BLACK);
}

void strengthen(size_t index)
{
    if (ChaserAgent* ca = dynamic_cast<ChaserAgent*>(agents[index]))
        ca->detectRange *= 1.25;
    else if (WanderingAgent* wa = dynamic_cast<WanderingAgent*>(agents[index]))
        wa->foodRange *= 1.5;
    else if (MutantAgent* ma = dynamic_cast<MutantAgent*>(agents[index]))
        ma->rechargeTime /= 2;
}

void evolve() 
{

    // Sorts based on score
    sort(agents.begin(), agents.end(), comparePtrToNode);

    // Strengthens the top 2 scorers
    strengthen(agents.size() - 1);
    strengthen(agents.size() - 2);

    // Resets food eaten
    for (Agent* a : agents) {
        foodEatenPerAgent.push_back(a->foodEaten);
        a->foodEaten = 0;
    }
}

int getCellX(int index)
{
    return XDIM / (float)20 + (index + 1) * XDIM / (agents.size() + 2);
}

int getCellY(int index)
{
    return (index + 1) * 1.5 * YDIM / (categories->size());
}

void drawSplash()
{
    std::stringstream s;
    int x, y;
    float i = 0;

    // Category Label
    for (i = 0; i < CATEGORY_COUNT; i++)
    {
        DrawText((*(categories+(int)i)).c_str(), xOffset,  yOffset + getCellY(i), TEXT_SIZE, ORANGE);
    }

    i = 0;

    for (Agent* a : agents)
    {
        x = getCellX(i); 
        y = yOffset;

        // Agent Label
        s << "Agent " << (i++)+1 << ": ";
        DrawText(s.str().c_str(), x, y, TEXT_SIZE, ORANGE);
        s.str(std::string());

        // Max Speed Stat
        x += 2 * TEXT_SIZE;
        y = yOffset + getCellY(1);
        s << a->maxSpeed;
        DrawText(s.str().c_str(), x, y, TEXT_SIZE, DARKGRAY);
        s.str(std::string());

        // Food Range Stat
        y = yOffset + getCellY(2);
        s << a->foodRange;
        DrawText(s.str().c_str(), x, y, TEXT_SIZE, DARKGRAY);
        s.str(std::string());

        // Detect Range Stat
        y = yOffset + getCellY(3);
        s << a->detectRange;
        DrawText(s.str().c_str(), x, y, TEXT_SIZE, DARKGRAY);
        s.str(std::string());

        // Recharge Time Stat
        y = yOffset + getCellY(4);
        s << a->rechargeTime;
        DrawText(s.str().c_str(), x, y, TEXT_SIZE, DARKGRAY);
        s.str(std::string());

    }

    // Food Eaten Stat
    for (i = 0; i < foodEatenPerAgent.size(); i++)
    {
        x = getCellX(i) + 2 * TEXT_SIZE;
        y = yOffset + getCellY(0);

        s.str(std::string());
        s << foodEatenPerAgent[i];
        DrawText(s.str().c_str(), x, y, TEXT_SIZE, DARKGRAY);
    }
}

void drawAgents() {
    for (Agent* ptr : agents) {
        if (ChaserAgent* j = dynamic_cast<ChaserAgent*>(ptr))
            j->draw();
        else if (WanderingAgent* k = dynamic_cast<WanderingAgent*>(ptr))
            k->draw();
        else if (MutantAgent* i = dynamic_cast<MutantAgent*>(ptr))
            i->draw();
    }
}

void updateAllAgents() {
    for (Agent* ptr : agents) {
        if (ChaserAgent* j = dynamic_cast<ChaserAgent*>(ptr))
            j->update(&food);
        else if (WanderingAgent* k = dynamic_cast<WanderingAgent*>(ptr))
            k->update(&food);
        else if (MutantAgent* i = dynamic_cast<MutantAgent*>(ptr))
            i->update(&food);
    }

}

bool comparePtrToNode(Agent* a, Agent* b) {
    //std::cout << a->foodEaten << "\t" << b->foodEaten << "\n";
    return (*a < *b);
}

void printAgents() {
    for (Agent* i : agents) {
        i->printVals();
        std::cout << "\n";
    }
}

void reproduce() {  
    vector<Agent*> newAgents;
    vector<int> indices;

    for (int j = 0; j < agents.size(); j++) {
        Agent* ptr = agents[j];

        if (WanderingAgent* w = dynamic_cast<WanderingAgent*>(ptr)) {


            for (int i = 0; i < agents.size(); i++) {
                std::cout << "\nj:" << j;
                std::cout << "\ti: " << i;
                Agent* ptr2 = agents[i];
                if (Vector2Distance(ptr2->location, w->location) > REPROCUTION_RANGE || rand() % 100 > (REPRODUCTION_CHANCE * 100)) {
                    std::cout << "notadded\n";
                    
                    continue;
                }//added
                else if (ChaserAgent* c = dynamic_cast<ChaserAgent*>(ptr2)) {

                    if (c->mutated || w->mutated) continue;

                    std::cout << "m\n";
                    //replaces wanderer
                    newAgents.push_back(new MutantAgent{
                            w->location,
                            (MUTATION_FACTOR * w->size + c->size) / (MUTATION_FACTOR+1),            
                            (MUTATION_FACTOR * w->maxSpeed + c->maxSpeed) / (MUTATION_FACTOR + 1),
                            (MUTATION_FACTOR * w->maxForce + c->maxForce) / (MUTATION_FACTOR + 1),    
                            (MUTATION_FACTOR * w->foodRange + c->foodRange) / (MUTATION_FACTOR + 1),
                            (MUTATION_FACTOR * w->detectRange + c->detectRange) / (MUTATION_FACTOR + 1),
                            (MUTATION_FACTOR * w->rechargeTime + c->rechargeTime) / (MUTATION_FACTOR + 1)
                        });
                    //replaces chaser
                    newAgents.push_back(new MutantAgent{
                            c->location,
                            (w->size + MUTATION_FACTOR * c->size) / (MUTATION_FACTOR + 1),           
                            (w->maxSpeed + MUTATION_FACTOR * c->maxSpeed) / (MUTATION_FACTOR + 1),
                            (w->maxForce + MUTATION_FACTOR * c->maxForce) / (MUTATION_FACTOR + 1),    
                            (w->foodRange + MUTATION_FACTOR * c->foodRange) / (MUTATION_FACTOR + 1),
                            (w->detectRange + MUTATION_FACTOR * c->detectRange) / (MUTATION_FACTOR + 1),
                            (w->rechargeTime + MUTATION_FACTOR * c->rechargeTime) / (MUTATION_FACTOR + 1)
                        });

                    circleRadii.push_back(Vector2Distance(c->location, w->location));
                    circlePos.push_back(Vector2{ (w->location.x + c->location.x) / 2, (w->location.y + c->location.y) / 2 });
                    startPos.push_back(w->location);
                    endPos.push_back(c->location);

                    //removes existing guys that were mutated

                    c->mutate();
                    w->mutate();

                    indices.push_back(j);
                    indices.push_back(i);

                }
            }
        }
    }
    for (int i = agents.size()-1; i >= 0; i--)
        if (agents[i]->mutated)
        {
            delete agents[i];
            agents.erase(agents.begin() + i);
        }

    std::cout << "before l = " << agents.size() << "\n\n";
    //printAgents();
    agents.insert(agents.end(), newAgents.begin(), newAgents.end());
    std::cout << "\n\nafter l = " << agents.size() << "\n\n";
    //printAgents();


}

void drawCircles() {
    for (int i = 0; i < circlePos.size(); i++) {
        DrawRing(circlePos[i], circleRadii[i] + 20, circleRadii[i] + 25, 0, 360, 1, RED);
        DrawLineEx(startPos[i], endPos[i], 5, RED);
    }
}
