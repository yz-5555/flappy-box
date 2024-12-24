#include "flappy-box.h"

void run_flappy_box()
{
    InitWindow(800, 600, "flappy-box");

    Box box = {
        .body = { 0.f, 0.f, 0.f, 0.f },
        .velocity = { 0.f, 0.f },
        .rotation = 0.f,
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLUE);
            DrawText("flappy-box", 10, 10, 20, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();
}

// DOD & Entity
