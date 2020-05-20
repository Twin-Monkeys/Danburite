#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/Model_Header.glsl"
#include "header/Material_Header.glsl"
#include "header/Animation_Header.glsl"

void main()
{
	vec3 localPos = VertexAttribute_pos;

	if (Material_isVertexBoneEnabled())
		localPos = Animation_getAnimatedPosition(localPos, VertexAttribute_boneIndices, VertexAttribute_boneWeights);

	gl_Position = vec4(Model_getWorldPosition(VertexAttribute_modelMat, localPos), 1.f);
} 