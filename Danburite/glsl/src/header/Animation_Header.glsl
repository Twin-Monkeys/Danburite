//? #version 460 core

#ifndef __ANIMATION_HEADER__
#define __ANIMATION_HEADER__

#include "Constant_Header.glsl"

struct Animation
{
	mat4 boneMatrices[MAX_NUM_BONES];
};

layout(binding = BINDING_POINT_ANIMATION) uniform UBAnimation
{
	Animation animation;
};

vec3 Animation_getAnimatedPosition(const vec3 localPos, const vec4 boneIndices, const vec4 boneWeights)
{
	mat4 boneMat = mat4(0.f);

	for (uint i = 0U; i < 4U; i++)
	{
		const float boneWeight = boneWeights[i];
		if (boneWeight < EPSILON)
			break;

		const uint boneIndex = uint(boneIndices[i]);
		boneMat += (animation.boneMatrices[boneIndex] * boneWeight);
	}

	return (boneMat * vec4(localPos, 1.f)).xyz;
}

#endif