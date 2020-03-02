#version 460 core

#include "header/Cubemap_Header.glsl"
 
in vec3 texCoord;

out vec4 fragColor;

void main()
{
	fragColor = Cubemap_getAlbedo(texCoord);
} 