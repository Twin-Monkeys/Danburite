#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class FrameBufferClearFlag : GLbitfield
	{
		COLOR				= GL_COLOR_BUFFER_BIT,
		DEPTH				= GL_DEPTH_BUFFER_BIT,
		STENCIL				= GL_STENCIL_BUFFER_BIT,

		COLOR_DEPTH			= (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT),
		COLOR_DEPTH_STENCIL	= (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)
	};

	constexpr FrameBufferClearFlag operator|(
		const FrameBufferClearFlag lhs, const FrameBufferClearFlag rhs) noexcept
	{
		return FrameBufferClearFlag(GLbitfield(lhs) | GLbitfield(rhs));
	}
}