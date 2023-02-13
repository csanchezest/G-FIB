#version 330 core

in vec4 frontColor;
out vec4 fragColor;

//coordenades en espai de textura
in vec2 vtexCoord;

void main()
{  
    vec2 res = vec2(abs(vtexCoord.x-0.5),abs(vtexCoord.y-0.5));
    float d = length(res);
    fragColor = mix(vec4(1,0,0,0),vec4(1,1,1,0),step(0.2, d)); 
    //fragColor = mix(vec4(1,0,0,0),vec4(1,1,1,0),smoothstep(0.2-0.1,0.2+0.1, d)); 
}

