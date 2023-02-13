#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

void main()
{
    float x = vtexCoord.x, y = vtexCoord.y;
    if((x < 0.1 || x > 0.9) || (y < 0.2 || y > 0.8)) fragColor = vec4(0,1,0,1);
    else { 
   	vec2 res = vec2(abs(vtexCoord.x*2-1),abs(vtexCoord.y-0.5));
    	float d = length(res);
	vec4 color = vec4(1,1,0,1);
	//vec4 color1, color2, color3;
   	//vec2 res1 = vec2(abs(vtexCoord.x*2-1.1),abs(vtexCoord.y-0.6));
    	//float d1 = length(res1);
    	color = mix(vec4(0,0,1,0),color,step(0.2, d)); 
	//color2 = mix(vec4(1,1,0,0),color1,step(0.2, d1));
	fragColor = color; 
    }
}
