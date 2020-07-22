#pragma once

#include "TextureRectangle.h"
#include "Attachable.h"

namespace ObjectGL
{
	class AttachableTextureRectangle : public TextureRectangle, public Attachable
	{
	private:
		using TextureRectangle::memoryAlloc;

	protected:
		virtual void _onAttach(const AttachmentType type) noexcept override;
		virtual void _onDetach(const AttachmentType type) noexcept override;

	public:
		void memoryAlloc(
			const GLsizei width, const GLsizei height,
			const TextureInternalFormatType internalFormat,
			const TextureExternalFormatType externalFormat = TextureExternalFormatType::RGB,
			const TextureDataType dataType = TextureDataType::UNSIGNED_BYTE) noexcept;

		virtual ~AttachableTextureRectangle() = default;
	};
}