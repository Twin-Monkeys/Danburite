#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/ModelCamera_Header.glsl"
#include "header/Material_Header.glsl"

void main()
{
	vec3 scaledPos = (VertexAttribute_pos * material.thicknessRatio);
	gl_Position = ModelCamera_getNDCPosition(VertexAttribute_modelMat, scaledPos);
} 