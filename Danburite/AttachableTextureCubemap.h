#pragma once

#include "TextureCubemap.h"
#include "Attachable.h"

namespace ObjectGL
{
	class AttachableTextureCubemap : public TextureCubemap, public Attachable
	{
	private:
		using TextureCubemap::memoryAlloc;
		using TextureCubemap::createMipmap;

	protected:
		virtual void _onAttach(const AttachmentType type) noexcept override;
		virtual void _onDetach(const AttachmentType type) noexcept override;

	public:
		void memoryAlloc(
			const CubemapSideType sideType,
			const GLsizei width, const GLsizei height,
			const TextureInternalFormatType internalFormat,
			const TextureExternalFormatType externalFormat,
			const TextureDataType dataType) noexcept;

		virtual ~AttachableTextureCubemap() = default;
	};
}