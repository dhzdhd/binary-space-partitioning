#pragma once
#include "raylib.h"

constexpr int SCREEN_WIDTH{800};
constexpr int SCREEN_HEIGHT{450};

struct Ball
{
    Vector2 pos;
    Vector2 vel;
    Color color;
};