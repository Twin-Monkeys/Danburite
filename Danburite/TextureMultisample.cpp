#include "TextureMultisample.h"

namespace ObjectGL
{
	TextureMultisample::TextureMultisample() :
		TextureBase(TextureType::TEXTURE_2D_MULTISAMPLE)
	{}

	void TextureMultisample::_onAttach(const AttachmentType type) noexcept
	{
		assert(!isHandleCreated());
		glFramebufferTexture2D(GL_FRAMEBUFFER, GLenum(type), _RAW_TYPE, ID, 0);
	}

	void TextureMultisample::_onDetach(const AttachmentType type) noexcept
	{
		assert(!isHandleCreated());
		glFramebufferTexture2D(GL_FRAMEBUFFER, GLenum(type), _RAW_TYPE, 0, 0);
	}

	void TextureMultisample::memoryAlloc(
		const GLsizei width, const GLsizei height,
		const TextureInternalFormatType internalFormat,
		const GLsizei numSamplePoints, const bool fixedSampleLocations) noexcept
	{
		assert(!isHandleCreated());

		_bindID();
		glTexImage2DMultisample(
			_RAW_TYPE, numSamplePoints, GLenum(internalFormat), width, height, fixedSampleLocations);
	}
}