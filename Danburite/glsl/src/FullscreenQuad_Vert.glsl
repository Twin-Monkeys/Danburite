#version 460 core

#define VariableInOut_Vert_exportToFrag_texCoord
#include "header/VariableInOut_Vert_Header.glsl"
#include "header/Fullscreen_Header.glsl"
/*
	It needs to call dummy draw command with empty VBO likes:

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 6);
*/
void main()
{
	const vec2 texCoord = Fullscreen_getTexCoord(gl_VertexID);

	variableInOut_VertToFrag.texCoord = texCoord;
    gl_Position = Fullscreen_getPosition(texCoord);
}