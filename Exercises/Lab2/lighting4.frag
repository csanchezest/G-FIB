#version 330 core


in vec4 frontColor;
out vec4 fragColor;

in vec4 fragVertex;
in vec3 fragNormal;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

//posicio llum
uniform vec4 lightPosition;
//llum ambient
uniform vec4 lightAmbient;
//llum ambient
uniform vec4 lightDiffuse;
//llum ambient
uniform vec4 lightSpecular;

//reflectivitat ambient
uniform vec4 matAmbient;
//reflectivitat difosa
uniform vec4 matDiffuse;
//reflectivitat especular
uniform vec4 matSpecular;
//brillantesa
uniform float matShininess;

void main()
{
    vec4 eyeVertex = modelViewMatrix * fragVertex;
    vec3 N = normalize(normalMatrix * fragNormal);
    vec3 L = normalize(lightPosition.xyz - eyeVertex.xyz);
    vec3 V = normalize((-eyeVertex).xyz);
    vec3 R = normalize(2 * dot(N,L) * N-L);
    if(dot(N,L) < 0) fragColor = matAmbient * lightAmbient + matDiffuse * lightDiffuse * max(0.0,dot(N,L));
    else fragColor = matAmbient * lightAmbient + matDiffuse * lightDiffuse * max(0.0,dot(N,L)) + matSpecular * lightSpecular * pow(max(0.0,dot(R,V)),matShininess);
}
