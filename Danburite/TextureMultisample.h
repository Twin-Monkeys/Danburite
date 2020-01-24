#pragma once

#include "Texture.h"

namespace ObjectGL
{
	class TextureMultisample : public Texture
	{
	public:
		TextureMultisample();

		void memoryAlloc(
			const GLsizei width, const GLsizei height,
			const TextureInternalFormatType internalFormat,
			const GLsizei numSamplePoints = 4, const bool fixedSampleLocations = true) noexcept;

		virtual ~TextureMultisample() = default;
	};
}