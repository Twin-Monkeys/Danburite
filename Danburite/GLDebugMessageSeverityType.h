#pragma once

#include <GL/glew.h>

enum class GLDebugMessageSeverityType : GLenum
{
	/*
		All OpenGL Errors, shader compilation/linking errors,
		Or highly-dangerous undefined behavior
	*/
	HIGH = GL_DEBUG_SEVERITY_HIGH,

	/*
		Major performance warnings,
		Shader compilation/linking warnings,
		Or the use of deprecated functionality
	*/
	MEDIUM = GL_DEBUG_SEVERITY_MEDIUM,

	/*
		Redundant state change performance warning,
		Or unimportant undefined behavior
	*/
	LOW = GL_DEBUG_SEVERITY_LOW,

	// Anything that isn't an error or performance issue.
	NOTIFICATION = GL_DEBUG_SEVERITY_NOTIFICATION
};
