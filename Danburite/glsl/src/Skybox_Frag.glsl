#version 460 core

#include "header/Skybox_Header.glsl"
 
in vec3 texCoord;

out vec4 fragColor;

void main()
{
	fragColor = Skybox_getAlbedo(texCoord);
} 