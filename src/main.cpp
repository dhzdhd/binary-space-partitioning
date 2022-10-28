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
    std::vector<Ball> objectVec{};

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
            if (IsMouseButtonDown(0))
            {
                std::cout << "e";
            }
        }

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawFPS(0, 0);
        DrawText(isRectangleMode ? "Rectangle Mode" : "Sim Mode", 0, 20, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
