#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
	mat4 trans = mat4(vec4(1,0,0,0),vec4(0,1,0,0),vec4(0,0,1,0),vec4(0,boundingBoxMin.y,0,1));
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0);
		gl_Position = modelViewProjectionMatrix * trans * (gl_in[i].gl_Position * vec4(1,0.0001,1,1));
		EmitVertex();
	}
    EndPrimitive();
}
