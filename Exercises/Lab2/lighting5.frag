#version 330 core


in vec4 frontColor;
out vec4 fragColor;

in vec4 fragVertex;
in vec3 fragNormal;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewMatrixInverse;

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

uniform bool world;

vec4 light(vec3 N, vec3 V, vec3 L) {
    N=normalize(N); V=normalize(V); L=normalize(L);
    vec3 R = normalize( 2.0*dot(N,L)*N-L );
    float NdotL = max( 0.0, dot( N,L ) );
    float RdotV = max( 0.0, dot( R,V ) );
    float Idiff = NdotL;
    float Ispec = 0;
    if (NdotL>0) Ispec=pow( RdotV, matShininess );
    return matAmbient * lightAmbient + matDiffuse * lightDiffuse * Idiff+ matSpecular * lightSpecular * Ispec;
}

void main()
{
    vec4 eyeVertex = modelViewMatrix * fragVertex;
    vec3 fragLight = lightPosition.xyz;
    vec3 N = normalize(normalMatrix * fragNormal);
    vec3 V = normalize((-eyeVertex).xyz);
    if(world) { 
        N = fragNormal;
        V = (modelViewMatrixInverse * vec4(0,0,0,1) - fragVertex).xyz;
        eyeVertex = fragVertex;
        fragLight = (modelViewMatrixInverse * lightPosition).xyz;
    }
    vec3 L = normalize(fragLight  - eyeVertex.xyz);
    fragColor = light(N,V,L);
}

