#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform int tiles=1;

uniform sampler2D colorMap;

void main()
{
    fragColor = frontColor * texture(colorMap, vec2(vtexCoord.s*tiles, vtexCoord.t*tiles));
}


