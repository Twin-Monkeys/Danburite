#pragma once

#include "RenderBufferBase.h"

namespace ObjectGL
{
	class RenderBufferMultisample : public RenderBufferBase
	{
	private:
		RenderBufferMultisample(const RenderBufferMultisample &) = delete;
		RenderBufferMultisample& operator=(const RenderBufferMultisample &) = delete;

	public:
		RenderBufferMultisample() = default;

		void memoryAlloc(
			const GLsizei width, const GLsizei height,
			const RenderBufferInternalFormatType internalFormat, const GLsizei numSamplePoints) noexcept;

		virtual ~RenderBufferMultisample() = default;
	};
}