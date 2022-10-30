#include "bsp.hpp"
#include "sim.hpp"
#include <algorithm>
#include <iostream>
#include <math.h>

Node *createBSPTree(std::vector<Rect> &geometryVec, int depth)
{
    if (geometryVec.size() == 0)
    {
        return nullptr;
    }

    int numGeometries = geometryVec.size();
    if (depth >= 10 || numGeometries <= 2)
    {
        return new Node{
            nullptr,
            nullptr,
            geometryVec,
            none,
        };
    }

    std::vector<Rect> frontVec, backVec;
    Rect plane = pickSplittingPlane(geometryVec);

    for (int i = 0; i < numGeometries; i++)
    {
        Rect rect = geometryVec.at(i);
        Rect frontPart, backPart;
    }
}

Rect pickSplittingPlane(std::vector<Rect> geometryVec)
{
    std::vector<double> xCoordsVec{};
    std::vector<double> yCoordsVec{};

    for (Rect rect : geometryVec)
    {
        xCoordsVec.push_back(absd(rect.corner1.x) + absd(rect.corner2.x - rect.corner1.x) / 2.0);
        yCoordsVec.push_back(absd(rect.corner1.y) + absd(rect.corner2.y - rect.corner1.y) / 2.0);
    }

    std::sort(xCoordsVec.begin(), xCoordsVec.end());
    std::sort(yCoordsVec.begin(), yCoordsVec.end());

    if ((xCoordsVec.end() - xCoordsVec.begin()) > (yCoordsVec.end() - yCoordsVec.begin()))
    {
    }
    else
    {
    }
}
