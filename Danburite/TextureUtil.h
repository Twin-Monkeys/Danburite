#pragma once

#include "Texture2D.h"
#include "TextureCubemap.h"
#include "TextureUtilException.h"
#include <vector>
#include <memory>

namespace Danburite
{
	class TextureUtil abstract final
	{
	public:
		static std::shared_ptr<ObjectGL::Texture2D> createTexture2DFromImage(
			const std::string_view &imagePath, const ObjectGL::TextureDataType dataType = ObjectGL::TextureDataType::UNSIGNED_BYTE,
			const GLint mipmapLevel = 0, const bool mipmapCreation = true);

		static std::shared_ptr<ObjectGL::TextureCubemap> createTextureCubemapFromImage(
			const std::vector<std::string_view> &imagePaths,
			const ObjectGL::TextureDataType dataType = ObjectGL::TextureDataType::UNSIGNED_BYTE,
			const GLint mipmapLevel = 0, const bool mipmapCreation = false);

		template <typename T>
		static GLuint64 getHandleIfExist(const std::shared_ptr<T> &pTexture) noexcept;
	};

	template <typename T>
	GLuint64 TextureUtil::getHandleIfExist(const std::shared_ptr<T> &pTexture) noexcept
	{
		if (!pTexture)
			return 0ULL;

		return pTexture->getHandle();
	}
}
