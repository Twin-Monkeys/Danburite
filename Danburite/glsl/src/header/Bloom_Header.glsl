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
	// #Kernels: 59
	// Sigma: 11
	const float kernels[(NUM_BLOOM_BLUR_KERNELS + 1) / 2] = float[] (
		.036522f, .036372f, .035924f, .035190f, .034187f,
		.032940f, .031477f, .029832f, .028040f, .026139f,
		.024167f, .022160f, .020152f, .018175f, .016258f,
		.014423f, .012690f, .011073f, .009583f, .008225f,
		.007002f, .005911f, .004950f, .004110f, .003385f,
		.002765f, .002240f, .001800f, .001434f, .001133f);

	return kernels[idx];
}

#endif