#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 N;

void main()
{
    gl_FragDepth = 1 - gl_FragCoord.z;
    fragColor = frontColor * -N.z;
}
