#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform float step=0.1;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void cube(vec3 barycentre) {
	gfrontColor=vec4(0.8) * (normalMatrix * vec3(1,0,0)).z;
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,0.5,0.5)*step + barycentre,1);	//(i,j,k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,-0.5,0.5)*step + barycentre,1);	//(i,-j,k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,0.5,-0.5)*step + barycentre,1);	//(i,j,-k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,-0.5,-0.5)*step + barycentre,1);	//(i,-j,-k)
	EmitVertex();
	EndPrimitive();
	gfrontColor=vec4(0.8) * (normalMatrix * vec3(0,0,1)).z;
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,0.5,0.5)*step + barycentre,1);	//(i,j,k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,0.5,0.5)*step + barycentre,1);	//(-i,j,k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,-0.5,0.5)*step + barycentre,1);	//(i,-j,k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,-0.5,0.5)*step + barycentre,1);	//(-i,-j,k)
	EmitVertex();
	EndPrimitive();
	gfrontColor=vec4(0.8) * (normalMatrix * vec3(-1,0,0)).z;
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,0.5,0.5)*step + barycentre,1);	//(-i,j,k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,0.5,-0.5)*step + barycentre,1);	//(-i,j,-k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,-0.5,0.5)*step + barycentre,1);	//(-i,-j,k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,-0.5,-0.5)*step + barycentre,1);	//(-i,-j,-k)
	EmitVertex();
	EndPrimitive();
	gfrontColor=vec4(0.8) * (normalMatrix * vec3(0,0,-1)).z;
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,0.5,-0.5)*step + barycentre,1);	//(i,j,-k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,-0.5,-0.5)*step + barycentre,1);	//(i,-j,-k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,0.5,-0.5)*step + barycentre,1);	//(-i,j,-k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,-0.5,-0.5)*step + barycentre,1);	//(-i,-j,-k)
	EmitVertex();
	EndPrimitive();
	gfrontColor=vec4(0.8) * (normalMatrix * vec3(0,1,0)).z;
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,0.5,0.5)*step + barycentre,1);	//(i,j,k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,0.5,-0.5)*step + barycentre,1);	//(i,j,-k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,0.5,0.5)*step + barycentre,1);	//(-i,j,k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,0.5,-0.5)*step + barycentre,1);	//(-i,j,-k)
	EmitVertex();
	EndPrimitive();
	gfrontColor=vec4(0.8) * (normalMatrix * vec3(0,-1,0)).z;
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,-0.5,-0.5)*step + barycentre,1);	//(-i,-j,-k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,-0.5,-0.5)*step + barycentre,1);	//(i,-j,-k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(-0.5,-0.5,0.5)*step + barycentre,1);	//(-i,-j,k)
	EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(vec3(0.5,-0.5,0.5)*step + barycentre,1);	//(i,-j,k)
	EmitVertex();
	EndPrimitive();
}


void main( void )
{
	vec3 barycentre = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz)/3;
	barycentre /= step;
	barycentre = vec3(floor(barycentre.x), floor(barycentre.y), floor(barycentre.z));
	barycentre *= step;
	cube(barycentre);
}
