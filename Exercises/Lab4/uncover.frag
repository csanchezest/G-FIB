#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform float time;
in vec3 NDC;

void main()
{

    if(NDC.x<=time-1) //fragColor = mix(vec4(0,0,frontColor.z,0),vec4(1,1,1,0),step(time-1,NDC.x));
    fragColor = vec4(0,0,frontColor.z,0);
    else discard;
}
