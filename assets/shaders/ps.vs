#version 330 core
/*  PlayStation-1-style vertex shader  */

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexTexCoord;
layout(location = 2) in vec4 vertexColor;

out vec2 fragTexCoord;   // passed straight to default fragment shader
out vec4 fragColor;

uniform mat4  mvp;           // filled automatically by raylib
uniform vec2  screenSize;    // set from C++
uniform float grid;          // 128 ≈ PS1, lower = wobblier

void main()
{
    /* hand varyings to fragment stage unchanged */
    fragTexCoord = vertexTexCoord;
    fragColor    = vertexColor;

    /* 1. Model-View-Projection transform --------------------------- */
    vec4 pos = mvp * vec4(vertexPosition, 1.0);

    /* 2. Clip-space → pixel coordinates ---------------------------- */
    vec2 ndc = pos.xy / pos.w;                  // −1..+1
    vec2 px  = (ndc * 0.5 + 0.5) * screenSize;  // 0..res

    /* 3. Quantise to coarse grid ----------------------------------- */
    vec2 step = screenSize / grid;              // e.g. 3.125 px
    px = floor(px / step) * step;               // truncate

    /* 4. Back to clip-space ---------------------------------------- */
    ndc        = (px / screenSize) * 2.0 - 1.0;
    pos.xy     = ndc * pos.w;
    gl_Position = pos;
}
