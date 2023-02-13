#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

void main()
{
    fragColor = frontColor;
    vec2 tex = vec2(vtexCoord.x * 5, vtexCoord.y * 7);
    float x = floor(tex.x);
    float y = floor(tex.y);
    if(y==6. && x == 1.) fragColor = vec4(0);
    else if(y==6. && x == 2.) fragColor = vec4(0);
    else if(y==6. && x == 3.) fragColor = vec4(0);
    else if(y==5. && x == 0.) fragColor = vec4(0);
    else if(y==5. && x == 4.) fragColor = vec4(0);
    else if(y==4. && x == 0.) fragColor = vec4(0);
    else if(y==3. && x == 0.) fragColor = vec4(0);
    else if(y==2. && x == 0.) fragColor = vec4(0);
    else if(y==1. && x == 0.) fragColor = vec4(0);
    else if(y==1. && x == 4.) fragColor = vec4(0);
    else if(y==0. && x == 1.) fragColor = vec4(0);
    else if(y==0. && x == 2.) fragColor = vec4(0);
    else if(y==0. && x == 3.) fragColor = vec4(0);
    else discard;
}
