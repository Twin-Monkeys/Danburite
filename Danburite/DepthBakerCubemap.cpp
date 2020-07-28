#include "DepthBakerCubemap.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DepthBakerCubemap::DepthBakerCubemap() :
		__depthBakingProgram(
			ProgramFactory::getInstance().getProgram(ProgramType::DEPTH_BAKING_CUBEMAP)),

		__depthBakingCubemapSetter(
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::DEPTH_BAKING_CUBEMAP))
	{}

	void DepthBakerCubemap::_releaseDepthMap() noexcept
	{
		__pDepthMap = nullptr;
	}

	void DepthBakerCubemap::_allocDepthMap(const GLsizei width, const GLsizei height) noexcept
	{
		__pDepthMap = make_unique<AttachableTextureCubemap>();
		__pDepthMap->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pDepthMap->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_R, TextureWrapValue::CLAMP_TO_EDGE);

		for (CubemapSideType i = CubemapSideType::POSITIVE_X; i <= CubemapSideType::NEGATIVE_Z; i++)
		{
			__pDepthMap->memoryAlloc(
				i, width, height,
				TextureInternalFormatType::DEPTH_COMPONENT,
				TextureExternalFormatType::DEPTH_COMPONENT,
				TextureDataType::FLOAT);
		}

		_attachTextureToFrameBuffer(AttachmentType::DEPTH_ATTACHMENT, *__pDepthMap);
	}

	void DepthBakerCubemap::_onBind() noexcept
	{
		__depthBakingCubemapSetter.setUniformVec3(
			ShaderIdentifier::Name::DepthBakingCubemap::CENTER, __center);

		__depthBakingCubemapSetter.setUniformFloat(
			ShaderIdentifier::Name::DepthBakingCubemap::Z_FAR, __zFar);

		__depthBakingCubemapSetter.setUniformMat4Array(
			ShaderIdentifier::Name::DepthBakingCubemap::PROJ_VIEW_MATRICES, __viewProjMatrices);

		__depthBakingProgram.bind();
	}

	void DepthBakerCubemap::setProjViewMatrix(const CubemapSideType sideType, const mat4 &projViewMat) noexcept
	{
		__viewProjMatrices[unsigned(sideType - CubemapSideType::POSITIVE_X)] = projViewMat;
	}

	GLuint64 DepthBakerCubemap::getDepthMapHandle() noexcept
	{
		return __pDepthMap->getHandle();
	}
}