#include "collision.hpp"
#include <iostream>

void resolveCollisionWithScreen(Object &obj)
{
    if (obj.pos.x > SCREEN_WIDTH - 5 || obj.pos.x < 5)
    {
        obj.vel.x *= -1;
    }
    if (obj.pos.y < 5 || obj.pos.y > SCREEN_HEIGHT - 5)
    {
        obj.vel.y *= -1;
    }
}

std::vector<Rect> resolveCollisionWithRects(std::vector<Rect> rectVec, Object &obj)
{
    std::vector<Rect> collisionVec{};
    for (auto rect : rectVec)
    {
        Rectangle raylibRect = Rectangle{
            rect.corner1.x,
            rect.corner1.y,
            rect.corner2.x - rect.corner1.x,
            rect.corner2.y - rect.corner1.y,
        };
        bool collision = CheckCollisionCircleRec(obj.pos, 5, raylibRect);
        if (collision)
        {
            collisionVec.push_back(rect);
        }
    }

    return collisionVec;
}

std::vector<Rect> getVecFromTree(Node *root, Object &obj)
{
    Node *temp = root;
    std::vector<Rect> planeVec{};

    while (temp->right != nullptr && temp->left != nullptr)
    {
        ObjectLocation location = classifyObjectToPlane(obj, temp->plane);
        planeVec.push_back(temp->plane);

        switch (location)
        {
        case positive:
        {
            temp = temp->right;
            break;
        }
        case negative:
        {
            temp = temp->left;
            break;
        }
        default:
            break;
        }
    }

    // TODO: Move out of this function by returning planeVec
    // Draws partitions as per projectile position
    for (auto rect : planeVec)
    {
        if (rect.corner1.x == rect.corner2.x)
        {
            // vert
            DrawRectangle(rect.corner1.x, rect.corner1.y, 2, rect.corner2.y - rect.corner1.y, GREEN);
        }
        else
        {
            DrawRectangle(rect.corner1.x, rect.corner1.y, rect.corner2.x - rect.corner1.x, 2, GREEN);
        }
    }

    return temp->data;
}

ObjectLocation classifyObjectToPlane(Object obj, Rect plane)
{
    if (plane.corner1.x == plane.corner2.x)
    {
        // vertical
        if (obj.pos.x > plane.corner1.x)
        {
            return positive;
        }
        return negative;
    }
    else
    {
        // horizontal
        if (obj.pos.y < plane.corner1.y)
        {
            return positive;
        }
        return negative;
    }
}
