#include "raylib.h"
#include <cstdlib>
#include "bsp.hpp"
#include "sim.hpp"

int main()
{
    // Initialization

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Binary Space Partitioning");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_Q))
        {
            std::exit(0);
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
