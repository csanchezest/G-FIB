#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
const float speed = 0.5;
in vec3 vnormal[];
uniform float time;

void main( void )
{
	vec3 n = (vnormal[0]+vnormal[1]+vnormal[2])/3;
	//n = normalize(n);
	mat4 trans = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(speed*time*n.xyz,1));
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * trans * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
