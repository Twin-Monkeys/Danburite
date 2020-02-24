#include "RenderBufferMultisample.h"
#include <cassert>

namespace ObjectGL
{
	void RenderBufferMultisample::memoryAlloc(
		const GLsizei width, const GLsizei height,
		const RenderBufferInternalFormatType internalFormat, const GLsizei numSamplePoints) noexcept
	{
		bind();

		glRenderbufferStorageMultisample(
			GL_RENDERBUFFER, numSamplePoints, GLenum(internalFormat), width, height);

		assert(glGetError() == GL_NO_ERROR);
	}
}