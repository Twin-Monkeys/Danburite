#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/ModelCamera_Header.glsl"

out vec3 worldPos;
out vec4 color;
out vec3 worldNormal;
out vec2 texCoord;
out mat3 TBN;

void main()
{
	worldPos = Model_getWorldPosition(VertexAttribute_modelMat, VertexAttribute_pos);
	color = VertexAttribute_color;
	worldNormal = Model_getWorldNormal(VertexAttribute_modelMat, VertexAttribute_normal);
	texCoord = VertexAttribute_texCoord;

	const vec3 T = Model_getWorldNormal(VertexAttribute_modelMat, VertexAttribute_tangent);
	const vec3 B = cross(worldNormal, T);
	TBN = mat3(T, B, worldNormal);

	gl_Position = ModelCamera_getNDCPosition(VertexAttribute_modelMat, VertexAttribute_pos);
} 