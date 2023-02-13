#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform float n = 8;

void main()
{  
    float a = vtexCoord.x * n, b = vtexCoord.y * n;  
    float val;
    if(fract(a)<=0.1 || fract(b) <= 0.1) val = 1;
    else val = 0;
    fragColor = mix(vec4(0.8,0.8,0.8,1),vec4(0,0,0,0),step(1,val));
}
