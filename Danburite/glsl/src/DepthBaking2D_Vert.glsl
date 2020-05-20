#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/DepthBaking2D_Header.glsl"
#include "header/Material_Header.glsl"
#include "header/Bone_Header.glsl"

void main()
{
	vec3 localPos = VertexAttribute_pos;

	if (Material_isVertexBoneEnabled())
		localPos = (Bone_getBoneMatrix(VertexAttribute_boneIndices, VertexAttribute_boneWeights) * vec4(localPos, 1.f)).xyz;

	gl_Position = DepthBaking2D_getNDCPosition(VertexAttribute_modelMat, VertexAttribute_pos);
} 