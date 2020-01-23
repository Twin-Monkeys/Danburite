#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/ModelCamera_Header.glsl"

out vec3 worldPos;
out vec3 worldNormal;

void main()
{
	worldPos = Model_getWorldPosition(VertexAttribute_modelMat, VertexAttribute_pos);
	worldNormal = Model_getWorldNormal(VertexAttribute_modelMat, VertexAttribute_normal);

	gl_Position = ModelCamera_getNDCPosition(VertexAttribute_modelMat, VertexAttribute_pos);
} 