//? #version 460 core

#ifndef __CONVOLUTIONAL_HEADER__
#define __CONVOLUTIONAL_HEADER__

#include "Constant_Header.glsl"

struct Convolution
{
	float samplingOffset;
	uint kernelSize;
	float kernel[MAX_KERNEL_SIZE * MAX_KERNEL_SIZE];
};

layout(binding = BINDING_POINT_CONVOLUTION) uniform UBConvolution
{
	Convolution convolution;
};

vec4 Convolutional_convolve(sampler2D tex, const vec2 texCoord)
{
	const float edgeDetectingKernel3x3[] =
		{
			1.f, 1.f, 1.f,
			1.f, -8.f, 1.f,
			1.f, 1.f, 1.f
		};

	const int KERNEL_SIZE = int(convolution.kernelSize);
	const int KERNEL_SIZE_HALF = (KERNEL_SIZE / 2);

	const int NUM_KERNEL_ELEMS = (KERNEL_SIZE * KERNEL_SIZE);

	vec3 retVal = vec3(0.f);
	for (int i = 0; i < NUM_KERNEL_ELEMS; i++)
	{
		const float S_OFFSET =
		(((i % KERNEL_SIZE) - KERNEL_SIZE_HALF) * convolution.samplingOffset);
		
		const float T_OFFSET =
		(((i / KERNEL_SIZE) - KERNEL_SIZE_HALF) * convolution.samplingOffset);

		vec3 pixel = texture(tex, texCoord + vec2(S_OFFSET, T_OFFSET)).rgb;
		retVal += (pixel * edgeDetectingKernel3x3[i]);
	}

	return vec4(retVal, texture(tex, texCoord).a);
}

#endif