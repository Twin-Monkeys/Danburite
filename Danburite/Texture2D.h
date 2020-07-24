#pragma once

#include "TextureBase.h"

namespace ObjectGL
{
	class Texture2D : public TextureBase
	{
	public:
		Texture2D();

		void memoryAlloc(
			const GLsizei width, const GLsizei height, const void* const pData,
			const TextureInternalFormatType internalFormat,
			const TextureExternalFormatType externalFormat,
			const TextureDataType dataType,
			const GLint mipmapLevel = 0, const bool mipmapCreation = true) noexcept;

		virtual ~Texture2D() = default;
	};
}