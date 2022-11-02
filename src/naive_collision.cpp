#include "naive_collision.hpp"

void resolveNaiveCollisionWithRects(const std::vector<Rect> &rectVec, const Object &obj, std::vector<Rect> &collisionVec)
{
    for (auto rect : rectVec)
    {
        Rectangle raylibRect = Rectangle{
            rect.corner1.x,
            rect.corner1.y,
            rect.corner2.x - rect.corner1.x,
            rect.corner2.y - rect.corner1.y,
        };
        if (CheckCollisionCircleRec(obj.pos, 5, raylibRect))
        {
            collisionVec.push_back(rect);
        }
    }
}