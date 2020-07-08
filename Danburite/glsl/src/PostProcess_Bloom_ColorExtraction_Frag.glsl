#version 460 core

#define VariableInOut_Frag_importFromVert_texCoord
#include "header/VariableInOut_Frag_Header.glsl"

#include "header/PostProcess_Header.glsl"
#include "header/Bloom_Header.glsl"
#include "header/Grayscale_Header.glsl"

out vec4 extractedColor;

void main()
{
	const vec3 originalColor = PostProcess_getPixel(0, variableInOut_VertToFrag.texCoord).rgb;
	const float grayscaledColor = Grayscale_getGrayscaledColor(originalColor);

	if (grayscaledColor > Bloom_getBrightnessThreshold())
		extractedColor = vec4(originalColor, 1.f);
	else
		extractedColor = vec4(0.f, 0.f, 0.f, 1.f);
}