#pragma once

#include "sim.hpp"
#include "bsp.hpp"

enum class ObjectLocation
{
    positive,
    negative,
};

std::vector<Rect> getVecFromTree(Node *root, const Object &obj);
void resolveCollisionWithScreen(Object &obj);
ObjectLocation classifyObjectToPlane(const Object &obj, const Rect &plane);
void resolveCollisionWithRects(const std::vector<Rect> &rectVec, const Object &obj, std::vector<Rect> &collisionVec);
