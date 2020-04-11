#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/DepthBaking2D_Header.glsl"

void main()
{
	gl_Position = DepthBaking2D_getNDCPosition(VertexAttribute_modelMat, VertexAttribute_pos);
} 