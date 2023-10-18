#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <iostream>
#include <stdlib.h>  
#include <chrono>
#include <ctime>  

#define DETECT_COLOR Color{216, 162, 235, 255}
#define EAT_COLOR Color{162, 235, 166, 255}
#define XDIM 1600
#define YDIM 900
#define wanderI WanderingAgent(Vector2{(float)GetRandomValue(0, XDIM), (float)GetRandomValue(0, YDIM)}, 5, 2, .1, 10, 0, 1)
#define chaseI ChaserAgent(Vector2{(float)GetRandomValue(0, XDIM), (float)GetRandomValue(0, YDIM)}, 5, 3, .1, 5, 100, 0)



void drawFood();
void generateFood();
void evolve();
void drawAgents();
void drawSplash();
void updateAllAgents();
