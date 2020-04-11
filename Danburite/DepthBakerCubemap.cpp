#include "DepthBakerCubemap.h"
#include "Constant.h"
#include "GLFunctionWrapper.h"
#include "Material.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DepthBakerCubemap::DepthBakerCubemap() :
		__depthBakingProgram(ProgramFactory::getInstance().getProgram(ProgramType::DEPTH_BAKING_2D))
	{
		__createDepthMap();
	}

	void DepthBakerCubemap::__createDepthMap() noexcept
	{
		__pDepthMap = make_unique<AttachableTextureCubemap>();
		__pDepthMap->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pDepthMap->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_R, TextureWrapValue::CLAMP_TO_EDGE);
	}

	void DepthBakerCubemap::_onSetResolution(const GLsizei width, const GLsizei height) noexcept
	{
		if (__pDepthMap->isHandleCreated())
			__createDepthMap();

		for (GLuint i = 0; i < 6; i++)
		{
			__pDepthMap->memoryAlloc(
				CubemapSideType::POSITIVE_X + i, width, height,
				TextureInternalFormatType::DEPTH_COMPONENT, TextureExternalFormatType::DEPTH_COMPONENT,
				TextureDataType::FLOAT);
		}

		_attachTextureToFrameBuffer(AttachmentType::DEPTH_ATTACHMENT, *__pDepthMap);
	}

	void DepthBakerCubemap::_onBind() noexcept
	{
		__depthBakingProgram.bind();
	}

	void DepthBakerCubemap::setViewProjMatrix(
		const CubemapSideType sideType, const mat4 &viewProjMat) noexcept
	{
		__viewProjMatrices[unsigned(sideType - CubemapSideType::POSITIVE_X)] = viewProjMat;
	}

	void DepthBakerCubemap::setViewProjMatrix(
		const CubemapSideType sideType, const mat4 &viewMat, const mat4 &projMat) noexcept
	{
		setViewProjMatrix(sideType, projMat * viewMat);
	}

	GLuint64 DepthBakerCubemap::getDepthMapHandle() noexcept
	{
		return __pDepthMap->getHandle();
	}
}