#include "RCAttributeDescriptor.h"

namespace ObjectGL
{
	RCAttributeDescriptor::RCAttributeDescriptor() noexcept
	{
		memcpy(__attribs, __defaultAttribs, sizeof(__defaultAttribs));
	}

	void RCAttributeDescriptor::setGLVersion(const int major, const int minor) noexcept
	{
		__attribs[1] = major;
		__attribs[3] = minor;
	}

	void RCAttributeDescriptor::setGLProfileFlags(const GLProfileFlag flags, const bool enabled) noexcept
	{
		if (enabled)
			__attribs[5] |= flags;
		else
			__attribs[5] &= ~flags;
	}

	RCAttributeDescriptor::operator const int* () const noexcept
	{
		return __attribs;
	}
}