#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform sampler2D colormap;

in vec2 vtexCoord;

void main()
{
    fragColor = frontColor;
    vec2 tex = vec2(vtexCoord.x * 10, vtexCoord.y * 10);
    float x = floor(tex.x);
    float y = floor(tex.y);
    
    float ntcx = fract(vtexCoord.s*10);
    float ntcy = fract(vtexCoord.t*10);
    vec2 ship = vec2(ntcx/4 + 3./4., ntcy/4 + 1./4.);
    vec2 phantom = vec2(ntcx/4, ntcy/4);
    vec2 shield = vec2(ntcx/4 + 3./4., ntcy/4); 
    vec2 alien1 = vec2(ntcx/4, ntcy/4); 
    vec2 alien2 = vec2(ntcx/4 + 1./4., ntcy/4); 
    vec2 alien3 = vec2(ntcx/4 + 2./4., ntcy/4); 
    vec2 alien4 = vec2(ntcx/4 + 3./4., ntcy/4 + 2./4.); 
    vec2 alien5 = vec2(ntcx/4 + 1./4., ntcy/4 + 1./4.); 
    vec2 alien6 = vec2(ntcx/4 + 2./4., ntcy/4 + 1./4.); 
    if(y==1. && x == 3.) fragColor = texture(colormap, ship);
    else if(y==2. && (x==2. || x==4. || x==6. || x==8.)) fragColor = texture(colormap, shield);
    else if(y == 3. && (x >= 1. && x <= 8.)) fragColor = texture(colormap, alien1);
    else if(y == 4. && (x >= 1. && x <= 8.)) fragColor = texture(colormap, alien2);
    else if(y == 5. && (x >= 1. && x <= 8.)) fragColor = texture(colormap, alien3);
    else if(y == 6. && (x >= 1. && x <= 8.)) fragColor = texture(colormap, alien4);
    else if(y == 7. && (x >= 1. && x <= 8.)) fragColor = texture(colormap, alien5);
    else if(y == 8. && (x >= 1. && x <= 8.)) fragColor = texture(colormap, alien6);
    //else if(y == 9. && (x >= 1. && x <= 9.)) fragColor = texture(colormap, shield);
    else fragColor = vec4(0.);
}
