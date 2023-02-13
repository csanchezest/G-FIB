#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform float n = 8;

void main()
{
    int a = (int) floor(vtexCoord.x * n), b = (int) floor(vtexCoord.y * n);
    float val;
    if((a+b)%2==0) val = 0;
    else val = 1;
    fragColor = mix(vec4(0.8,0.8,0.8,1),vec4(0,0,0,0),step(1,val));
}
