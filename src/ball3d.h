#pragma once
#include <raylib.h>

class Ball3D
{
public:
    Ball3D();

    // per-frame simulation & rendering
    void Update(float dt = GetFrameTime());
    void Draw() const;

private:
    Vector3 position{};
    Vector3 velocity{};
    float   radius        = 1.0f;   // metres
    float   restitution   = 0.8f;   // bounciness 0-1
    float   worldBounds   = 9.0f;   // half-extent of a simple box
};
