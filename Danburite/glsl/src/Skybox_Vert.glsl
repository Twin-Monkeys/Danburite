#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/ModelCamera_Header.glsl"

out vec3 texCoord;

void main()
{
	texCoord = VertexAttribute_pos;

	vec4 ndcPosition =
		ModelCamera_getViewProjMatrixWithoutTranslation() * vec4(VertexAttribute_pos, 1.f);

	gl_Position = ndcPosition.xyww;
} 