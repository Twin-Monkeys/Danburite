//? #version 460 core

#ifndef __ANIMATION_HEADER__
#define __ANIMATION_HEADER__

#include "Constant_Header.glsl"

struct Bone
{
	mat4 boneMatrices[MAX_NUM_BONES];
};

layout(binding = BINDING_POINT_BONE) uniform UBBone
{
	Bone bone;
};

vec3 Bone_getAnimatedPosition(const vec4 boneIndices, const vec4 boneWeights, const vec3 localPos)
{
	vec3 retVal = vec3(0.f);

	bool noBone = true;
	for (uint i = 0U; i < 4U; i++)
	{
		const float boneWeight = boneWeights[i];
		if (boneWeight < EPSILON)
			continue;

		noBone = false;
		const uint boneIndex = uint(boneIndices[i]);

		retVal += ((bone.boneMatrices[boneIndex] * vec4(localPos, 1.f)) * boneWeight).xyz;
	}

	if (noBone)
		retVal = localPos;

	return retVal;
}

vec3 Bone_getAnimatedNormal(const vec4 boneIndices, const vec4 boneWeights, const vec3 localNormal)
{
	vec3 retVal = vec3(0.f);

	bool noBone = true;
	for (uint i = 0U; i < 4U; i++)
	{
		const float boneWeight = boneWeights[i];
		if (boneWeight < EPSILON)
			continue;

		noBone = false;
		const uint boneIndex = uint(boneIndices[i]);

		retVal += ((transpose(inverse(mat3(bone.boneMatrices[boneIndex]))) * localNormal) * boneWeight);
	}

	if (noBone)
		retVal = localNormal;

	return retVal;
}

#endif