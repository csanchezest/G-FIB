#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 N;
in vec2 vtexCoord;

uniform float time;
uniform sampler2D window; 
uniform sampler2D palm1; 
uniform sampler2D background2;

void main()
{
    vec4 C = texture(window, vtexCoord);
    if(C.a < 1.0) {
	vec2 D = vtexCoord + 0.25*N.xy + vec2(0.1*sin(2*time)*vtexCoord.t,0);
	vec4 D1 = texture(palm1, D);
	if(D1.a >= 0.5) fragColor = D1;
	else {
		vec2 coords = vtexCoord + 0.5+N.xy;
		fragColor = texture(background2, vec2(coords.x/2, coords.y/2));
	}
    } else fragColor = C;
}
