#version 460 core

#include "header/PostProcess_Header.glsl"
#include "header/Bloom_Header.glsl"
#include "header/Grayscale_Header.glsl"

out vec3 extractedColor;

void main()
{
	const vec3 originalColor = PostProcess_getRectPixel(0, gl_FragCoord.xy).rgb;
	const float grayscaledColor = Grayscale_getGrayscaledColor(originalColor);

	if (grayscaledColor > Bloom_getBrightnessThreshold())
		extractedColor = originalColor;
	else
		extractedColor = vec3(0.f, 0.f, 0.f);
}