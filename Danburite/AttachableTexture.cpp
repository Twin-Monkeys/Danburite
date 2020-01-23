#include "AttachableTexture.h"

namespace ObjectGL
{
	AttachableTexture::AttachableTexture()
	{
		setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	}

	void AttachableTexture::_onAttach(const AttachmentType type) noexcept
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GLenum(type), GL_TEXTURE_2D, ID, 0);
	}

	void AttachableTexture::_onDetach(const AttachmentType type) noexcept
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GLenum(type), GL_TEXTURE_2D, 0, 0);
	}

	void AttachableTexture::memoryAlloc(
		const GLsizei width, const GLsizei height,
		const TextureInternalFormatType internalFormat, const TextureExternalFormatType externalFormat,
		const TextureDataType dataType) noexcept
	{
		memoryAlloc(width, height, nullptr, internalFormat, externalFormat, dataType, 0, false);
	}
}