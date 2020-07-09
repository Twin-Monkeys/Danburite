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
	// #Kernels: 29
	// Sigma: 5
	const float kernels[(NUM_BLOOM_BLUR_KERNELS + 1) / 2] = float[] (
		.079954f, .078376f, .073827f, .066823f, .058120f,
		.048575f, .039011f, .030106f, .022325f, .015908f,
		.010893f, .007167f, .004531f, .002753f, .001607f);

	return kernels[idx];
}

#endif