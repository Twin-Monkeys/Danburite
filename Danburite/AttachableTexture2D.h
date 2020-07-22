#pragma once

#include "Texture2D.h"
#include "Attachable.h"

namespace ObjectGL
{
	class AttachableTexture2D : public Texture2D, public Attachable
	{
	private:
		using Texture2D::memoryAlloc;

	protected:
		virtual void _onAttach(const AttachmentType type) noexcept override;
		virtual void _onDetach(const AttachmentType type) noexcept override;

	public:
		void memoryAlloc(
			const GLsizei width, const GLsizei height,
			const TextureInternalFormatType internalFormat,
			const TextureExternalFormatType externalFormat = TextureExternalFormatType::RGB,
			const TextureDataType dataType = TextureDataType::UNSIGNED_BYTE) noexcept;

		virtual ~AttachableTexture2D() = default;
	};
}