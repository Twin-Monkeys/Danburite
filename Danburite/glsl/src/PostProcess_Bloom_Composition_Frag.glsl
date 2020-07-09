#version 460 core

#define VariableInOut_Frag_importFromVert_texCoord
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/PostProcess_Header.glsl"
#include "header/Bloom_Header.glsl"

out vec4 fragColor;

void main()
{
	 const vec3 originalColor = PostProcess_getPixel(0, variableInOut_VertToFrag.texCoord).rgb;
	 const vec3 bloomColor = PostProcess_getPixel(1, variableInOut_VertToFrag.texCoord).rgb;

	 fragColor = vec4(originalColor + (bloomColor * Bloom_getEffectStrength()), 1.f);
} 