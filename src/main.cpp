#include "raylib.h"
#include <cstdlib>
#include "bsp.hpp"
#include "sim.hpp"
#include <vector>

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

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
