#version 460 core

#include "header/PostProcess_Header.glsl"
 
in vec2 texCoord;
out vec4 fragColor;

void main()
{
	fragColor = PostProcess_getPixel(0, texCoord);
	const float avgColor = ((.2126f * fragColor.r) + (.7152f * fragColor.g) + (.0722f * fragColor.b));

	fragColor.rgb = vec3(avgColor);
} 