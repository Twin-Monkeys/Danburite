#include "DepthBaker2D.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DepthBaker2D::DepthBaker2D()
	{
		__setupTransaction.setup([this](ContextStateManager& stateMgr)
		{
			stateMgr.setState(GLStateType::DEPTH_TEST, true);
			stateMgr.setState(GLStateType::CULL_FACE, true);

			stateMgr.enableDepthMask(true);
			stateMgr.setDepthFunction(DepthStencilFunctionType::LESS);
			stateMgr.setCulledFace(FacetType::FRONT);
			stateMgr.setFrontFace(WindingOrderType::COUNTER_CLOCKWISE);

			__depthBaking2DUB.getInterface().projViewMat = __projViewMat;
			__depthBaking2DUB.selfDeploy();
		});
	}

	void DepthBaker2D::_releaseDepthMap() noexcept
	{
		__pDepthMap = nullptr;
	}

	void DepthBaker2D::_allocDepthMap(const GLsizei width, const GLsizei height) noexcept
	{
		__pDepthMap = make_unique<AttachableTexture2D>();
		__pDepthMap->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pDepthMap->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_BORDER);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_BORDER);
		__pDepthMap->setStates(TextureParamType::TEXTURE_BORDER_COLOR, { 1.f, 1.f, 1.f, 1.f });

		__pDepthMap->memoryAlloc(
			width, height,
			TextureInternalFormatType::DEPTH_COMPONENT, TextureExternalFormatType::DEPTH_COMPONENT,
			TextureDataType::FLOAT);

		_attachTextureToFrameBuffer(AttachmentType::DEPTH_ATTACHMENT, *__pDepthMap);
	}

	void DepthBaker2D::_onBind() noexcept
	{
		__setupTransaction();
		__depthBakingProgram.bind();
	}

	void DepthBaker2D::setProjViewMatrix(const mat4 &projViewMat) noexcept
	{
		__projViewMat = projViewMat;
	}

	GLuint64 DepthBaker2D::getDepthMapHandle() noexcept
	{
		return __pDepthMap->getHandle();
	}
}