#include "Shader.h"

namespace ObjectGL
{
	Shader::Shader(const GLuint id) noexcept :
		Object(id)
	{
		AssertException::test(id);
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