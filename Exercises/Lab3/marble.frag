#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 N;
in vec3 vrtx;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform vec4 ps = 0.3 * vec4(0,1,-1,0);
uniform vec4 pt = 0.3 * vec4(-2,-1,1,0);
uniform sampler2D noise;

vec4 shading(vec3 N, vec3 Pos, vec4 diffuse) {
 vec3 lightPos = vec3(0.0,0.0,2.0);
 vec3 L = normalize( lightPos - Pos );
 vec3 V = normalize( -Pos);
 vec3 R = reflect(-L,N);
 float NdotL = max( 0.0, dot( N,L ) );
 float RdotV = max( 0.0, dot( R,V ) );
 float Ispec = pow( RdotV, 20.0 );
 return diffuse * NdotL + Ispec;
}

void main()
{
    float s = dot(vec4(vrtx,1),ps);
    float t = dot(vec4(vrtx,1),pt);
    vec4 txt = texture(noise,vec2(s,t));
    float r = 2 * txt.r;
    vec4 color;
    if(r<1) color = mix(vec4(1,1,1,1), vec4(0.5,0.2,0.2,1),fract(r));
    else if(r<2) color = mix(vec4(0.5,0.2,0.2,1), vec4(1,1,1,1),fract(r));
    else color = vec4(1,1,1,1);
    fragColor = shading(normalize(normalMatrix * N), (modelViewMatrix * vec4(vrtx,1)).xyz, color);
}
