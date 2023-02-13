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
uniform float amp = 0.5;
uniform float freq = 0.25;
const float pi = 3.141592;

void main()
{
    float theta = amp * sin(2 * pi * freq * time + vertex.y);
    mat4 rot = mat4(vec4(1,0,0,0),vec4(0,cos(theta),sin(theta),0),vec4(0,-sin(theta),cos(theta),0),vec4(0,0,0,1));
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * rot * vec4(vertex, 1.0);
}
