#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform bool classic = false;

const float PI = 3.141592;

void main()
{

    if(classic) {
      vec2 res = vec2(abs(vtexCoord.x-0.5),abs(vtexCoord.y-0.5));
      float d = length(res);
      fragColor = mix(vec4(1,0,0,0),vec4(1,1,1,0),step(0.2, d)); 
    } else {
      vec2 res = vec2(abs(vtexCoord.x-0.5),abs(vtexCoord.y-0.5));
      float d = length(res);
      if(d<=0.2) fragColor = mix(vec4(1,0,0,0),vec4(1,1,1,0),step(0.2, d)); 
      else { 
        vec2 u = vec2(vtexCoord.x - 0.5, vtexCoord.y - 0.5);
        float phi = atan(u.x, u.y);
        float theta = PI/16;
        fragColor = mix(vec4(1,0,0,0),vec4(1,1,1,0),step(1, mod(phi/theta + 0.5,2))); 
      }
    }
}
