#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <iostream>
#include <stdlib.h>  
#include <chrono>
#include <ctime>  
#include <algorithm>

using namespace std;
using namespace chrono;

#define DETECT_COLOR_START Color{0, 0, 255, 255}
#define DETECT_COLOR_END Color{255, 0, 0, 255}
#define EAT_COLOR_START Color{0, 255, 0, 255}
#define EAT_COLOR_END Color{255, 0, 0, 255}

#define XDIM 1920 
#define YDIM 1080

#define wanderI WanderingAgent(Vector2{(float)GetRandomValue(0, XDIM), (float)GetRandomValue(0, YDIM)}, 5, 2, .1, 60, 0, .5)
#define chaseI ChaserAgent(Vector2{(float)GetRandomValue(0, XDIM), (float)GetRandomValue(0, YDIM)}, 5, 2.5, .1, 5, 80, 0)

#define CHASER_STARTING_POP 5
#define WANDERING_STARTING_POP 5
#define FOOD_PER_ROUND 125

#define SIM_RUN_TIME 20
#define MUTATION_SCREEN_TIME 1
#define SPLASH_SCREEN_TIME 10

#define MUTATION_FACTOR 2

#define REPROCUTION_RANGE 200
#define REPRODUCTION_CHANCE 1

#define TEXT_SIZE 26

static const string categories[] = { "Food Eaten:", "Max Speed:", "Food Range:", "Detect Range:", "Recharge Time:" };
#define CATEGORY_COUNT 5




void drawFood();
void generateFood();
void evolve();
void drawAgents();
void drawSplash();
void updateAllAgents();
void printAgents();
void reproduce();

