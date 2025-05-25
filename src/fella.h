#pragma once
#include <raylib.h>

class Fella
{
public:
    Fella();

    // per-frame simulation & rendering
    void Update(float dt = GetFrameTime());
    void Draw() const;

private:
    Vector3 position{};
};
