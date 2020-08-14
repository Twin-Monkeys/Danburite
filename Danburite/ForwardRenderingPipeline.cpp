#include "ForwardRenderingPipeline.h"

using namespace ObjectGL;

namespace Danburite
{
	ForwardRenderingPipeline::ForwardRenderingPipeline(
		LightManager &lightManager, PerspectiveCamera &camera, BatchProcessor<SceneObject> &drawer, Skybox &skybox) :
		RenderingPipeline(RenderingPipelineType::FORWARD, lightManager, camera, drawer, skybox)
	{}

	void ForwardRenderingPipeline::_onRender(
		LightManager &lightManager, PerspectiveCamera &camera,
		BatchProcessor<SceneObject> &drawer, Skybox &skybox, PostProcessorPipeline &ppPipeline) noexcept
	{
		// 순서 중요.
		lightManager.process(&Light::bakeDepthMap, drawer);
		lightManager.selfDeploy();

		camera.selfDeploy();
		ppPipeline.render(drawer, skybox, FrameBufferBlitFlag::COLOR | FrameBufferBlitFlag::DEPTH);
	}
}