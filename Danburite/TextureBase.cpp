#include "TextureBase.h"

using namespace std;

namespace ObjectGL
{
	GLuint TextureBase::__createTexObj()
	{
		GLuint retVal;
		glGenTextures(1, &retVal);

		if (!retVal)
			throw TextureException("Cannot create texture");

		return retVal;
	}

	TextureBase::TextureBase(const TextureType type) :
		Object(__createTexObj()), _RAW_TYPE(GLenum(type))
	{}

	void TextureBase::__release() noexcept
	{
		glDeleteTextures(1, &ID);
	}

	void TextureBase::_bindID() noexcept
	{
		glBindTexture(_RAW_TYPE, ID);
	}

	void TextureBase::bind(const GLuint location) noexcept
	{
		glActiveTexture(GL_TEXTURE0 + location);
		_bindID();
	}

	TextureBase::~TextureBase() noexcept
	{
		__release();
	}

	void TextureBase::unbind(const TextureType type, const GLint location) noexcept
	{
		glActiveTexture(GL_TEXTURE0 + location);
		glBindTexture(GLenum(type), 0);
	}
}