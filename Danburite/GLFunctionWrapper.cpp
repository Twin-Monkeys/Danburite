#include "GLFunctionWrapper.h"
#include <gl/glew.h>
#include <gl/wglew.h>

using namespace glm;

namespace ObjectGL
{
	bool GLFunctionWrapper::setVerticalSync(const bool enabled) noexcept
	{
		return wglSwapIntervalEXT(enabled);
	}

	void GLFunctionWrapper::setOption(const GLOptionType optionType, const bool enabled) noexcept
	{
		if (enabled)
			glEnable(GLenum(optionType));
		else
			glDisable(GLenum(optionType));
	}

	void GLFunctionWrapper::setClearColor(const float r, const float g, const float b) noexcept
	{
		glClearColor(r, g, b, 1.f);
	}

	void GLFunctionWrapper::setClearColor(const vec3& color) noexcept
	{
		setClearColor(color.r, color.g, color.b);
	}

	void GLFunctionWrapper::clearBuffers(const FrameBufferClearFlag flags) noexcept
	{
		glClear(GLbitfield(flags));
	}

	void GLFunctionWrapper::setPolygonMode(
		const FacetType facetType, const RasterizationType rasterizationType) noexcept
	{
		glPolygonMode(GLenum(facetType), GLenum(rasterizationType));
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
		glFrontFace(GLenum(type));
	}
}