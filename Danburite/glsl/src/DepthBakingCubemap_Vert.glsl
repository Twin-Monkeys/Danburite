#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/Model_Header.glsl"

void main()
{
	gl_Position = vec4(
		Model_getWorldPosition(VertexAttribute_modelMat, VertexAttribute_pos), 1.f);
} 