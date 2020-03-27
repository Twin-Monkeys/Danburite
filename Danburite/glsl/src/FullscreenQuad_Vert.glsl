#version 460 core

out vec2 texCoord;

/*
	It needs to call dummy draw command with empty VBO likes:

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 6);
*/
void main()
{
	texCoord.x = float(((gl_VertexID + 2) / 3) % 2);
    texCoord.y = float(((gl_VertexID + 1) / 3) % 2);

    gl_Position = vec4(-1.f + (texCoord.x * 2.f), -1.f + (texCoord.y * 2.f), 0.f, 1.f);
}