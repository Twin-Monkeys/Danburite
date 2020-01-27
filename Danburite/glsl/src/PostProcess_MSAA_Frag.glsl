#version 460 core

#include "header/MSAA_Header.glsl"
#include "header/Constant_Header.glsl"
 
in vec2 texCoord;
out vec4 fragColor;

void main()
{
	vec4 retVal = vec4(0.f);
	for (uint i = 0; i < NUM_SAMPLE_POINTS; i++)
		retVal += MSAA_getPixel(0, texCoord, int(i));

	fragColor = (retVal / float(NUM_SAMPLE_POINTS));
} 