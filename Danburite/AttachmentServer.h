#pragma once

#include <list>
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
			ObjectGL::TextureDataType,
			ObjectGL::TextureMinFilterValue,
			ObjectGL::TextureMagFilterValue>;

		std::list<std::pair<
			TexRectParam, std::weak_ptr<ObjectGL::AttachableTextureRectangle>>>
			__texRectWeakPtrs;

	public:
		[[nodiscard]]
		std::shared_ptr<ObjectGL::AttachableTextureRectangle>
			getTexRectangle(
			const GLsizei width, const GLsizei height,
			const ObjectGL::TextureInternalFormatType internalFormat,
			const ObjectGL::TextureExternalFormatType externalFormat,
			const ObjectGL::TextureDataType dataType,
			const ObjectGL::TextureMinFilterValue minFilter,
			const ObjectGL::TextureMagFilterValue magFilter) noexcept;
	};
}