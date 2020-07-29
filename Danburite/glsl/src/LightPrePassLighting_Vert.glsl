#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/ModelCamera_Header.glsl"
#include "header/Animation_Header.glsl"

void main()
{
	const mat4 modelMat =
		Animation_getAnimatedModelMatrix(VertexAttribute_modelMat, VertexAttribute_boneIndices, VertexAttribute_boneWeights);

	gl_Position = ModelCamera_getNDCPosition(modelMat, VertexAttribute_pos);

	// To prevent clipping light volume
	gl_Position.z = 0.f;
} 