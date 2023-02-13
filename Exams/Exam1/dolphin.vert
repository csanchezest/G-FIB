#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;
uniform float time;
const float PI = 3.1416;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(0.8) * N.z;
    mat4 rot;
    float theta;
    vec4 desp = vec4(0,0,0,1);
    mat4 trans, inv;
    float smth;
    float rangey = boundingBoxMax.y - boundingBoxMin.y, y = (vertex.y-boundingBoxMin.y)/rangey;
    vec4 vtexTrans;
    if(vertex.y > 0) {
	if(mod(int(floor(time)),2)==1) theta = ((1 - fract(time)) * 2 - 1) * (PI/32);
	else theta = (fract(time) * 2 - 1) * (PI/32);
	theta = 2*PI*time + theta;
	rot = mat4(vec4(1,0,0,0),vec4(0,cos(theta),sin(theta),0),vec4(0,-sin(theta),cos(theta),0),vec4(0,0,0,1));
    	desp = vec4(vec3(0,-(vertex.y+0.15),0),1.);
	smth = smoothstep(vertex.y, vtexTrans.y, y);
	vtexTrans = vec4(vtexTrans.x, y, vtexTrans.z, vtexTrans.w);
    }
    else if(vertex.y <= 0 && time>=0.25) {
	if(mod(int(floor(time)),2)==1) theta = fract(time) * (-PI/4);
	else theta = (fract(time) - 1) * (PI/4);
	theta = 2*PI*time + theta;
	rot = mat4(vec4(1,0,0,0),vec4(0,cos(theta),sin(theta),0),vec4(0,-sin(theta),cos(theta),0),vec4(0,0,0,1));
	//rot *= -1.;
    	desp = vec4(vec3(0,-(vertex.y-0.15),0),1.);
    	inv = inverse(trans);
    	vtexTrans = inv * rot * trans vec4(vertex, 1.0);
	smth = smoothstep(vertex.y, vtexTrans.y, y);
	vtexTrans = vec4(vtexTrans.x, y, vtexTrans.z, vtexTrans.w);
    }
    trans = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),desp);
    inv = inverse(trans);
    vtexCoord = texCoord;
    vtexTrans = inv * rot * trans vec4(vertex, 1.0);
    gl_Position = modelViewProjectionMatrix * vtexTrans;
}
