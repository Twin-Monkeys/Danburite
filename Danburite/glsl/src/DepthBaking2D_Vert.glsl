#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/DepthBaking2D_Header.glsl"
#include "header/Animation_Header.glsl"

void main()
{
	const mat4 modelMat =
		Animation_getAnimatedModelMatrix(VertexAttribute_modelMat, VertexAttribute_boneIndices, VertexAttribute_boneWeights);

	gl_Position = DepthBaking2D_getNDCPosition(modelMat, VertexAttribute_pos);
} 