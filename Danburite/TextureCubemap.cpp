#include "TextureCubemap.h"

namespace ObjectGL
{
	TextureCubemap::TextureCubemap() :
		TextureBase(TextureType::TEXTURE_CUBE_MAP)
	{}

	void TextureCubemap::memoryAlloc(
		const CubemapSideType sideType,
		const GLsizei width, const GLsizei height, const void* const pData,
		const TextureInternalFormatType internalFormat, const TextureExternalFormatType externalFormat,
		const TextureDataType dataType, const GLint mipmapLevel) noexcept
	{
		_bindID();
		glTexImage2D(
			GLenum(sideType), mipmapLevel, GLint(internalFormat),
			width, height, 0, GLenum(externalFormat), GLenum(dataType), pData);
	}

	void TextureCubemap::createMipmap() noexcept
	{
		_bindID();
		glGenerateMipmap(_RAW_TYPE);
	}
}