#pragma once

#include "GLStateType.h"
#include <unordered_map>
#include <glm/glm.hpp>
#include "FrameBufferBlitFlag.h"
#include "DepthStencilFunctionType.h"
#include "StencilOperationType.h"
#include "BlendingFunctionType.h"
#include "BlendingEquationType.h"
#include "RenderTargetType.h"
#include "RasterizationType.h"
#include "FacetType.h"
#include "WindingOrderType.h"
#include "RCException.h"

namespace ObjectGL
{
	class RenderContext;

	class ContextStateManager
	{
		friend RenderContext;

	private:
		bool __validFlag = false;

		// vsync
		bool __vsyncEnabled = true;

		// glEnable / disable states
		std::unordered_map<GLStateType, bool> __stateMap;

		// clear color
		glm::vec4 __clearColor { 0.f, 0.f, 0.f, 0.f };

		// depth test
		bool __depthMask = false;
		DepthStencilFunctionType __depthFunc = DepthStencilFunctionType::LESS;

		// stencil test
		GLuint __stencilMask = 0xFFU;
		GLuint __stencilQueryValue = 0x00U;
		DepthStencilFunctionType __stencilFunc = DepthStencilFunctionType::ALWAYS;

		StencilOperationType
			__stencilFail			= StencilOperationType::KEEP,
			__stencilPassDepthFail	= StencilOperationType::KEEP,
			__stencilDepthPass		= StencilOperationType::KEEP;

		// blending
		BlendingFunctionType __blendingSrcRGBFuncType = BlendingFunctionType::ONE;
		BlendingFunctionType __blendingDestRGBFuncType = BlendingFunctionType::ZERO;
		BlendingFunctionType __blendingSrcAlphaFuncType = BlendingFunctionType::ONE;
		BlendingFunctionType __blendingDestAlphaFuncType = BlendingFunctionType::ZERO;

		BlendingEquationType __blendingEqType = BlendingEquationType::ADD;

		// polygon mode
		RenderTargetType __polyModeRenderTarget = RenderTargetType::FRONT_AND_BACK;
		RasterizationType __polyModeRasterType = RasterizationType::FILL;

		// culling
		FacetType __cullingFacet = FacetType::BACK;
		WindingOrderType __windingOrder = WindingOrderType::COUNTER_CLOCKWISE;

	public:
		ContextStateManager() noexcept;

		constexpr bool isValid() const noexcept;

		bool enableVerticalSync(const bool enabled);
		bool setState(const GLStateType stateType, const bool state);

		bool setClearColor(
			const float red, const float green, const float blue, const float alpha = 1.f);
		
		bool setClearColor(const glm::vec3 &color, const float alpha = 1.f);
		bool setClearColor(const glm::vec4 &color);

		bool enableDepthMask(const bool enabled);
		bool setDepthFunction(const DepthStencilFunctionType func);

		bool setStencilMask(const GLuint mask);
		bool setStencilFunction(const DepthStencilFunctionType func, const GLuint queryValue);

		bool setStencilOperation(
			const StencilOperationType stencilFail,
			const StencilOperationType stencilPassDepthFail,
			const StencilOperationType stencilDepthPass);

		bool setBlendingFunction(
			const BlendingFunctionType srcFuncType,
			const BlendingFunctionType destFuncType);

		bool setBlendingFunction(
			const BlendingFunctionType srcRGBFuncType,
			const BlendingFunctionType destRGBFuncType,
			const BlendingFunctionType srcAlphaFuncType,
			const BlendingFunctionType destAlphaFuncType);

		bool setBlendingEquation(const BlendingEquationType type);
		bool setPolygonMode(const RenderTargetType renderTargetType, const RasterizationType rasterizationType);

		bool setCulledFace(const FacetType type);
		bool setFrontFace(const WindingOrderType type);
	};

	constexpr bool ContextStateManager::isValid() const noexcept
	{
		return __validFlag;
	}
}