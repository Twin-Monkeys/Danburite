#include "GLFunctionWrapper.h"
#include <gl/glew.h>
#include <gl/wglew.h>

using namespace glm;

namespace ObjectGL
{
	void GLFunctionWrapper::setVerticalSync(const bool enabled) noexcept
	{
		const BOOL result = wglSwapIntervalEXT(enabled);
		assert(result);
	}

	void GLFunctionWrapper::setOption(const GLOptionType optionType, const bool enabled) noexcept
	{
		if (enabled)
			glEnable(GLenum(optionType));
		else
			glDisable(GLenum(optionType));

		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setClearColor(const float r, const float g, const float b) noexcept
	{
		glClearColor(r, g, b, 1.f);
		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setClearColor(const vec3& color) noexcept
	{
		setClearColor(color.r, color.g, color.b);
	}

	void GLFunctionWrapper::clearBuffers(const FrameBufferBlitFlag flags) noexcept
	{
		glClear(GLbitfield(flags));
		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setPolygonMode(
		const FrameBufferPositionType facetType, const RasterizationType rasterizationType) noexcept
	{
		glPolygonMode(GLenum(facetType), GLenum(rasterizationType));
		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setDepthMask(const bool enabled) noexcept
	{
		glDepthMask(enabled);
		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setDepthFunction(const DepthStencilFunctionType func) noexcept
	{
		glDepthFunc(GLenum(func));
		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setStencilMask(const GLuint mask) noexcept
	{
		glStencilMask(mask);
		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setStencilOperation(
		const StencilOperationType stencilFail,
		const StencilOperationType stencilPassDepthFail,
		const StencilOperationType stencilDepthPass) noexcept
	{
		glStencilOp(GLenum(stencilFail), GLenum(stencilPassDepthFail), GLenum(stencilDepthPass));
		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setStencilFunction(
		const DepthStencilFunctionType func, const GLint queryValue, const GLuint mask) noexcept
	{
		glStencilFunc(GLenum(func), queryValue, mask);
		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setBlendingFunction(
		const BlendingFunctionType srcFuncType, const BlendingFunctionType destFuncType) noexcept
	{
		glBlendFunc(GLenum(srcFuncType), GLenum(destFuncType));
		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setBlendingFunction(
		const BlendingFunctionType srcRGBFuncType, const BlendingFunctionType destRGBFuncType,
		const BlendingFunctionType srcAlphaFuncType, const BlendingFunctionType destAlphaFuncType) noexcept
	{
		glBlendFuncSeparate(
			GLenum(srcRGBFuncType), GLenum(destRGBFuncType), GLenum(srcAlphaFuncType), GLenum(destAlphaFuncType));

		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setBlendingEquation(const BlendingEquationType type) noexcept
	{
		glBlendEquation(GLenum(type));
		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setCulledFace(const FrameBufferPositionType type) noexcept
	{
		glCullFace(GLenum(type));
		assert(glGetError() == GL_NO_ERROR);
	}

	void GLFunctionWrapper::setFrontFace(const WindingOrderType type) noexcept
	{
		glFrontFace(GLenum(type));
		assert(glGetError() == GL_NO_ERROR);
	}
}