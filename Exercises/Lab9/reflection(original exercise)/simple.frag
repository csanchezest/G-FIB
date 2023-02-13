#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float size;

in vec2 vtexCoord;

void main()
{
    fragColor = texture(colorMap, vec2(gl_FragCoord.x/size,gl_FragCoord.y/size));
}
