#pragma once

#include "TextureBase.h"

namespace ObjectGL
{
	class TextureRectangle : public TextureBase
	{
	public:
		TextureRectangle();

		void memoryAlloc(
			const GLsizei width, const GLsizei height, const void* const pData,
			const TextureInternalFormatType internalFormat,
			const TextureExternalFormatType externalFormat,
			const TextureDataType dataType) noexcept;

		virtual ~TextureRectangle() = default;
	};
}