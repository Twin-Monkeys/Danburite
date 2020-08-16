#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class FrameBufferBlitFlag : GLbitfield
	{
		COLOR	= GL_COLOR_BUFFER_BIT,
		DEPTH	= GL_DEPTH_BUFFER_BIT,
		STENCIL	= GL_STENCIL_BUFFER_BIT
	};

	constexpr bool operator&(
		const FrameBufferBlitFlag lhs, const FrameBufferBlitFlag rhs) noexcept
	{
		return bool(GLbitfield(lhs) | GLbitfield(rhs));
	}

	constexpr FrameBufferBlitFlag operator|(
		const FrameBufferBlitFlag lhs, const FrameBufferBlitFlag rhs) noexcept
	{
		return FrameBufferBlitFlag(GLbitfield(lhs) | GLbitfield(rhs));
	}
}