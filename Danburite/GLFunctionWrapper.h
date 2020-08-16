#pragma once

#include "GLStateType.h"
#include <glm/glm.hpp>
#include "FrameBufferBlitFlag.h"
#include "RenderTargetType.h"
#include "RasterizationType.h"
#include "DepthStencilFunctionType.h"
#include "StencilOperationType.h"
#include "BlendingFunctionType.h"
#include "BlendingEquationType.h"
#include "WindingOrderType.h"
#include "FacetType.h"

namespace ObjectGL
{
	class GLFunctionWrapper abstract final
	{
	public:
		static void setVerticalSync(const bool enabled) noexcept;
		static void setState(const GLStateType stateType, const bool enabled) noexcept;
		static void setClearColor(const float r, const float g, const float b, const float a = 1.f) noexcept;
		static void setClearColor(const glm::vec3 &color) noexcept;
		static void setClearColor(const glm::vec4 &color) noexcept;
		static void clearBuffers(const FrameBufferBlitFlag flags) noexcept;

		static void setPolygonMode(
			const RenderTargetType positionType, const RasterizationType rasterizationType) noexcept;

		static void setDepthMask(const bool enabled) noexcept;
		static void setDepthFunction(const DepthStencilFunctionType func) noexcept;

		static void setStencilMask(const GLuint mask) noexcept;
		static void setStencilOperation(
			const StencilOperationType stencilFail,
			const StencilOperationType stencilPassDepthFail,
			const StencilOperationType stencilDepthPass) noexcept;

		static void setStencilFunction(
			const DepthStencilFunctionType func, const GLint queryValue, const GLuint mask = 0xFF) noexcept;

		static void setBlendingFunction(
			const BlendingFunctionType srcFuncType, const BlendingFunctionType destFuncType) noexcept;

		static void setBlendingFunction(
			const BlendingFunctionType srcRGBFuncType, const BlendingFunctionType destRGBFuncType,
			const BlendingFunctionType srcAlphaFuncType, const BlendingFunctionType destAlphaFuncType) noexcept;

		static void setBlendingEquation(const BlendingEquationType type) noexcept;

		static void setCulledFace(const FacetType type) noexcept;
		static void setFrontFace(const WindingOrderType type) noexcept;
	};
}