#pragma once

#include "sim.hpp"
#include <vector>

void resolveNaiveCollisionWithRects(const std::vector<Rect> &rectVec, const Object &obj, std::vector<Rect> &collisionVec);
