#include "AssertException.h"
#include <GL/glew.h>

using namespace std;

namespace ObjectGL
{
	AssertException::AssertException(char const* const _Message) noexcept :
		exception(_Message)
	{}

	void AssertException::test(const bool expression)
	{
#ifndef NDEBUG
		if (!expression)
			throw AssertException();
#endif
	}

	void AssertException::fail()
	{
		test(false);
	}

	void AssertException::glErrorTest()
	{
		test(glGetError() == GL_NO_ERROR);
	}
}