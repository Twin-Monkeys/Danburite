#pragma once

#include "TextureBase.h"
#include "CubemapSideType.h"

namespace ObjectGL
{
	class TextureCubemap : public TextureBase
	{
	public:
		TextureCubemap();

		void memoryAlloc(
			const CubemapSideType sideType,
			const GLsizei width, const GLsizei height, const void* const pData,
			const TextureInternalFormatType internalFormat,
			const TextureExternalFormatType externalFormat,
			const TextureDataType dataType,
			const GLint mipmapLevel = 0) noexcept;

		void createMipmap() noexcept;

		virtual ~TextureCubemap() = default;
	};
}