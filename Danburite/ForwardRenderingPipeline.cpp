#include "ForwardRenderingPipeline.h"
#include "PhongCalcMethodType.h"

using namespace ObjectGL;

namespace Danburite
{
	ForwardRenderingPipeline::ForwardRenderingPipeline(
		LightManager &lightManager, PerspectiveCamera &camera, BatchProcessor<SceneObject> &drawer, Skybox &skybox) :
		RenderingPipeline(lightManager, camera, drawer, skybox)
	{
		__setupTransaction.setup([this](ContextStateManager &stateMgr)
		{
			__phongUB.getInterface().calcMethodType = GLuint(PhongCalcMethodType::FORWARD);
			__phongUB.selfDeploy();

			stateMgr.setState(GLStateType::DEPTH_TEST, true);
			stateMgr.setState(GLStateType::STENCIL_TEST, false);
			stateMgr.setState(GLStateType::BLEND, false);
			stateMgr.setState(GLStateType::CULL_FACE, true);

			stateMgr.setDepthFunction(DepthStencilFunctionType::LESS);
			stateMgr.enableDepthMask(true);
			stateMgr.setCulledFace(FacetType::BACK);
			stateMgr.setFrontFace(WindingOrderType::COUNTER_CLOCKWISE);
		});
	}

	void ForwardRenderingPipeline::_onRender(
		LightManager &lightManager, PerspectiveCamera &camera,
		BatchProcessor<SceneObject> &drawer, Skybox &skybox, PostProcessorPipeline &ppPipeline) noexcept
	{
		// 순서 중요.
		lightManager.process(&Light::bakeDepthMap, drawer);
		lightManager.selfDeploy();

		camera.selfDeploy();
		ppPipeline.render(
			__setupTransaction, drawer, skybox,
			FrameBufferBlitFlag::COLOR | FrameBufferBlitFlag::DEPTH);
	}
}