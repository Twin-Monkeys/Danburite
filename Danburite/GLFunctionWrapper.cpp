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

	void GLFunctionWrapper::setState(const GLStateType stateType, const bool enabled) noexcept
	{
		if (enabled)
			glEnable(GLenum(stateType));
		else
			glDisable(GLenum(stateType));
	}

	void GLFunctionWrapper::setClearColor(const float r, const float g, const float b, const float a) noexcept
	{
		glClearColor(r, g, b, a);
	}

	void GLFunctionWrapper::setClearColor(const vec3& color) noexcept
	{
		setClearColor(color.r, color.g, color.b);
	}

	void GLFunctionWrapper::setClearColor(const vec4 &color) noexcept
	{
		setClearColor(color.r, color.g, color.b, color.a);
	}

	void GLFunctionWrapper::clearBuffers(const FrameBufferBlitFlag flags) noexcept
	{
		glClear(GLbitfield(flags));
	}

	void GLFunctionWrapper::setPolygonMode(
		const RenderTargetType renderTargetType, const RasterizationType rasterizationType) noexcept
	{
		glPolygonMode(GLenum(renderTargetType), GLenum(rasterizationType));
	}

	void GLFunctionWrapper::setDepthMask(const bool enabled) noexcept
	{
		glDepthMask(enabled);
	}

	void GLFunctionWrapper::setDepthFunction(const DepthStencilFunctionType func) noexcept
	{
		glDepthFunc(GLenum(func));
	}

	void GLFunctionWrapper::setStencilMask(const GLuint mask) noexcept
	{
		glStencilMask(mask);
	}

	void GLFunctionWrapper::setStencilOperation(
		const StencilOperationType stencilFail,
		const StencilOperationType stencilPassDepthFail,
		const StencilOperationType stencilDepthPass) noexcept
	{
		glStencilOp(GLenum(stencilFail), GLenum(stencilPassDepthFail), GLenum(stencilDepthPass));
	}

	void GLFunctionWrapper::setStencilFunction(
		const DepthStencilFunctionType func, const GLint queryValue, const GLuint mask) noexcept
	{
		glStencilFunc(GLenum(func), queryValue, mask);
	}

	void GLFunctionWrapper::setBlendingFunction(
		const BlendingFunctionType srcFuncType, const BlendingFunctionType destFuncType) noexcept
	{
		glBlendFunc(GLenum(srcFuncType), GLenum(destFuncType));
	}

	void GLFunctionWrapper::setBlendingFunction(
		const BlendingFunctionType srcRGBFuncType, const BlendingFunctionType destRGBFuncType,
		const BlendingFunctionType srcAlphaFuncType, const BlendingFunctionType destAlphaFuncType) noexcept
	{
		glBlendFuncSeparate(
			GLenum(srcRGBFuncType), GLenum(destRGBFuncType), GLenum(srcAlphaFuncType), GLenum(destAlphaFuncType));
	}

	void GLFunctionWrapper::setBlendingEquation(const BlendingEquationType type) noexcept
	{
		glBlendEquation(GLenum(type));
	}

	void GLFunctionWrapper::setCulledFace(const FacetType type) noexcept
	{
		glCullFace(GLenum(type));
	}

	void GLFunctionWrapper::setFrontFace(const WindingOrderType type) noexcept
	{
		// The initial value is GL_CCW.
		glFrontFace(GLenum(type));
	}
}