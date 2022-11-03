#include "raylib.h"
#include <cstdlib>
#include "bsp.hpp"
#include "sim.hpp"
#include "collision.hpp"
#include <vector>
#include <iostream>
#include <string>
#include "naive_collision.hpp"

int main()
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Binary Space Partitioning");

    bool isRectangleMode{true};
    bool isGeometryUpdated{false};
    bool isBSPCollision{true};
    bool isMedianPartition{false};

    std::vector<Rect> geometryVec{};
    std::vector<Rect> geometryVecActive{};
    std::vector<Rect> geometryVecCollision{};
    std::vector<Rect> planeVec{};

    Object obj = Object{Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, getRandomVector(-100, 100)};
    std::vector<Object> objectVec{obj};

    Node *root;

    Vector2 mousePos{};
    Vector2 mouseDraggedPos{};

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_Q))
        {
            std::exit(0);
        }
        if (IsKeyPressed(KEY_S))
        {
            isRectangleMode = !isRectangleMode;
        }
        if (IsKeyPressed(KEY_D))
        {
            isBSPCollision = !isBSPCollision;
        }
        if (IsKeyPressed(KEY_A))
        {
            isMedianPartition = !isMedianPartition;
        }

        if (isRectangleMode)
        {
            // Rectangle Mode
            isGeometryUpdated = false;

            if (IsMouseButtonPressed(0))
            {
                mousePos = GetMousePosition();
                std::cout << GetMousePosition().x << " " << GetMousePosition().y << "\n";
            }
            if (IsMouseButtonDown(0))
            {
                Vector2 dragVec = GetGestureDragVector();
                mouseDraggedPos = Vector2{mousePos.x + dragVec.x * SCREEN_WIDTH, mousePos.y + dragVec.y * SCREEN_HEIGHT};
                std::cout << mouseDraggedPos.x << " " << mouseDraggedPos.y << "\n";

                Rect rec = Rect{mousePos, mouseDraggedPos};
                DrawRectangle(rec.corner1.x, rec.corner1.y, rec.corner2.x - rec.corner1.x, rec.corner2.y - rec.corner1.y, ColorAlpha(GRAY, 0.1f));
            }
            if (IsMouseButtonReleased(0))
            {
                geometryVec.push_back(Rect{mousePos, mouseDraggedPos});
            }
        }
        else
        {
            // Sim Mode

            Node *root;
            // Create BSP tree based on geometryVec
            if (!isGeometryUpdated && isBSPCollision)
            {
                isGeometryUpdated = true;

                root = createBSPTree(geometryVec, 0, Rect{Vector2{0, 0}, Vector2{SCREEN_WIDTH, SCREEN_HEIGHT}}, isMedianPartition);

                if (root == nullptr)
                {
                    isRectangleMode = true;
                }
            }

            if (IsMouseButtonPressed(0))
            {
                objectVec.push_back(Object{GetMousePosition(), getRandomVector(-100, 100)});
            }

            for (Object &obj : objectVec)
            {
                // Check collision of projectile with screen
                resolveCollisionWithScreen(obj);

                obj.pos.x += obj.vel.x * GetFrameTime();
                obj.pos.y += obj.vel.y * GetFrameTime();

                if (isBSPCollision)
                {
                    auto temp = getVecFromTree(root, obj);
                    geometryVecActive.insert(
                        geometryVecActive.end(),
                        temp.begin(),
                        temp.end());
                    resolveCollisionWithRects(geometryVecActive, obj, geometryVecCollision);
                }
                else
                {
                    resolveNaiveCollisionWithRects(geometryVec, obj, geometryVecCollision);
                }
            }

            // for (Rect rec : geometryVecActive)
            // {
            //     DrawRectangle(rec.corner1.x, rec.corner1.y, rec.corner2.x - rec.corner1.x, rec.corner2.y - rec.corner1.y, YELLOW);
            // }
            // while (temp->left != nullptr && temp != nullptr)
            // {

            //     DrawRectangle(temp->plane.corner1.x, temp->plane.corner1.y, (depth % 2 == 0) ? 2 : temp->plane.corner2.x - temp->plane.corner1.x, (depth % 2 == 0) ? temp->plane.corner2.y - temp->plane.corner1.y : 2, GREEN);
            //     std::cout
            //         << std::endl;
            //     depth++;
            //     temp = temp->left;
            // }
        }

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawFPS(0, 0);
        DrawText(isRectangleMode ? "Rectangle Mode" : "Sim Mode", 0, 20, 20, GREEN);
        DrawText(isBSPCollision ? "BSP collision" : "Naive collision", 0, 40, 20, GREEN);
        DrawText(std::to_string(objectVec.size()).c_str(), 0, 60, 20, GREEN);

        // Draw handmade rectangles
        for (Rect rec : geometryVec)
        {
            DrawRectangle(rec.corner1.x, rec.corner1.y, rec.corner2.x - rec.corner1.x, rec.corner2.y - rec.corner1.y, ColorAlpha(GRAY, 0.1f));
        }

        if (!isRectangleMode)
        {
            // Draw active rectangles
            for (Rect rec : geometryVecActive)
            {
                DrawRectangle(rec.corner1.x, rec.corner1.y, rec.corner2.x - rec.corner1.x, rec.corner2.y - rec.corner1.y, ColorAlpha(YELLOW, 0.7f));
            }
            for (Rect rec : geometryVecCollision)
            {
                DrawRectangle(rec.corner1.x, rec.corner1.y, rec.corner2.x - rec.corner1.x, rec.corner2.y - rec.corner1.y, ColorAlpha(RED, 0.7f));
            }

            for (Object obj : objectVec)
            {
                DrawCircle(obj.pos.x, obj.pos.y, 5, BLUE);
            }

            geometryVecActive.clear();
            geometryVecCollision.clear();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

double absd(const double value)
{
    return value < 0 ? -value : value;
}

Vector2 getRandomVector(const int min, const int max)
{
    return Vector2{
        (float)GetRandomValue(min, max),
        (float)GetRandomValue(min, max),
    };
}
