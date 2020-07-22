#version 460 core

#include "header/PostProcess_Header.glsl"
#include "header/Bloom_Header.glsl"
#include "header/Grayscale_Header.glsl"

out vec4 extractedColor;

void main()
{
	const vec3 originalColor = PostProcess_getRectPixel(0, gl_FragCoord.xy).rgb;
	const float grayscaledColor = Grayscale_getGrayscaledColor(originalColor);

	if (grayscaledColor > Bloom_getBrightnessThreshold())
		extractedColor = vec4(originalColor, 1.f);
	else
		extractedColor = vec4(0.f, 0.f, 0.f, 1.f);
}