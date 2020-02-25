#pragma once

#include <Windows.h>
#include "PFDBufferType.h"

namespace ObjectGL
{
	class PixelFormatDescriptor
	{
	private:
		PIXELFORMATDESCRIPTOR __desc =
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

	public:
		constexpr void setDoubleBuffering(const bool enabled) noexcept;
		constexpr void setBufferSize(const PFDBufferType bufferType, const size_t bitSize) noexcept;

		constexpr operator const PIXELFORMATDESCRIPTOR &() const noexcept;

		virtual ~PixelFormatDescriptor() = default;
	};

	constexpr void PixelFormatDescriptor::setDoubleBuffering(const bool enabled) noexcept
	{
		if (enabled)
			__desc.dwFlags |= PFD_DOUBLEBUFFER;
		else
			__desc.dwFlags &= ~PFD_DOUBLEBUFFER;
	}

	constexpr void PixelFormatDescriptor::setBufferSize(const PFDBufferType bufferType, const size_t bitSize) noexcept
	{
		switch (bufferType)
		{
		case PFDBufferType::COLOR:
			__desc.cColorBits = BYTE(bitSize);
			break;

		case PFDBufferType::DEPTH:
			__desc.cDepthBits = BYTE(bitSize);
			break;

		case PFDBufferType::STENCIL:
			__desc.cStencilBits = BYTE(bitSize);
			break;
		}
	}

	constexpr PixelFormatDescriptor::operator const PIXELFORMATDESCRIPTOR &() const noexcept
	{
		return __desc;
	}
}

