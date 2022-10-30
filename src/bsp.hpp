#pragma once

#include "raylib.h"
#include "sim.hpp"
#include <vector>

enum Orientation
{
    vertical,
    horizontal,
    none,
};

struct Node
{
    Node *left;
    Node *right;
    std::vector<Rect> data;
    Orientation orientation;
};

Node *createBSPTree(std::vector<Rect> &geometryVec, int depth);
Rect pickSplittingPlane(std::vector<Rect> geometryVec);
