#version 460 core

#include "header/Material_Header.glsl"

layout(early_fragment_tests) in;
 
out vec4 fragColor;

void main()
{
	float linearDepth = Material_getLinearDepth(gl_FragCoord.z);
	fragColor = vec4(vec3(linearDepth), 1.f);
} 