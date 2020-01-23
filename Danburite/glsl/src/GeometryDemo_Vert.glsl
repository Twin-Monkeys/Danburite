#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/ModelCamera_Header.glsl"

out VS_OUT
{
	vec3 color;
}
vs_out;

void main()
{
	gl_Position = ModelCamera_getNDCPosition(VertexAttribute_pos);
	vs_out.color = VertexAttribute_color.rgb;
} 