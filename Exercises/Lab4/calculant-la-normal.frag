#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 vtx;

void main()
{
    //el vertex s'ha de trobar en coordenades de camera (Eye space)
    vec3 prod = normalize(cross(dFdx(vtx),dFdy(vtx)));
    //recordar que sempre es la component z
    fragColor = frontColor * prod.z;
    //fragColor = frontColor;
}
