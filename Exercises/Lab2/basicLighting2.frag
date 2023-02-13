#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in float z_normal;

void main()
{
    fragColor = frontColor * z_normal;
}
