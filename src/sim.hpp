#pragma once
#include "raylib.h"

constexpr int SCREEN_WIDTH{800};
constexpr int SCREEN_HEIGHT{450};

struct Rect
{
    Vector2 end1;
    Vector2 end2;
};

struct Ball
{
    Vector2 pos;
    Vector2 vel;
    Color color;
};
