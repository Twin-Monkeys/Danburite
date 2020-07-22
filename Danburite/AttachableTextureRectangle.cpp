#include "AttachableTextureRectangle.h"

namespace ObjectGL
{
	void AttachableTextureRectangle::_onAttach(const AttachmentType type) noexcept
	{
		assert(!isHandleCreated());
		glFramebufferTexture2D(GL_FRAMEBUFFER, GLenum(type), _RAW_TYPE, ID, 0);
	}

	void AttachableTextureRectangle::_onDetach(const AttachmentType type) noexcept
	{
		assert(!isHandleCreated());
		glFramebufferTexture2D(GL_FRAMEBUFFER, GLenum(type), _RAW_TYPE, 0, 0);
	}

	void AttachableTextureRectangle::memoryAlloc(
		const GLsizei width, const GLsizei height,
		const TextureInternalFormatType internalFormat, const TextureExternalFormatType externalFormat,
		const TextureDataType dataType) noexcept
	{
		memoryAlloc(width, height, nullptr, internalFormat, externalFormat, dataType);
	}
}