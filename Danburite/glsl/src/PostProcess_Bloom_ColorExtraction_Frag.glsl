#version 460 core

#include "header/TextureContainer_Header.glsl"
#include "header/Bloom_Header.glsl"
#include "header/Grayscale_Header.glsl"

out vec3 extractedColor;

void main()
{
	const sampler2DRect srcTex = TextureContainer_getTextureAs2DRect(0);
	
	const vec3 originalColor = texelFetch(srcTex, ivec2(gl_FragCoord.xy)).rgb;
	const float grayscaledColor = Grayscale_getGrayscaledColor(originalColor);

	const float extractingFactor = (4.5f * clamp(grayscaledColor - Bloom_getBrightnessThreshold(), 0.f, 1.f));
	extractedColor = (extractingFactor * originalColor);
}