#version 460 core
layout(early_fragment_tests) in;

#include "header/Cubemap_Header.glsl"
 
in vec3 texCoord;

out vec4 fragColor;

void main()
{
	fragColor = Cubemap_getAlbedo(texCoord);
} 