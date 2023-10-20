#include "Header.h"
#include "ChaserAgent.cpp"
#include "WanderingAgent.cpp"
#include "MutantAgent.cpp"





const int evolutionScreenTime = 5, simRunTime = 5;
auto simStartTime = high_resolution_clock::now();
bool simulating = true;

vector<Vector2> circlePos;
vector<float> circleRadii;

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




    agents.reserve(CHASER_STARTING_POP+WANDERING_STARTING_POP);
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
            circlePos.clear();
            circleRadii.clear();
            startPos.clear();
            endPos.clear();


        }
        else if (currentRunTime > simRunTime) {    //draw spash screen showing the stat changes/killing/mutations
            if (simulating) {
                simulating = false;
                evolve();

            }
            //for testing
            drawAgents();
            drawFood();
            drawCircles();

            //drawSplash();
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

void evolve() {

    sort(agents.begin(), agents.end(), comparePtrToNode);

    for (Agent* a : agents) {
        a->foodEaten = 0;
    }

    agents.erase(agents.begin());

    reproduce();
    
       //removes the guy who eaten the least


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

void drawSplash() {
    //draw ranking, who died, who mutated etc.

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
    //cout << a->foodEaten << "\t" << b->foodEaten << "\n";
    return (*a < *b); 
}

void printAgents() {
    for (Agent* i : agents) {
        i->printVals();
        cout << "\n";
    }
}

void reproduce() {  //to be implemented
    vector<Agent*> newAgents;
    vector<Agent*> agentsCopy(agents);
    int qw = 0, wq = 0;

    for (int i = 0; i < agents.size(); i++) {
        Agent*ptr = agents[i];
        int g = 0;
        if (MutantAgent* i = dynamic_cast<MutantAgent*>(ptr)) continue;
        /*if (ChaserAgent* c = dynamic_cast<ChaserAgent*>(ptr)) {
            cout << "c\n";
            for (Agent* ptr2 : agents) {
                if (Vector2Distance(ptr2->location, c->location) > REPROCUTION_RANGE || rand() % 100 > (REPRODUCTION_CHANCE * 100)) continue;
                if (WanderingAgent* w = dynamic_cast<WanderingAgent*>(ptr))
                    newAgents.push_back(new MutantAgent{
                            Vector2{(float)GetRandomValue(0, XDIM), (float)GetRandomValue(0, YDIM)},
                            (w->size + c->size) / 2,            //not needed
                            (w->maxSpeed + c->maxSpeed) / 2,
                            (w->maxForce + c->maxForce) / 2,    //not needed
                            (w->detectRange + c->detectRange) / 2,
                            (w->foodRange + c->foodRange) / 2,
                            (w->rechargeTime + c->rechargeTime) / 2
                        });
            }
        }
        else*/ if (WanderingAgent* w = dynamic_cast<WanderingAgent*>(ptr)) {
            //cout << "w\n";
            for (int i = 0; i < agentsCopy.size(); i++) {
                g++;

                Agent*ptr2 = agentsCopy[i];
                if (Vector2Distance(ptr2->location, w->location) > REPROCUTION_RANGE || rand() % 100 >= (REPRODUCTION_CHANCE * 100)) {
                    //cout << "notadded\n";
                    continue;
                }//added
                else if (ChaserAgent* c = dynamic_cast<ChaserAgent*>(ptr2)) {
                    cout << "m\n";
                    newAgents.push_back(new MutantAgent{
                            Vector2{(float)GetRandomValue(0, XDIM), (float)GetRandomValue(0, YDIM)},
                            (w->size + c->size) / 2,            //not needed
                            (w->maxSpeed + c->maxSpeed) / 2,
                            (w->maxForce + c->maxForce) / 2,    //not needed
                            (w->foodRange + c->foodRange) / 2,
                            (w->detectRange + c->detectRange) / 2,
                            (w->rechargeTime + c->rechargeTime) / 2
                        });
                    circleRadii.push_back(Vector2Distance(c->location, w->location));
                    circlePos.push_back(Vector2{ (w->location.x + c->location.x) / 2, (w->location.y + c->location.y) / 2 });
                    startPos.push_back(w->location);
                    endPos.push_back(c->location);

                    agentsCopy.erase(agentsCopy.begin()+i);
                }
            }
            cout << g;
        }
    }
    cout << "before l = " << agents.size() << "\n\n";
    //printAgents();
    agents.insert(agents.end(), newAgents.begin(), newAgents.end());
    cout << "\n\nafter l = " << agents.size() << "\n\n";
    //printAgents();


}
void drawCircles() {
    for (int i = 0; i < circlePos.size(); i++) {
        DrawRing(circlePos[i], circleRadii[i] + 20, circleRadii[i] + 25, 0, 360, 1, RED);
        DrawLineEx(startPos[i], endPos[i], 5 ,RED);
    }
}
