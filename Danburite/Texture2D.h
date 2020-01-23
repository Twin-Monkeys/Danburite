#pragma once

#include "Texture.h"

namespace ObjectGL
{
	class Texture2D : public Texture
	{
	public:
		Texture2D();

		void memoryAlloc(
			const GLsizei width, const GLsizei height, const void* const pData,
			const TextureInternalFormatType internalFormat = TextureInternalFormatType::RGB,
			const TextureExternalFormatType externalFormat = TextureExternalFormatType::RGB,
			const TextureDataType dataType = TextureDataType::UNSIGNED_BYTE,
			const GLint mipmapLevel = 0, const bool mipmapCreation = true) noexcept;

		virtual ~Texture2D() = default;
	};
}