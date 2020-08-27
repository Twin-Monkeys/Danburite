//? #version 460 core

#ifndef __BONE_HEADER__
#define __BONE_HEADER__

#include "Constant_Header.glsl"

layout(std140, binding = BINDING_POINT_BONE) uniform UBBone
{
	layout(offset = 0) mat4 boneMatrices[MAX_NUM_BONES];
}
bone;

mat4 Bone_getBoneMatrix(const vec4 boneIndices, const vec4 boneWeights)
{
	mat4 retVal = mat4(0.f);

	for (uint i = 0U; i < 4U; i++)
	{
		const float boneWeight = boneWeights[i];
		if (boneWeight < EPSILON)
			break;

		const uint boneIndex = uint(boneIndices[i]);
		retVal += (bone.boneMatrices[boneIndex] * boneWeight);
	}

	return retVal;
}

#endif