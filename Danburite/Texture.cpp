#include "Texture.h"

using namespace std;

namespace ObjectGL
{
	GLuint Texture::__createTexObj()
	{
		GLuint retVal;
		glGenTextures(1, &retVal);

		if (!retVal)
			throw TextureException("Cannot create texture");

		return retVal;
	}

	Texture::Texture(const TextureType type) :
		Object(__createTexObj()), _RAW_TYPE(GLenum(type))
	{}

	void Texture::__release() noexcept
	{
		glDeleteTextures(1, &ID);
	}

	void Texture::_bindID() noexcept
	{
		glBindTexture(_RAW_TYPE, ID);
	}

	void Texture::bind(const GLuint location) noexcept
	{
		glActiveTexture(GL_TEXTURE0 + location);
		_bindID();
	}

	Texture::~Texture() noexcept
	{
		__release();
	}

	void Texture::unbind(const TextureType type, const GLint location) noexcept
	{
		glActiveTexture(GL_TEXTURE0 + location);
		glBindTexture(GLenum(type), 0);
	}
}