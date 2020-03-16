#include "RenderBuffer.h"
#include <cassert>

namespace ObjectGL
{
	void RenderBuffer::memoryAlloc(
		const GLsizei width, const GLsizei height, const RenderBufferInternalFormatType internalFormat) noexcept
	{
		bind();

		glRenderbufferStorage(GL_RENDERBUFFER, GLenum(internalFormat), width, height);
	}
}
