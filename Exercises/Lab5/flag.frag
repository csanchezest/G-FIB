#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

void main()
{
    vec2 tex = vtexCoord;
    tex.y /= 4;
    tex.y *= 3;
    vec4 color;  
    float coord = floor(vtexCoord.y*3);
    if(coord<1.0) color = vec4(0,0,1,1);
    else if(coord<2.0) color = vec4(1,1,0,1);
    else color = vec4(0,1,0,1);
    vec2 res = vec2(abs(vtexCoord.x-0.5),abs(vtexCoord.y-0.5)*3/4);
    float d = length(res);
    fragColor = mix(vec4(1,0,0,0),color,step(0.2, d)); 
    //int coord = (int) floor(vtexCoord.s*6);
    //fragColor.xyz = vec3(0.75,0.5,0);
    //fragColor = frontColor;
    //vec2 res = vec2(abs(vtexCoord.x-0.75),abs(vtexCoord.y*3/4-0.4));
    //float d = length(res);
    //vec2 res1 = vec2(abs(vtexCoord.x-0.45),abs(vtexCoord.y*3/4-0.4));
    //float d1 = length(res1); 
    //fragColor = mix(vec4(1,1,1,0),vec4(0.75,0.6,0.1,0),step(0.2, d));
    //if(length(vec2(abs(vtexCoord.s),abs(vtexCoord.t)))<=d1+0.2) fragColor = mix(vec4(0.75,0.6,0,0),vec4(0.75,0.6,0,0),step(0.2, d1));
    //if(tex.t>=1. && tex.t<=2. && tex.s>=0.8 && tex.s <=1.8) discard;
    //fragColor.xyz = vec3(0.75,0.5,0);
    //fragColor = frontColor;
}
    
