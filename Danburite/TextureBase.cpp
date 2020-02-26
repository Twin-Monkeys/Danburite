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
		assert(glGetError() == GL_NO_ERROR);
	}

	void TextureBase::_bindID() noexcept
	{
		glBindTexture(_RAW_TYPE, ID);
		assert(glGetError() == GL_NO_ERROR);
	}

	void TextureBase::bind(const GLuint location) noexcept
	{
		glActiveTexture(GL_TEXTURE0 + location);
		assert(glGetError() == GL_NO_ERROR);

		_bindID();
	}

	GLuint64 TextureBase::createHandle(const bool residence) noexcept
	{
		if (__handle)
			unreside();

		__handle = glGetTextureHandleARB(ID);
		assert(glGetError() == GL_NO_ERROR);

		if (residence)
			reside();

		return __handle;
	}

	void TextureBase::reside() noexcept
	{
		assert(__handle);

		glMakeTextureHandleResidentARB(__handle);
		assert(glGetError() == GL_NO_ERROR);
	}

	void TextureBase::unreside() noexcept
	{
		assert(__handle);

		glMakeTextureHandleNonResidentARB(__handle);
		assert(glGetError() == GL_NO_ERROR);
	}

	TextureBase::~TextureBase() noexcept
	{
		__release();
	}

	void TextureBase::unbind(const TextureType type, const GLint location) noexcept
	{
		glActiveTexture(GL_TEXTURE0 + location);
		assert(glGetError() == GL_NO_ERROR);

		glBindTexture(GLenum(type), 0);
		assert(glGetError() == GL_NO_ERROR);
	}
}