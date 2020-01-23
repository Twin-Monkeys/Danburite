#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/ModelCamera_Header.glsl"

out vec3 worldPos;
out vec4 color;
out vec3 worldNormal;
out vec2 texCoord;

void main()
{
	worldPos = Model_getWorldPosition(VertexAttribute_modelMat, VertexAttribute_pos);
	color = VertexAttribute_color;
	worldNormal = Model_getWorldNormal(VertexAttribute_modelMat, VertexAttribute_normal);
	texCoord = VertexAttribute_texCoord;

	gl_Position = ModelCamera_getNDCPosition(VertexAttribute_modelMat, VertexAttribute_pos);
} 