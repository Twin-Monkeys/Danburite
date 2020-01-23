#version 460 core

#include "header/VertexAttribute_Header.glsl"
#include "header/ModelCamera_Header.glsl"

out VsOut
{
	vec3 worldPos;
	vec4 color;
	vec3 worldNormal;
	vec2 texCoord;
}
vsOut;

void main()
{
	vsOut.worldPos = Model_getWorldPosition(VertexAttribute_pos);
	vsOut.color = VertexAttribute_color;
	vsOut.worldNormal = Model_getWorldNormal(VertexAttribute_normal);
	vsOut.texCoord = VertexAttribute_texCoord;

	gl_Position = ModelCamera_getNDCPosition(VertexAttribute_pos);
} 