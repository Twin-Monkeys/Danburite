#pragma once

#include "GLProfileFlag.h"
#include <iterator>

namespace ObjectGL
{
	class RCAttributeDescriptor
	{
	private:
		int __attribs[7] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

	public:
		constexpr void setGLVersion(const int major, const int minor) noexcept;
		constexpr void setGLProfileFlags(const ObjectGL::GLProfileFlag flags, const bool enabled) noexcept;

		constexpr operator const int *() const noexcept;

		virtual ~RCAttributeDescriptor() = default;
	};

	constexpr void RCAttributeDescriptor::setGLVersion(const int major, const int minor) noexcept
	{
		__attribs[1] = major;
		__attribs[3] = minor;
	}

	constexpr void RCAttributeDescriptor::setGLProfileFlags(const GLProfileFlag flags, const bool enabled) noexcept
	{
		if (enabled)
			__attribs[5] |= flags;
		else
			__attribs[5] &= ~flags;
	}

	constexpr RCAttributeDescriptor::operator const int *() const noexcept
	{
		return __attribs;
	}
}