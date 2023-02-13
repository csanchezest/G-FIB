#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform float time;
uniform sampler2D colorMap;

void main()
{
    vec2 coord = (vtexCoord+1)/2;
    float offs = 0.01 * sin(10.0 * time + 30.0 * coord.s);
    fragColor = texture(colorMap, vec2(coord.s + offs, coord.t + offs));
    //fragColor = vec4(coord,0,1);
}
