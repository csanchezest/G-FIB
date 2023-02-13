#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform float time;
uniform sampler2D explosion;
in vec2 vtexCoord;

void main()
{

    int val = (int) floor(time*30);
    fragColor = frontColor * texture(explosion, vec2((vtexCoord.s + val)/8, (vtexCoord.t + 5 - val/8)/6));
    fragColor = fragColor.a * fragColor;
}
