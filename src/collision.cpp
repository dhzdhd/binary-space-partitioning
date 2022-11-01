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

std::vector<Rect> getVecFromTree(Node *root, Object &obj)
{
    Node *temp = root;
    while (temp->right != nullptr && temp->left != nullptr)
    {
        ObjectLocation location = classifyObjectToPlane(obj, temp->plane);
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
