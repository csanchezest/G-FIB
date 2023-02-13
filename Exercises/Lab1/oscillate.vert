#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform mat4 modelViewMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform float time;
const float PI = 3.141592;
uniform bool eyespace;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    float y = vertex.y;
    if(eyespace) y = (modelViewMatrix * vec4(vertex,1.0)).y;
    vec3 diag = boundingBoxMax - boundingBoxMin;
    float r = length(diag)/2;
    float d = (r)/10*y;
    //ATENCIO: a l'enunciat diu que el periode es 2*pi, per tant la frequencia seria 1/(2*pi), per tant fariem 2*pi*(1/(2*pi))*temps i per tant ens queda nomes el temps
    float sinVal = d*sin(time);
    gl_Position = modelViewProjectionMatrix * vec4(vertex + normal*vec3(sinVal), 1.0);
}
