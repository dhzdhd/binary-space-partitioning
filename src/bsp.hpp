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

Node *createBSPTree(const std::vector<Rect> &geometryVec, int depth, const Rect &remainingScreen, const bool isMedianPartition);
RectLocation classifyRectToPlane(const Rect &rect, const Rect &plane);
Rect pickSplittingPlane(const std::vector<Rect> &geometryVec, int depth, const Rect &remainingScreen, const bool isMedianPartition);
SplitRect splitRectangleAsPerPlane(const Rect &rect, const Rect &plane);
