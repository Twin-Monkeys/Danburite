#version 460 core

#define VariableInOut_Vert_exportToFrag_texCoord
#include "header/VariableInOut_Vert_Header.glsl"

/*
	It needs to call dummy draw command with empty VBO likes:

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 6);
*/
void main()
{
	vec2 texCoord;
	texCoord.x = float(((gl_VertexID + 2) / 3) % 2);
    texCoord.y = float(((gl_VertexID + 1) / 3) % 2);

	variableInOut_VertToFrag.texCoord = texCoord;
    gl_Position = vec4(-1.f + (texCoord.x * 2.f), -1.f + (texCoord.y * 2.f), 0.f, 1.f);
}