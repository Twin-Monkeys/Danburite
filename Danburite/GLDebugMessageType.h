#pragma once

#include <GL/glew.h>

enum class GLDebugMessageType : GLenum
{
	// An error, typically from the API
	ERR = GL_DEBUG_TYPE_ERROR,

	// Some behavior marked deprecated has been used
	DEPRECATED_BEHAVIOR = GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,

	// Something has invoked undefined behavior
	UNDEFINED_BEHAVIOR = GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,

	// Some functionality the user relies upon is not portable
	PORTABILITY = GL_DEBUG_TYPE_PORTABILITY,

	// Code has triggered possible performance issues
	PERFORMANCE = GL_DEBUG_TYPE_PERFORMANCE,

	// Command stream annotation
	MARKER = GL_DEBUG_TYPE_MARKER,

	// Group push / pop (See glPushDebugGroup() & glPopDebugGroup())
	PUSH_GROUP = GL_DEBUG_TYPE_PUSH_GROUP,
	POP_GROUP = GL_DEBUG_TYPE_POP_GROUP,

	// Some type that isn't one of these
	OTHER = GL_DEBUG_TYPE_OTHER,
};
