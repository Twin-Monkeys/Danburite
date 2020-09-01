#include "DepthBakerCubemap.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DepthBakerCubemap::DepthBakerCubemap()
	{
		__setupTransaction.setup([this](ContextStateManager& stateMgr)
		{
			DepthBakingCubemapUniformInterface &
				depthBakingCubemapUniformInterface = __depthBakingCubemapUB.getInterface();

			depthBakingCubemapUniformInterface.center.set(__center);
			depthBakingCubemapUniformInterface.zFar.set(__zFar);
			depthBakingCubemapUniformInterface.projViewMatrices.set(0, 6, __viewProjMatrices);
			__depthBakingCubemapUB.selfDeploy();
		});
	}

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
		__setupTransaction();
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