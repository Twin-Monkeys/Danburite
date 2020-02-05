#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/ModelCamera_Header.glsl"

void main()
{
	gl_Position = ModelCamera_getNDCPosition(VertexAttribute_modelMat, VertexAttribute_pos);
} 