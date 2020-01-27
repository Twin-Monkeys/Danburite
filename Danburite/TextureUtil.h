#pragma once

#include "Texture2D.h"
#include "TextureCubemap.h"
#include "TextureUtilException.h"
#include <vector>

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
		static void bindIfExist(T *const pTexture, const GLint location) noexcept;

		template <>
		static void bindIfExist<ObjectGL::Texture2D>(ObjectGL::Texture2D *const pTexture, const GLint location) noexcept;

		template <>
		static void bindIfExist<ObjectGL::TextureCubemap>(ObjectGL::TextureCubemap *const pTexture, const GLint location) noexcept;

		template <typename T>
		static void bindIfExist(const std::shared_ptr<T> &pTexture, const GLint location) noexcept;
	};

	template <typename T>
	void TextureUtil::bindIfExist(T *const pTexture, const GLint location) noexcept
	{
		static_assert(false, "not implemented yet.");
	}

	template <>
	void TextureUtil::bindIfExist<ObjectGL::Texture2D>(ObjectGL::Texture2D *const pTexture, const GLint location) noexcept
	{
		if (pTexture)
			pTexture->bind(location);
		else
			ObjectGL::TextureBase::unbind(ObjectGL::TextureType::TEXTURE_2D, location);
	}

	template <>
	void TextureUtil::bindIfExist<ObjectGL::TextureCubemap>(ObjectGL::TextureCubemap *const pTexture, const GLint location) noexcept
	{
		if (pTexture)
			pTexture->bind(location);
		else
			ObjectGL::TextureBase::unbind(ObjectGL::TextureType::TEXTURE_CUBE_MAP, location);
	}

	template <typename T>
	static void TextureUtil::bindIfExist(const std::shared_ptr<T> &pTexture, const GLint location) noexcept
	{
		bindIfExist(pTexture.get(), location);
	}
}
