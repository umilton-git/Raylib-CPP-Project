#include "ball3d.h"
#include <cmath>        // fabsf, copysignf
#include <initializer_list>   // for brace-init list in the range-for
#include <cmath>              // already present for fabsf / copysignf
#include <raylib.h>          // for Vector3, DrawSphere, etc.


Ball3D::Ball3D()
{
    position = { 0.0f, radius, 0.0f };   // 1 unit above the floor
    velocity = { 3.0f, 6.0f, 2.5f };     // arbitrary initial kick
}

/*-----------------------------------------*/
void Ball3D::Update(float dt)
/*-----------------------------------------*/
{
    // gravity (-Y axis)
    velocity.y -= 9.81f * dt;

    // integrate position
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    position.z += velocity.z * dt;

    // ----- collide with floor (Y = 0 plane) -----
    if (position.y - radius < 0.0f)
    {
        position.y = radius;
        velocity.y = -velocity.y * restitution;
    }

    // ----- very simple box walls on X and Z -----
for (float Vector3::*axis : { &Vector3::x, &Vector3::z })
{
    float &p = position.*axis;        // position.x  or position.z
    float &v = velocity.*axis;        // velocity.x  or velocity.z

    if (std::fabs(p) > worldBounds - radius)
    {
        p = std::copysign(worldBounds - radius, p);
        v = -v * restitution;
    }
}

}

/*-----------------------------------------*/
void Ball3D::Draw() const
/*-----------------------------------------*/
{
    DrawSphere(position, radius, MAROON);
}
