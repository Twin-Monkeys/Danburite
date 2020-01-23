#pragma once

#include "GLProfileFlag.h"
#include <iterator>

namespace ObjectGL
{
	class RCAttributeDescriptor
	{
	private:
		static inline constexpr int __defaultAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		int __attribs[std::size(__defaultAttribs)];

	public:
		RCAttributeDescriptor() noexcept;

		void setGLVersion(const int major, const int minor) noexcept;
		void setGLProfileFlags(const ObjectGL::GLProfileFlag flags, const bool enabled) noexcept;

		operator const int* () const noexcept;

		virtual ~RCAttributeDescriptor() = default;
	};
}