#include "raylib.h"
#include <cstdlib>
#include "bsp.hpp"
#include "sim.hpp"
#include "collision.hpp"
#include <vector>
#include <iostream>
#include "naive_collision.hpp"

int main()
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Binary Space Partitioning");

    bool isRectangleMode{true};
    bool isGeometryUpdated{false};
    bool isBSPCollision{true};

    std::vector<Rect> geometryVec{};
    std::vector<Rect> geometryVecActive{};
    std::vector<Rect> geometryVecCollision{};
    std::vector<Rect> planeVec{};

    Object obj = Object{Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, getRandomVector(-100, 100)};
    std::vector<Object> objectVec{obj};

    Node *root;

    Vector2 mousePos{};
    Vector2 mouseDraggedPos{};

    Player player = {Vector2{5, 5}, Vector2{-10, 10}};

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
            }
            if (IsMouseButtonReleased(0))
            {
                geometryVec.push_back(Rect{mousePos, mouseDraggedPos});
            }
        }
        else
        {
            // Sim Mode
            if (IsKeyDown(KEY_RIGHT))
            {
                player.vel.x = 200 * GetFrameTime();
            }
            if (IsKeyDown(KEY_LEFT))
            {
                player.vel.x = -200 * GetFrameTime();
            }
            if (IsKeyDown(KEY_UP))
            {
                player.vel.y = -200 * GetFrameTime();
            }
            if (IsKeyDown(KEY_DOWN))
            {
                player.vel.y = 200 * GetFrameTime();
            }
            if (IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_RIGHT))
            {
                player.vel.x = 0;
            }
            if (IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_DOWN))
            {
                player.vel.y = 0;
            }

            if (player.pos.x < 0)
            {
                player.pos.x = 0;
            }
            if (player.pos.x > SCREEN_WIDTH)
            {
                player.pos.x = SCREEN_WIDTH;
            }
            if (player.pos.y < 0)
            {
                player.pos.y = 0;
            }
            if (player.pos.y > SCREEN_HEIGHT)
            {
                player.pos.y = SCREEN_HEIGHT;
            }

            // Move player
            player.pos.x += player.vel.x;
            player.pos.y += player.vel.y;

            // Create projectile
            // if (IsMouseButtonPressed(0))
            // {
            //     Vector2 pos = GetMousePosition();
            //     objectVec.push_back(Object{
            //         player.pos,
            //         Vector2{100, 100},
            //     });
            // }

            Node *root;
            // Create BSP tree based on geometryVec
            if (!isGeometryUpdated && isBSPCollision)
            {
                isGeometryUpdated = true;

                root = createBSPTree(geometryVec, 0, Rect{Vector2{0, 0}, Vector2{SCREEN_WIDTH, SCREEN_HEIGHT}});

                if (root == nullptr)
                {
                    isRectangleMode = true;
                }
            }

            // int depth = 0;
            // Node *temp = root;

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
                    // geometryVecCollision.insert(
                    //     geometryVecCollision.end(),
                    //     temp.begin(),
                    //     temp.end());
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

        // Draw handmade rectangles
        for (Rect rec : geometryVec)
        {
            DrawRectangle(rec.corner1.x, rec.corner1.y, rec.corner2.x - rec.corner1.x, rec.corner2.y - rec.corner1.y, ColorAlpha(GRAY, 0.1f));
        }

        // geometryVecActive.clear();

        // DrawCircle(player.pos.x, player.pos.y, 5, BLACK);

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

        // DrawCircle(obj.pos.x, obj.pos.y, 5, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

double absd(double value)
{
    return value < 0 ? -value : value;
}

Vector2 getRandomVector(int min, int max)
{
    return Vector2{
        (float)GetRandomValue(min, max),
        (float)GetRandomValue(min, max),
    };
}
