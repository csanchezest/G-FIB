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
out vec3 N;

void main()
{
    N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    float scaleFactor = 0.5 + abs(sin(time));
    vec4 v = modelViewProjectionMatrix * vec4(vertex, 1.0);
    vec3 scaledVert = vec3(v.x/v.w, v.y/v.w, v.z/v.w);
    scaledVert.x *= scaleFactor;
    scaledVert.y *= scaleFactor;
    gl_Position = vec4(scaledVert,1);
}
