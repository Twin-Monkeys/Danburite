#version 460 core

#include "header/VertexAttribute_Header.glsl"

out vec2 texCoord;

void main()
{
	texCoord = VertexAttribute_texCoord;
	gl_Position = vec4(VertexAttribute_pos, 1.f);
} 