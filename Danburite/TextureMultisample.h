#pragma once

#include "TextureBase.h"
#include "Attachable.h"

namespace ObjectGL
{
	class TextureMultisample : public TextureBase, public Attachable
	{
	protected:
		virtual void _onAttach(const AttachmentType type) noexcept override;
		virtual void _onDetach(const AttachmentType type) noexcept override;

	public:
		TextureMultisample();

		void memoryAlloc(
			const GLsizei width, const GLsizei height,
			const TextureInternalFormatType internalFormat,
			const GLsizei numSamplePoints = 4, const bool fixedSampleLocations = true) noexcept;

		virtual ~TextureMultisample() = default;
	};
}