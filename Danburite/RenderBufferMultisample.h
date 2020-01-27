#pragma once

#include "RenderBuffer.h"

namespace ObjectGL
{
	class RenderBufferMultisample : private RenderBuffer
	{
	private:
		RenderBufferMultisample(const RenderBufferMultisample &) = delete;
		RenderBufferMultisample& operator=(const RenderBufferMultisample &) = delete;

	public:
		void memoryAlloc(
			const GLsizei width, const GLsizei height,
			const RenderBufferInternalFormatType internalFormat, const GLsizei numSamplePoints = 4) noexcept;

		virtual ~RenderBufferMultisample() = default;
	};
}