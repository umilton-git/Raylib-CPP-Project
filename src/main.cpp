#include <raylib.h>
#include "ball3d.h"
#include "fella.h"

int main()
{
    constexpr int screenWidth  = 800;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "A Fucking Cube");
    SetTargetFPS(60);

    // ── Load PS-style wobble shader ─────────────────────────────────────
    Shader ps = LoadShader("assets/shaders/ps.vs", nullptr);   // <- vertex shader
    int locMVP  = GetShaderLocation(ps, "mvp");
    int locRes  = GetShaderLocation(ps, "screenSize");
    int locGrid = GetShaderLocation(ps, "grid");

    float res[2] = { (float)screenWidth, (float)screenHeight };
    SetShaderValue(ps, locRes, res, SHADER_UNIFORM_VEC2);

    float snap = 256.0f;          // 128 / 64 / 32 = wobblier
    SetShaderValue(ps, locGrid, &snap, SHADER_UNIFORM_FLOAT);

    // -------- camera ------------
    Camera3D camera{};
    camera.position   = { 8.0f, 8.0f, 8.0f };
    camera.target     = { 0.0f, 1.0f, 0.0f };
    camera.up         = { 0.0f, 1.0f, 0.0f };
    camera.fovy       = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Ball3D ball;
    Fella guy;
    Color  bg = { 135, 190, 170, 255 };
    bool cameraLocked = true;

    while (!WindowShouldClose())
{
    /* --------- input / camera handling (unchanged) ---------- */
    if (IsKeyDown(KEY_LEFT_CONTROL))
    {
        if (cameraLocked) { EnableCursor();  cameraLocked = false; }
    }
    else
    {
        if (!cameraLocked) { DisableCursor(); cameraLocked = true; }
    }

    if (cameraLocked)
    {
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        DisableCursor();
    }
    else
    {
        UpdateCamera(&camera, CAMERA_ORBITAL);
    }

    /* ------------------------ drawing ------------------------ */
    BeginDrawing();
        ClearBackground(bg);

        BeginMode3D(camera);
            BeginShaderMode(ps);                 // <-- everything between
                DrawPlane({0, 0, 0}, {20, 20}, DARKGREEN); // floor
                DrawGrid(20, 1.0f);                        // helper grid
                guy.Draw();                                // draw fella
            EndShaderMode();                   //      these two lines wobbles
        EndMode3D();

        DrawFPS(10, 10);
    EndDrawing();
}
/* -------------------------------------------------------------- */
UnloadShader(ps);


    CloseWindow();
    return 0;
}
