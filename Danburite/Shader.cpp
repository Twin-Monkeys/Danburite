#include "Shader.h"
#include <cassert>

namespace ObjectGL
{
	Shader::Shader(const GLuint id) noexcept :
		Object(id)
	{
		assert(id);
	}

	void Shader::__release() noexcept
	{
		glDeleteShader(ID);
		assert(glGetError() == GL_NO_ERROR);
	}

	Shader::~Shader() noexcept
	{
		__release();
	}
}