#pragma once

#include <vector>
#include <memory>
#include "AttachableTextureRectangle.h"

namespace Danburite
{
	class AttachmentServer
	{
	private:
		using TexRectParam =
			std::tuple<
			GLsizei, GLsizei,
			ObjectGL::TextureInternalFormatType,
			ObjectGL::TextureExternalFormatType,
			ObjectGL::TextureDataType>;

		std::vector<std::pair<
			TexRectParam, std::weak_ptr<ObjectGL::AttachableTextureRectangle>>>
			__texRectWeakPtrs;

	public:
		std::shared_ptr<ObjectGL::AttachableTextureRectangle>
			getTexRectangle(
			const GLsizei width, const GLsizei height,
			const ObjectGL::TextureInternalFormatType internalFormat,
			const ObjectGL::TextureExternalFormatType externalFormat = ObjectGL::TextureExternalFormatType::RGB,
			const ObjectGL::TextureDataType dataType = ObjectGL::TextureDataType::UNSIGNED_BYTE
			) noexcept;
	};
}