#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/Model_Header.glsl"
#include "header/Material_Header.glsl"
#include "header/Bone_Header.glsl"

void main()
{
	vec3 localPos = VertexAttribute_pos;

	if (Material_isVertexBoneEnabled())
		localPos = (Bone_getBoneMatrix(VertexAttribute_boneIndices, VertexAttribute_boneWeights) * vec4(localPos, 1.f)).xyz;

	gl_Position = vec4(Model_getWorldPosition(VertexAttribute_modelMat, localPos), 1.f);
} 