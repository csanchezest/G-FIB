#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D colorMap;
in vec2 vtexCoord;
uniform float time;

// punt interior a cercle
bool inCircle(vec2 p, vec2 c, float r)
{
	return (distance(p, c) <= r);
}

// punt interior a rectangle
bool inRect(vec2 p, vec2 m, vec2 M)
{
	return  (p.x >= m.x && p.x <= M.x) && (p.y >= m.y && p.y <= M.y);
}

void main()
{
    float val = vtexCoord.s;
    float ntc = fract(val*6.);
    float v_4 = ntc/10 + 0.4;
    float v_7 = ntc/10 + 0.7;
    float v_9 = ntc/10 + 0.9;
    float v_2 = ntc/10 + 0.2;
    float coord = int(floor(vtexCoord.s*6));
    if(coord == 0) fragColor = texture(colorMap, vec2(v_4,vtexCoord.t));
    else if(coord==1) fragColor = texture(colorMap, vec2(v_7,vtexCoord.t));
    else if(coord==2) fragColor = texture(colorMap, vec2(v_9,vtexCoord.t));
    else if(coord==3) fragColor = texture(colorMap, vec2(v_7,vtexCoord.t));
    else if(coord==4) fragColor = texture(colorMap, vec2(v_2,vtexCoord.t));
    else fragColor = texture(colorMap, vec2(v_2,vtexCoord.t));
    fragColor.rgb = vec3(0,0,1);
    
    if(fragColor.a<0.5) discard;

}

