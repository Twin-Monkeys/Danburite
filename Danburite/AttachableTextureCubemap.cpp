#include "AttachableTextureCubemap.h"

namespace ObjectGL
{
	void AttachableTextureCubemap::_onAttach(const AttachmentType type) noexcept
	{
		assert(!isHandleCreated());
		glFramebufferTexture(GL_FRAMEBUFFER, GLenum(type), ID, 0);
	}

	void AttachableTextureCubemap::_onDetach(const AttachmentType type) noexcept
	{
		assert(!isHandleCreated());
		glFramebufferTexture(GL_FRAMEBUFFER, GLenum(type), 0, 0);
	}

	void AttachableTextureCubemap::memoryAlloc(
		const CubemapSideType sideType, const GLsizei width, const GLsizei height,
		const TextureInternalFormatType internalFormat, const TextureExternalFormatType externalFormat,
		const TextureDataType dataType) noexcept
	{
		memoryAlloc(sideType, width, height, nullptr, internalFormat, externalFormat, dataType);
	}
}