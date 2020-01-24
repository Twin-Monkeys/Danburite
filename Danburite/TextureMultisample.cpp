#include "TextureMultisample.h"

namespace ObjectGL
{
	TextureMultisample::TextureMultisample() :
		Texture(TextureType::TEXTURE_2D_MULTISAMPLE)
	{}

	void TextureMultisample::memoryAlloc(
		const GLsizei width, const GLsizei height,
		const TextureInternalFormatType internalFormat,
		const GLsizei numSamplePoints, const bool fixedSampleLocations) noexcept
	{

	}
}