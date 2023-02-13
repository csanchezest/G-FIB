#version 330 core

in vec4 gfrontColor;
out vec4 fragColor;

in vec2 gtexCoord;

void main()
{
    if(gtexCoord.s <=0.95 && gtexCoord.s >= 0.05 && gtexCoord.t <= 0.95 && gtexCoord.t >= 0.05) fragColor = gfrontColor;
    else fragColor = vec4(0.);
}
