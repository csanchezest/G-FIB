#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
in vec2 vtexCoord[];
out vec2 gtexCoord;

uniform float time;
uniform mat4 modelViewProjectionMatrix;

void main( void )
{
	vec4 center;
	if(gl_PrimitiveIDIn == 0) center = vec4(-1.,-1.,-1.,1.);
	else if(gl_PrimitiveIDIn == 1) center = vec4(1.,-1.,-1.,1.);
	else if(gl_PrimitiveIDIn == 2) center = vec4(-1.,1.,-1.,1.);
	else if(gl_PrimitiveIDIn == 3) center = vec4(1.,1.,-1.,1.);
	else if(gl_PrimitiveIDIn == 4) center = vec4(-1.,-1.,1.,1.);
	else if(gl_PrimitiveIDIn == 5) center = vec4(1.,-1.,1.,1.);
	else if(gl_PrimitiveIDIn == 6) center = vec4(-1.,1.,1.,1.);
	else if(gl_PrimitiveIDIn == 7) center = vec4(1.,1.,1.,1.);
	if(gl_PrimitiveIDIn < 4) {
		mat4 rot = mat4(vec4(cos(time),sin(time),0,0),vec4(-sin(time),cos(time),0,0),vec4(0,0,1,0),vec4(0,0,0,1));
		vec4 p1 = center + vec4(-1.,-1.,-1.,0.);
		vec4 p2 = center + vec4(1.,-1.,-1.,0.);
		vec4 p3 = center + vec4(1.,-1.,1.,0.);
		vec4 p4 = center + vec4(-1.,-1.,1.,0.);
		vec4 p5 = center + vec4(-1.,1.,-1.,0.);
		vec4 p6 = center + vec4(1.,1.,-1.,0.);
		vec4 p7 = center + vec4(1.,1.,1.,0.);
		vec4 p8 = center + vec4(-1.,1.,1.,0.);
		//base	
		gl_Position = modelViewProjectionMatrix*rot*p1; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p2; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(1.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p3; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*rot*p1; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p3; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p4; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(0.,1.); EmitVertex();
    		EndPrimitive();
		//cap		
		gl_Position = modelViewProjectionMatrix*rot*p5; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p6; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(1.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p7; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*rot*p5; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p7; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p8; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(0.,1.); EmitVertex();
    		EndPrimitive();
		//lateral esquerre		
		gl_Position = modelViewProjectionMatrix*rot*p1; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p8; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p5; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(0.,1.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*rot*p1; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p4; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(1.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p8; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
    		EndPrimitive();
		//lateral dret	
		gl_Position = modelViewProjectionMatrix*rot*p6; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p7; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(0.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p2; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(1.,0.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*rot*p7; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(0.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p3; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p2; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(1.,0.);  EmitVertex();
    		EndPrimitive();
		//lateral darrere	
		gl_Position = modelViewProjectionMatrix*rot*p5; gfrontColor = vec4(1); gtexCoord = vec2(0.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p6; gfrontColor = vec4(1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p2; gfrontColor = vec4(1); gtexCoord = vec2(1.,0.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*rot*p1; gfrontColor = vec4(1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p5; gfrontColor = vec4(1); gtexCoord = vec2(0.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p2; gfrontColor = vec4(1); gtexCoord = vec2(1.,0.); EmitVertex();
    		EndPrimitive();
		//lateral davant
		gl_Position = modelViewProjectionMatrix*rot*p8; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(0.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p4; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p3; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(1.,0.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*rot*p3; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(1.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p7; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*rot*p8; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(0.,1.); EmitVertex();
    		EndPrimitive();
	}
	else if(gl_PrimitiveIDIn < 8) {
		vec4 p1 = center + vec4(-1.,-1.,-1.,0.);
		vec4 p2 = center + vec4(1.,-1.,-1.,0.);
		vec4 p3 = center + vec4(1.,-1.,1.,0.);
		vec4 p4 = center + vec4(-1.,-1.,1.,0.);
		vec4 p5 = center + vec4(-1.,1.,-1.,0.);
		vec4 p6 = center + vec4(1.,1.,-1.,0.);
		vec4 p7 = center + vec4(1.,1.,1.,0.);
		vec4 p8 = center + vec4(-1.,1.,1.,0.);
		//base	
		gl_Position = modelViewProjectionMatrix*p1; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p2; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(1.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p3; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*p1; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p3; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p4; gfrontColor = vec4(1,0.6,0,1); gtexCoord = vec2(0.,1.); EmitVertex();
    		EndPrimitive();
		//cap		
		gl_Position = modelViewProjectionMatrix*p5; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p6; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(1.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p7; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*p5; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p7; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p8; gfrontColor = vec4(1,0,0,1); gtexCoord = vec2(0.,1.); EmitVertex();
    		EndPrimitive();
		//lateral esquerre		
		gl_Position = modelViewProjectionMatrix*p1; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p8; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p5; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(0.,1.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*p1; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p4; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(1.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p8; gfrontColor = vec4(0,1,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
    		EndPrimitive();
		//lateral dret	
		gl_Position = modelViewProjectionMatrix*p6; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p7; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(0.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p2; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(1.,0.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*p7; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(0.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p3; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p2; gfrontColor = vec4(0,0,1,1); gtexCoord = vec2(1.,0.);  EmitVertex();
    		EndPrimitive();
		//lateral darrere	
		gl_Position = modelViewProjectionMatrix*p5; gfrontColor = vec4(1); gtexCoord = vec2(0.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p6; gfrontColor = vec4(1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p2; gfrontColor = vec4(1); gtexCoord = vec2(1.,0.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*p1; gfrontColor = vec4(1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p5; gfrontColor = vec4(1); gtexCoord = vec2(0.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p2; gfrontColor = vec4(1); gtexCoord = vec2(1.,0.); EmitVertex();
    		EndPrimitive();
		//lateral davant
		gl_Position = modelViewProjectionMatrix*p8; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(0.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p4; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(0.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p3; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(1.,0.); EmitVertex();
    		EndPrimitive();
		gl_Position = modelViewProjectionMatrix*p3; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(1.,0.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p7; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(1.,1.); EmitVertex();
		gl_Position = modelViewProjectionMatrix*p8; gfrontColor = vec4(1,1,0,1); gtexCoord = vec2(0.,1.); EmitVertex();
    		EndPrimitive();
	}
}
