#pragma once
#include "raylib.h"

constexpr int SCREEN_WIDTH{800};
constexpr int SCREEN_HEIGHT{450};

struct Rect
{
    Vector2 corner1;
    Vector2 corner2;
};

struct Object
{
    Vector2 pos;
    Vector2 vel;
};

struct Player
{
    Vector2 pos;
    Vector2 vel;
};

double absd(double val);