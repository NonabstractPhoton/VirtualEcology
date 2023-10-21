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

#define XDIM 1600
#define YDIM 900

#define wanderI WanderingAgent(Vector2{(float)GetRandomValue(0, XDIM), (float)GetRandomValue(0, YDIM)}, 5, 2, .1, 50, 0, .5)
#define chaseI ChaserAgent(Vector2{(float)GetRandomValue(0, XDIM), (float)GetRandomValue(0, YDIM)}, 5, 3, .1, 5, 100, 0)

#define CHASER_STARTING_POP 5
#define WANDERING_STARTING_POP 5
#define FOOD_PER_ROUND 10

#define MUTATION_FACTOR 3

#define REPROCUTION_RANGE 200
#define REPRODUCTION_CHANCE 1




void drawFood();
void generateFood();
void evolve();
void drawAgents();
void drawSplash();
void updateAllAgents();
void printAgents();
void reproduce();

