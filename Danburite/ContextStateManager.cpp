#include "ContextStateManager.h"
#include <gl/wglew.h>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/constants.hpp>

using namespace std;
using namespace glm;

namespace ObjectGL
{
	ContextStateManager::ContextStateManager() noexcept :
		__stateMap
		{
			{ GLStateType::ALPHA_TEST, false },
			{ GLStateType::AUTO_NORMAL, false },
			{ GLStateType::BLEND, false },
			{ GLStateType::CLIP_PLANE0, false },
			{ GLStateType::CLIP_PLANE1, false },
			{ GLStateType::CLIP_PLANE2, false },
			{ GLStateType::CLIP_PLANE3, false },
			{ GLStateType::CLIP_PLANE4, false },
			{ GLStateType::CLIP_PLANE5, false },
			{ GLStateType::COLOR_LOGIC_OP, false },
			{ GLStateType::COLOR_MATERIAL, false },
			{ GLStateType::COLOR_SUM, false },
			{ GLStateType::COLOR_TABLE, false },
			{ GLStateType::CONVOLUTION_1D, false },
			{ GLStateType::CONVOLUTION_2D, false },
			{ GLStateType::CULL_FACE, false },
			{ GLStateType::DEBUG_OUTPUT, false },
			{ GLStateType::DEBUG_OUTPUT_SYNCHRONOUS, false },
			{ GLStateType::DEPTH_TEST, false },
			{ GLStateType::FOG, false },
			{ GLStateType::HISTOGRAM, false },
			{ GLStateType::INDEX_LOGIC_OP, false },
			{ GLStateType::LIGHT0, false },
			{ GLStateType::LIGHT1, false },
			{ GLStateType::LIGHT2, false },
			{ GLStateType::LIGHT3, false },
			{ GLStateType::LIGHT4, false },
			{ GLStateType::LIGHT5, false },
			{ GLStateType::LIGHT6, false },
			{ GLStateType::LIGHT7, false },
			{ GLStateType::LIGHTING, false },
			{ GLStateType::LINE_SMOOTH, false },
			{ GLStateType::LINE_STIPPLE, false },
			{ GLStateType::MAP1_COLOR_4, false },
			{ GLStateType::MAP1_INDEX, false },
			{ GLStateType::MAP1_NORMAL, false },
			{ GLStateType::MAP1_TEXTURE_COORD_1, false },
			{ GLStateType::MAP1_TEXTURE_COORD_2, false },
			{ GLStateType::MAP1_TEXTURE_COORD_3, false },
			{ GLStateType::MAP1_TEXTURE_COORD_4, false },
			{ GLStateType::MAP1_VERTEX_3, false },
			{ GLStateType::MAP1_VERTEX_4, false },
			{ GLStateType::MAP2_COLOR_4, false },
			{ GLStateType::MAP2_INDEX, false },
			{ GLStateType::MAP2_NORMAL, false },
			{ GLStateType::MAP2_TEXTURE_COORD_1, false },
			{ GLStateType::MAP2_TEXTURE_COORD_2, false },
			{ GLStateType::MAP2_TEXTURE_COORD_3, false },
			{ GLStateType::MAP2_TEXTURE_COORD_4, false },
			{ GLStateType::MAP2_VERTEX_3, false },
			{ GLStateType::MAP2_VERTEX_4, false },
			{ GLStateType::MINMAX, false },
			{ GLStateType::NORMALIZE, false },
			{ GLStateType::POINT_SMOOTH, false },
			{ GLStateType::POINT_SPRITE, false },
			{ GLStateType::POLYGON_OFFSET_FILL, false },
			{ GLStateType::POLYGON_OFFSET_LINE, false },
			{ GLStateType::POLYGON_OFFSET_POINT, false },
			{ GLStateType::POLYGON_SMOOTH, false },
			{ GLStateType::POLYGON_STIPPLE, false },
			{ GLStateType::POST_COLOR_MATRIX_COLOR, false },
			{ GLStateType::POST_CONVOLUTION_COLOR_, false },
			{ GLStateType::RESCALE_NORMAL, false },
			{ GLStateType::SAMPLE_ALPHA_TO_COVERAG, false },
			{ GLStateType::SAMPLE_ALPHA_TO_ONE, false },
			{ GLStateType::SAMPLE_COVERAGE, false },
			{ GLStateType::SEPARABLE_2D, false },
			{ GLStateType::SCISSOR_TEST, false },
			{ GLStateType::STENCIL_TEST, false },
			{ GLStateType::TEXTURE_1D, false },
			{ GLStateType::TEXTURE_2D, false },
			{ GLStateType::TEXTURE_3D, false },
			{ GLStateType::TEXTURE_CUBE_MAP, false },
			{ GLStateType::TEXTURE_GEN_Q, false },
			{ GLStateType::TEXTURE_GEN_R, false },
			{ GLStateType::TEXTURE_GEN_S, false },
			{ GLStateType::TEXTURE_GEN_T, false },
			{ GLStateType::VERTEX_PROGRAM_POINT_SIZE, false },
			{ GLStateType::VERTEX_PROGRAM_TWO_SIDE, false },
			{ GLStateType::FRAMEBUFFER_SRGB, false },
			{ GLStateType::DITHER, true },
			{ GLStateType::MULTISAMPLE, true }
		}
	{}

	bool ContextStateManager::enableVerticalSync(const bool enabled)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if (__vsyncEnabled == enabled)
			return false;

		__vsyncEnabled = enabled;
		wglSwapIntervalEXT(enabled);

		return true;
	}

	bool ContextStateManager::setState(const GLStateType stateType, const bool state)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		auto resultIt = __stateMap.find(stateType);
		if (resultIt != __stateMap.end())
		{
			if (resultIt->second == state)
				return false;
			else
				resultIt->second = state;
		}
		else
			__stateMap.emplace(stateType, state);

		if (state)
			glEnable(GLenum(stateType));
		else
			glDisable(GLenum(stateType));

		return true;
	}

	bool ContextStateManager::setClearColor(const float red, const float green, const float blue, const float alpha)
	{
		return setClearColor({ red, green, blue, alpha });
	}

	bool ContextStateManager::setClearColor(const vec3 &color, const float alpha)
	{
		return setClearColor(vec4 { color, alpha });
	}

	bool ContextStateManager::setClearColor(const vec4 &color)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if (all(epsilonEqual(__clearColor, color, epsilon<float>())))
			return false;

		__clearColor = color;
		glClearColor(color.r, color.g, color.b, color.a);

		return true;
	}

	bool ContextStateManager::enableDepthMask(const bool enabled)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if (__depthMask == enabled)
			return false;

		__depthMask = enabled;
		glDepthMask(enabled);

		return true;
	}

	bool ContextStateManager::setDepthFunction(const DepthStencilFunctionType func)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if (__depthFunc == func)
			return false;

		__depthFunc = func;
		glDepthFunc(GLenum(func));

		return true;
	}

	bool ContextStateManager::setStencilMask(const GLuint mask)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if (__stencilMask == mask)
			return false;

		__stencilMask = mask;
		glStencilMask(mask);

		return true;
	}

	bool ContextStateManager::setStencilFunction(
		const DepthStencilFunctionType func, const GLuint queryValue)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if ((__stencilFunc == func) &&
			(__stencilQueryValue == queryValue))
			return false;

		__stencilFunc = func;
		__stencilQueryValue = queryValue;
		glStencilFunc(GLenum(func), GLint(queryValue), 0xFFU);
		
		return true;
	}

	bool ContextStateManager::setStencilOperation(
		const StencilOperationType stencilFail,
		const StencilOperationType stencilPassDepthFail,
		const StencilOperationType stencilDepthPass)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if ((__stencilFail == stencilFail) &&
			(__stencilPassDepthFail == stencilPassDepthFail) &&
			(__stencilDepthPass == stencilDepthPass))
			return false;

		__stencilFail = stencilFail;
		__stencilPassDepthFail = stencilPassDepthFail;
		__stencilDepthPass = stencilDepthPass;

		glStencilOp(
			GLenum(stencilFail),
			GLenum(stencilPassDepthFail),
			GLenum(stencilDepthPass));

		return true;
	}

	bool ContextStateManager::setBlendingFunction(
		const BlendingFunctionType srcFuncType, const BlendingFunctionType destFuncType)
	{
		return setBlendingFunction(srcFuncType, destFuncType, srcFuncType, destFuncType);
	}

	bool ContextStateManager::setBlendingFunction(
		const BlendingFunctionType srcRGBFuncType, const BlendingFunctionType destRGBFuncType,
		const BlendingFunctionType srcAlphaFuncType, const BlendingFunctionType destAlphaFuncType)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if ((__blendingSrcRGBFuncType == srcRGBFuncType) &&
			(__blendingDestRGBFuncType == destRGBFuncType) &&
			(__blendingSrcAlphaFuncType == srcAlphaFuncType) &&
			(__blendingDestAlphaFuncType == destAlphaFuncType))
			return false;

		__blendingSrcRGBFuncType = srcRGBFuncType;
		__blendingDestRGBFuncType = destRGBFuncType;
		__blendingSrcAlphaFuncType = srcAlphaFuncType;
		__blendingDestAlphaFuncType = destAlphaFuncType;

		glBlendFuncSeparate(
			GLenum(srcRGBFuncType), GLenum(destRGBFuncType),
			GLenum(srcAlphaFuncType), GLenum(destAlphaFuncType));

		return true;
	}

	bool ContextStateManager::setBlendingFunction(
		const GLuint colorAttachmentIdx, const BlendingFunctionType srcFuncType, const BlendingFunctionType destFuncType)
	{
		return setBlendingFunction(colorAttachmentIdx, srcFuncType, destFuncType, srcFuncType, destFuncType);
	}

	bool ContextStateManager::setBlendingFunction(
		const GLuint colorAttachmentIdx,
		const BlendingFunctionType srcRGBFuncType, const BlendingFunctionType destRGBFuncType,
		const BlendingFunctionType srcAlphaFuncType, const BlendingFunctionType destAlphaFuncType)
	{
		if (!colorAttachmentIdx)
			return setBlendingFunction(srcRGBFuncType, destRGBFuncType, srcAlphaFuncType, destAlphaFuncType);

		if (!__validFlag)
			throw RCException("This context is not bound.");

		glBlendFuncSeparatei(colorAttachmentIdx,
			GLenum(srcRGBFuncType), GLenum(destRGBFuncType),
			GLenum(srcAlphaFuncType), GLenum(destAlphaFuncType));

		return true;
	}

	bool ContextStateManager::setBlendingEquation(const BlendingEquationType type)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if (__blendingEqType == type)
			return false;

		__blendingEqType = type;
		glBlendEquation(GLenum(type));

		return true;
	}

	bool ContextStateManager::setPolygonMode(
		const RenderTargetType renderTargetType, const RasterizationType rasterizationType)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if ((__polyModeRenderTarget == renderTargetType) &&
			(__polyModeRasterType == rasterizationType))
			return false;

		__polyModeRenderTarget = renderTargetType;
		__polyModeRasterType = rasterizationType;
		glPolygonMode(GLenum(renderTargetType), GLenum(rasterizationType));

		return true;
	}

	bool ContextStateManager::setCulledFace(const FacetType type)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if (__cullingFacet == type)
			return false;

		__cullingFacet = type;
		glCullFace(GLenum(type));

		return true;
	}

	bool ContextStateManager::setFrontFace(const WindingOrderType type)
	{
		if (!__validFlag)
			throw RCException("This context is not bound.");

		if (__windingOrder == type)
			return false;

		__windingOrder = type;
		glFrontFace(GLenum(type));

		return true;
	}
}