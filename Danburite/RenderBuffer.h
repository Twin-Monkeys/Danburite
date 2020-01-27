#pragma once

#include "RenderBufferBase.h"

namespace ObjectGL
{
	class RenderBuffer : public RenderBufferBase
	{
	private:
		RenderBuffer(const RenderBuffer &) = delete;
		RenderBuffer& operator=(const RenderBuffer &) = delete;

	public:
		RenderBuffer() = default;

		void memoryAlloc(
			const GLsizei width, const GLsizei height, const RenderBufferInternalFormatType internalFormat) noexcept;

		virtual ~RenderBuffer() = default;
	};
}