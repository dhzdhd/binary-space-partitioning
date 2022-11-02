#include "bsp.hpp"
#include "sim.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include "raymath.h"

Node *createBSPTree(const std::vector<Rect> &geometryVec, int depth, const Rect &remainingScreen, const bool isMedianPartition)
{
    if (geometryVec.empty())
    {
        return nullptr;
    }

    int numGeometries = geometryVec.size();
    if (depth >= 10 || numGeometries <= 2)
    {
        std::cout << "depth: " << depth << std::endl;
        return new Node{
            nullptr,
            nullptr,
            geometryVec,
            Rect{Vector2{0, 0}, Vector2{0, 0}},
        };
    }

    std::vector<Rect> frontVec, backVec;
    Rect plane = pickSplittingPlane(geometryVec, depth, remainingScreen, isMedianPartition);

    for (int i = 0; i < numGeometries; i++)
    {
        Rect rect = geometryVec.at(i);
        Rect frontPart, backPart;

        switch (classifyRectToPlane(rect, plane))
        {
        case RectLocation::front:
        {
            frontVec.push_back(rect);
            break;
        }
        case RectLocation::behind:
        {
            backVec.push_back(rect);
            break;
        }
        case RectLocation::straddling:
        {
            // split polygon and get 2 parts to push to 2 lists
            SplitRect splitRect = splitRectangleAsPerPlane(rect, plane);
            Rect front = splitRect.front;
            Rect back = splitRect.back;

            frontVec.push_back(front);
            backVec.push_back(back);
            break;
        }
        default:
            break;
        }
    }

    // front = right, top
    // back = left, bottom

    Rect frontPlane{};
    Rect backPlane{};

    if (depth % 2 == 0)
    {
        // vertical
        frontPlane = Rect{plane.corner1, remainingScreen.corner2};
        backPlane = Rect{remainingScreen.corner1, plane.corner2};
    }
    else
    {
        // horizontal
        frontPlane = Rect{remainingScreen.corner1, plane.corner2};
        backPlane = Rect{plane.corner1, remainingScreen.corner2};
    }
    Node *frontTree = createBSPTree(frontVec, depth + 1, frontPlane, isMedianPartition);
    Node *backTree = createBSPTree(backVec, depth + 1, backPlane, isMedianPartition);
    return new Node{backTree, frontTree, geometryVec, plane};
}

Rect pickSplittingPlane(const std::vector<Rect> &geometryVec, int depth, const Rect &remainingScreen, const bool isMedianPartition)
{
    // Commented code needed to split by median.
    std::vector<double> xCoordsVec{};
    std::vector<double> yCoordsVec{};

    for (Rect rect : geometryVec)
    {
        xCoordsVec.push_back(absd(rect.corner1.x) + absd(rect.corner2.x - rect.corner1.x) / 2.0);
        yCoordsVec.push_back(absd(rect.corner1.y) + absd(rect.corner2.y - rect.corner1.y) / 2.0);
    }

    std::sort(xCoordsVec.begin(), xCoordsVec.end());
    std::sort(yCoordsVec.begin(), yCoordsVec.end());

    // Alternatively split in half based on depth
    if (depth % 2 == 0)
    {
        // vertical
        float x{};
        if (!isMedianPartition)
        {
            x = remainingScreen.corner1.x + (remainingScreen.corner2.x - remainingScreen.corner1.x) / 2;
        }
        else
        {
            size_t size = xCoordsVec.size();
            if (size % 2 != 0)
            {
                x = xCoordsVec[size / 2];
            }
            else
            {
                x = (xCoordsVec[size / 2] + xCoordsVec[(size / 2) - 1]) / 2.f;
            }
        }

        return Rect{Vector2{x, remainingScreen.corner1.y}, Vector2{x, remainingScreen.corner2.y}};
    }
    else
    {
        // horizontal
        float y{};
        if (!isMedianPartition)
        {
            y = remainingScreen.corner1.y + (remainingScreen.corner2.y - remainingScreen.corner1.y) / 2;
        }
        else
        {
            size_t size = yCoordsVec.size();
            if (size % 2 != 0)
            {
                y = yCoordsVec[size / 2];
            }
            else
            {
                y = (yCoordsVec[size / 2] + yCoordsVec[(size / 2) - 1]) / 2.f;
            }
        }
        return Rect{Vector2{remainingScreen.corner1.x, y}, Vector2{remainingScreen.corner2.x, y}};
    }
}

RectLocation classifyRectToPlane(const Rect &rect, const Rect &plane)
{
    if (plane.corner1.x == plane.corner2.x)
    {
        // vertical
        if (rect.corner1.x > plane.corner1.x)
        {
            return RectLocation::front;
        }
        else if (rect.corner2.x < plane.corner1.x)
        {
            return RectLocation::behind;
        }
        return RectLocation::straddling;
    }
    else
    {
        // horizontal
        if (rect.corner2.y < plane.corner1.y)
        {
            return RectLocation::front;
        }
        else if (rect.corner1.y > plane.corner1.y)
        {
            return RectLocation::behind;
        }
        return RectLocation::straddling;
    }
}

SplitRect splitRectangleAsPerPlane(const Rect &rect, const Rect &plane)
{
    if (plane.corner1.x == plane.corner2.x)
    {
        // vertical
        Rect front = Rect{rect.corner1, Vector2{plane.corner1.x, rect.corner2.y}};
        Rect behind = Rect{Vector2{plane.corner1.x, rect.corner1.y}, rect.corner2};
        return SplitRect{behind, front};
    }
    else
    {
        // horizontal
        Rect front = Rect{Vector2{rect.corner1.x, plane.corner1.y}, rect.corner2};
        Rect behind = Rect{rect.corner1, Vector2{rect.corner2.x, plane.corner1.y}};
        return SplitRect{behind, front};
    }
}
