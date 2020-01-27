#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class FrameBufferBlitFlag : GLbitfield
	{
		COLOR				= GL_COLOR_BUFFER_BIT,
		DEPTH				= GL_DEPTH_BUFFER_BIT,
		STENCIL				= GL_STENCIL_BUFFER_BIT,

		COLOR_DEPTH			= (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT),
		COLOR_DEPTH_STENCIL	= (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)
	};

	constexpr FrameBufferBlitFlag operator|(
		const FrameBufferBlitFlag lhs, const FrameBufferBlitFlag rhs) noexcept
	{
		return FrameBufferBlitFlag(GLbitfield(lhs) | GLbitfield(rhs));
	}
}