#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main()
{

    vec3 red = vec3(1,0,0);
    vec3 yellow = vec3(1,1,0);
    vec3 green = vec3(0,1,0);
    vec3 cian = vec3(0,1,1);
    vec3 blue = vec3(0,0,1);
    float top = boundingBoxMax.y, bot = boundingBoxMin.y, y = vertex.y;
    float total_range = top - bot;
    if(y <= bot) frontColor = vec4(red,1.0);
    else if(y < bot + total_range/4) frontColor = vec4(mix(red,yellow,fract((y-bot)/(total_range/4))),1.0);
    else if(y < bot + total_range/2) frontColor = vec4(mix(yellow,green,fract((y-(bot+total_range/4))/(total_range/4))),1.0);
    else if(y < bot + 3*total_range/4) frontColor = vec4(mix(green,cian,fract((y-(bot+total_range/2))/(total_range/4))),1.0);
    else if(y < bot + total_range) frontColor = vec4(mix(cian,blue,fract((y-(bot+3*total_range/4))/(total_range/4))),1.0);
    else frontColor = vec4(blue,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
