#include "AttachableTexture.h"

namespace ObjectGL
{
	void AttachableTexture::_onAttach(const AttachmentType type) noexcept
	{
		assert(!getHandle());
		glFramebufferTexture2D(GL_FRAMEBUFFER, GLenum(type), _RAW_TYPE, ID, 0);

		assert(glGetError() == GL_NO_ERROR);
	}

	void AttachableTexture::_onDetach(const AttachmentType type) noexcept
	{
		assert(!getHandle());
		glFramebufferTexture2D(GL_FRAMEBUFFER, GLenum(type), _RAW_TYPE, 0, 0);

		assert(glGetError() == GL_NO_ERROR);
	}

	void AttachableTexture::memoryAlloc(
		const GLsizei width, const GLsizei height,
		const TextureInternalFormatType internalFormat, const TextureExternalFormatType externalFormat,
		const TextureDataType dataType) noexcept
	{
		memoryAlloc(width, height, nullptr, internalFormat, externalFormat, dataType, 0, false);
	}
}