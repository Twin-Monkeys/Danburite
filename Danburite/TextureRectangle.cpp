#include "TextureRectangle.h"

using namespace std;

namespace ObjectGL
{
	TextureRectangle::TextureRectangle() :
		TextureBase(TextureType::TEXTURE_RECTANGLE)
	{}

	void TextureRectangle::memoryAlloc(
		const GLsizei width, const GLsizei height, const void* const pData,
		const TextureInternalFormatType internalFormat, const TextureExternalFormatType externalFormat,
		const TextureDataType dataType) noexcept
	{
		assert(!isHandleCreated());

		_bindID();
		glTexImage2D(
			_RAW_TYPE, 0, GLint(internalFormat),
			width, height, 0, GLenum(externalFormat), GLenum(dataType), pData);
	}
}