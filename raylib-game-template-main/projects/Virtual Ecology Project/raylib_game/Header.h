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


void drawFood();
void generateFood();
void evolve();
void drawAgents();
void drawSplash();
void updateAllAgents();
