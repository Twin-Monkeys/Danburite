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

#endif