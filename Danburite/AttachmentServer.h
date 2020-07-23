#pragma once

#include "AttachableTextureRectangle.h"

namespace Danburite
{
	class AttachmentServer
	{
	private:

	public:
		ObjectGL::AttachableTextureRectangle &getTexRectangle(
			const ObjectGL::TextureInternalFormatType internalFormat,
			const ObjectGL::TextureExternalFormatType externalFormat = ObjectGL::TextureExternalFormatType::RGB,
			const ObjectGL::TextureDataType dataType = ObjectGL::TextureDataType::UNSIGNED_BYTE
			) noexcept;
	};
}