#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class AttachmentType : GLenum
	{
		COLOR_ATTACHMENT0 = GL_COLOR_ATTACHMENT0,
		COLOR_ATTACHMENT1 = GL_COLOR_ATTACHMENT1,
		COLOR_ATTACHMENT2 = GL_COLOR_ATTACHMENT2,
		COLOR_ATTACHMENT3 = GL_COLOR_ATTACHMENT3,
		COLOR_ATTACHMENT4 = GL_COLOR_ATTACHMENT4,
		COLOR_ATTACHMENT5 = GL_COLOR_ATTACHMENT5,
		COLOR_ATTACHMENT6 = GL_COLOR_ATTACHMENT6,
		COLOR_ATTACHMENT7 = GL_COLOR_ATTACHMENT7,
		COLOR_ATTACHMENT8 = GL_COLOR_ATTACHMENT8,
		COLOR_ATTACHMENT9 = GL_COLOR_ATTACHMENT9,
		COLOR_ATTACHMENT10 = GL_COLOR_ATTACHMENT10,
		COLOR_ATTACHMENT11 = GL_COLOR_ATTACHMENT11,
		COLOR_ATTACHMENT12 = GL_COLOR_ATTACHMENT12,
		COLOR_ATTACHMENT13 = GL_COLOR_ATTACHMENT13,
		COLOR_ATTACHMENT14 = GL_COLOR_ATTACHMENT14,
		COLOR_ATTACHMENT15 = GL_COLOR_ATTACHMENT15,
		DEPTH_ATTACHMENT = GL_DEPTH_ATTACHMENT,
		STENCIL_ATTACHMENT = GL_STENCIL_ATTACHMENT,
		DEPTH_STENCIL_ATTACHMENT = GL_DEPTH_STENCIL_ATTACHMENT
	};

	constexpr AttachmentType operator+(const AttachmentType lhs, const unsigned rhs)
	{
		return AttachmentType(GLenum(lhs) + rhs);
	}
}
