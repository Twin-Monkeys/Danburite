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
			const TextureInternalFormatType internalFormat = TextureInternalFormatType::RGB,
			const TextureExternalFormatType externalFormat = TextureExternalFormatType::RGB,
			const TextureDataType dataType = TextureDataType::UNSIGNED_BYTE,
			const GLint mipmapLevel = 0) noexcept;

		void createMipmap() noexcept;

		virtual ~TextureCubemap() = default;
	};
}