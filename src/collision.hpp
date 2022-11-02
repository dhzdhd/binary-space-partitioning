#pragma once

#include "sim.hpp"
#include "bsp.hpp"

enum class ObjectLocation
{
    positive,
    negative,
};

std::vector<Rect> getVecFromTree(Node *root, Object &obj);
void resolveCollisionWithScreen(Object &obj);
ObjectLocation classifyObjectToPlane(Object obj, Rect plane);
std::vector<Rect> resolveCollisionWithRects(std::vector<Rect> rectVec, Object &obj);
