#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;
uniform mat4 modelMatrix;
uniform mat4 modelMatrixInverse;

void main()
{
    float theta;
    if(vertex.y - 0.5 < 0) theta = 0.;
    else theta = (vertex.y - 0.5) * sin(time);
    mat4 rot = mat4(vec4(1,0,0,0),vec4(0,cos(theta),sin(theta),0),vec4(0,-sin(theta),cos(theta),0),vec4(0,0,0,1));
    vec4 desp = vec4(vec3(0,-1,0),1.);
    mat4 trans = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),desp);
    mat4 inv = inverse(trans);
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * inv * rot * trans * vec4(vertex, 1.0);
}
