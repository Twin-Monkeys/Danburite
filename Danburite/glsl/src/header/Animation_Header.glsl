//? #version 460 core

#ifndef __ANIMATION_HEADER__
#define __ANIMATION_HEADER__

#include "Material_Header.glsl"
#include "Joint_Header.glsl"
#include "Bone_Header.glsl"

mat4 Animation_getAnimatedModelMatrix(const mat4 modelMat, const vec4 boneIndices, const vec4 boneWeights)
{
	mat4 retVal = (modelMat * Joint_getJointMatrix());

	if (Material_isVertexBoneEnabled())
		retVal *= Bone_getBoneMatrix(boneIndices, boneWeights);

	return retVal;
}

#endif