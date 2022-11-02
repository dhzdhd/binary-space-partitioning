#pragma once

#include "raylib.h"
#include "sim.hpp"
#include <vector>

enum class Orientation
{
    vertical,
    horizontal,
    none,
};

enum class RectLocation
{
    front,
    behind,
    straddling,
};

struct Node
{
    Node *left;
    Node *right;
    std::vector<Rect> data;
    Rect plane;
};

struct SplitRect
{
    Rect front;
    Rect back;
};

Node *createBSPTree(std::vector<Rect> &geometryVec, int depth, Rect remainingScreen);
RectLocation classifyRectToPlane(Rect rect, Rect plane);
Rect pickSplittingPlane(const std::vector<Rect> &geometryVec, int depth, Rect remainingScreen);
SplitRect splitRectangleAsPerPlane(Rect rect, Rect plane);
