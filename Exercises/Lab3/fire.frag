#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform float slice=0.1;
uniform float time;
uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform sampler2D sampler3;
in vec2 vtexCoord;

void main()
{
    float val = mod(time,4 * slice);
    if(val>=0 && val<slice) fragColor = texture(sampler0,vtexCoord);
    else if(val>=slice && val<2*slice) fragColor = texture(sampler1,vtexCoord);
    else if(val>=2*slice && val<3*slice) fragColor = texture(sampler2,vtexCoord);
    else fragColor = texture(sampler3,vtexCoord);
    
    //fragColor = frontColor;
}
