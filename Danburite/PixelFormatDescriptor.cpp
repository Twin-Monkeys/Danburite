#include "PixelFormatDescriptor.h"

namespace ObjectGL
{
	PixelFormatDescriptor::PixelFormatDescriptor() noexcept :
		__desc(__defaultDesc)
	{}

	void PixelFormatDescriptor::setDoubleBuffering(const bool enabled) noexcept
	{
		if (enabled)
			__desc.dwFlags |= PFD_DOUBLEBUFFER;
		else
			__desc.dwFlags &= ~PFD_DOUBLEBUFFER;
	}

	void PixelFormatDescriptor::setBufferSize(const PFDBufferType bufferType, const size_t bitSize) noexcept
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

	PixelFormatDescriptor::operator const PIXELFORMATDESCRIPTOR &() const noexcept
	{
		return __desc;
	}
}