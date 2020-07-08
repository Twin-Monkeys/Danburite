//? #version 460 core

#ifndef __BLOOM_HEADER__
#define __BLOOM_HEADER__

#include "Constant_Header.glsl"

struct Bloom
{
	float brightnessThreshold;
};

layout(binding = BINDING_POINT_BLOOM) uniform UBBloom
{
	Bloom bloom;
};

float Bloom_getBrightnessThreshold()
{
	return bloom.brightnessThreshold;
}

float Bloom_getBlurKernel(const uint idx)
{
	// Kernel size: 19
	const float kernels[] = float[] (
		0.132572f, 0.125472f, 0.106373f, 0.08078f, 0.05495f,
		0.033482f, 0.018275f, 0.008934f, 0.003912f, 0.001535f);

	return kernels[idx];
}

#endif