#pragma once

#include "sim.hpp"
#include "bsp.hpp"

enum ObjectLocation
{
    positive,
    negative,
};

std::vector<Rect> getVecFromTree(Node *root, Object &obj);
void resolveCollisionWithScreen(Object &obj);
ObjectLocation classifyObjectToPlane(Object obj, Rect plane);
