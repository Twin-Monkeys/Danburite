#include "Texture2D.h"

using namespace std;

namespace ObjectGL
{
	Texture2D::Texture2D() :
		Texture(TextureType::TEXTURE_2D)
	{}

	void Texture2D::memoryAlloc(
		const GLsizei width, const GLsizei height, const void* const pData,
		const TextureInternalFormatType internalFormat, const TextureExternalFormatType externalFormat,
		const TextureDataType dataType, const GLint mipmapLevel, const bool mipmapCreation) noexcept
	{
		_bindID();
		glTexImage2D(
			_RAW_TYPE, mipmapLevel, GLint(internalFormat),
			width, height, 0, GLenum(externalFormat), GLenum(dataType), pData);

		if (mipmapCreation)
			glGenerateMipmap(_RAW_TYPE);
	}
}