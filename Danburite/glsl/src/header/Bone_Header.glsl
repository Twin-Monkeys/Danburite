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

mat4 Bone_getBoneMatrix(const vec4 boneIndices, const vec4 boneWeights)
{
	mat4 retVal = mat4(0.f);

	bool noBones = true;
	for (uint i = 0U; i < 4U; i++)
	{
		const float boneWeight = boneWeights[i];
		if (boneWeight > EPSILON)
			noBones = false;

		const uint boneIndex = uint(boneIndices[i]);

		retVal += (bone.boneMatrices[boneIndex] * boneWeight);
	}

	if (noBones)
		return mat4(1.f);

	return retVal;
}

#endif