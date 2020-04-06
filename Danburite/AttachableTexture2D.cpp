#include "AttachableTexture2D.h"

namespace ObjectGL
{
	void AttachableTexture2D::_onAttach(const AttachmentType type) noexcept
	{
		assert(!isHandleCreated());
		glFramebufferTexture2D(GL_FRAMEBUFFER, GLenum(type), _RAW_TYPE, ID, 0);
	}

	void AttachableTexture2D::_onDetach(const AttachmentType type) noexcept
	{
		assert(!isHandleCreated());
		glFramebufferTexture2D(GL_FRAMEBUFFER, GLenum(type), _RAW_TYPE, 0, 0);
	}

	void AttachableTexture2D::memoryAlloc(
		const GLsizei width, const GLsizei height,
		const TextureInternalFormatType internalFormat, const TextureExternalFormatType externalFormat,
		const TextureDataType dataType) noexcept
	{
		memoryAlloc(width, height, nullptr, internalFormat, externalFormat, dataType, 0, false);
	}
}