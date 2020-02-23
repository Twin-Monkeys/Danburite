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
	}

	Shader::~Shader() noexcept
	{
		__release();
	}
}