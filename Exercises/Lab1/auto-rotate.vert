#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float speed;
uniform float time;

void main()
{
    mat4 rot = mat4(vec4(cos(speed*time),0,-sin(speed*time),0),vec4(0,1,0,0),vec4(sin(speed*time),0,cos(speed*time),0),vec4(0,0,0,1));
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * rot * vec4(vertex, 1.0);
}
