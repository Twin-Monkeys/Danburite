#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/Model_Header.glsl"
#include "header/Animation_Header.glsl"

void main()
{
	const mat4 modelMat =
		Animation_getAnimatedModelMatrix(VertexAttribute_modelMat, VertexAttribute_boneIndices, VertexAttribute_boneWeights);

	gl_Position.xyz = Model_getWorldPosition(modelMat, VertexAttribute_pos);
	gl_Position.w = 1.f;
} 