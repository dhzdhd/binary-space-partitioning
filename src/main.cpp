#include "raylib.h"
#include <cstdlib>
#include "bsp.hpp"
#include "sim.hpp"
#include <vector>
#include <iostream>

int main()
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Binary Space Partitioning");

    bool isRectangleMode{true};

    std::vector<Rect> geometryVec{};
    std::vector<Object> objectVec{};

    Vector2 mousePos{};
    Vector2 mouseDraggedPos{};

    Player player = {Vector2{5, 5}, Vector2{0, 0}};

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

        if (isRectangleMode)
        {
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

            player.pos.x += player.vel.x;
            player.pos.y += player.vel.y;

            if (IsMouseButtonPressed(0))
            {
                Vector2 pos = GetMousePosition();
                objectVec.push_back(Object{
                    player.pos,
                    Vector2{100, 100},
                });
            }

            for (Object obj : objectVec)
            {
                obj.pos.x += obj.vel.x;
                obj.pos.y += obj.vel.y;
            }

            // run bsp tree and create partitions
            // run simulation
        }

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawFPS(0, 0);
        DrawText(isRectangleMode ? "Rectangle Mode" : "Sim Mode", 0, 20, 20, GREEN);

        // draw rects
        for (Rect rec : geometryVec)
        {
            DrawRectangle(rec.corner1.x, rec.corner1.y, rec.corner2.x - rec.corner1.x, rec.corner2.y - rec.corner1.y, GRAY);
        }

        DrawCircle(player.pos.x, player.pos.y, 5, BLACK);

        if (!isRectangleMode)
        {
            for (Object obj : objectVec)
            {
                DrawCircle(obj.pos.x, obj.pos.y, 2, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

double absd(double value)
{
    return value < 0 ? -value : value;
}
