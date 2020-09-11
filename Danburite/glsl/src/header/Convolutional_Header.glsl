//? #version 460 core

#ifndef __CONVOLUTIONAL_HEADER__
#define __CONVOLUTIONAL_HEADER__

#include "Constant_Header.glsl"

layout(std140, binding = BINDING_POINT_CONVOLUTION) uniform UBConvolution
{
	layout(offset = 0) float kernel[MAX_KERNEL_SIZE][MAX_KERNEL_SIZE];
	layout(offset = (16U * MAX_KERNEL_SIZE * MAX_KERNEL_SIZE)) uint kernelSize;
}
convolution;

vec3 Convolutional_convolve(const sampler2DRect tex, const vec2 texCoord)
{
	const int KERNEL_SIZE = int(convolution.kernelSize);
	const int KERNEL_SIZE_HALF = (KERNEL_SIZE / 2);

	vec3 retVal = vec3(0.f);

	for (int tIter = 0; tIter < KERNEL_SIZE; tIter++)
	{
		const float T_OFFSET = (tIter - KERNEL_SIZE_HALF);

		for (int sIter = 0; sIter < KERNEL_SIZE; sIter++)
		{
			const float S_OFFSET = (sIter - KERNEL_SIZE_HALF);

			const vec3 pixel = texture(tex, texCoord + vec2(S_OFFSET, -T_OFFSET)).rgb;
			retVal += (pixel * convolution.kernel[tIter][sIter]);
		}
	}

	return retVal;
}

#endif