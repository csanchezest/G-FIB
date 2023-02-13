#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

void main()
{
    // vtexCoord necessaria per poder fer la interpolacio de les textures adientment; per treure les components xyz, necessitem fer texture(objecte de tipus Sampler2D, vector de 2 dimensions); amb aixo, es treu correctament els valors xyz segons la coordenada de vertex
    float r = texture(noise0, vtexCoord).x;
    vec4 textureRock = texture(rock1,vtexCoord), textureGrass = texture(grass2, vtexCoord);
    fragColor = vec4(mix(textureRock.xyz, textureGrass.xyz, r), 1.0);
    //fragColor = frontColor;
}
