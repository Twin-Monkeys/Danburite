#pragma once

#include <Windows.h>
#include "PFDBufferType.h"

namespace ObjectGL
{
	class PixelFormatDescriptor
	{
	private:
		static inline constexpr PIXELFORMATDESCRIPTOR __defaultDesc =
		{
			// nSize
			sizeof(PIXELFORMATDESCRIPTOR),

			// nVersion
			1,

			// dwFlags
			(PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL),

			// iPixelType
			PFD_TYPE_RGBA,

			// cColorBits
			24,

			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

			// cDepthBits
			24,

			// cStencilBits
			8,

			0,

			// iLayerType
			PFD_MAIN_PLANE
		};

		PIXELFORMATDESCRIPTOR __desc;

	public:
		PixelFormatDescriptor() noexcept;

		void setDoubleBuffering(const bool enabled) noexcept;
		void setBufferSize(const PFDBufferType bufferType, const size_t bitSize) noexcept;

		operator const PIXELFORMATDESCRIPTOR &() const noexcept;

		virtual ~PixelFormatDescriptor() = default;
	};
}

