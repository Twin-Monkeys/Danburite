#include "ForwardRenderingPipeline.h"
#include "GLFunctionWrapper.h"

using namespace ObjectGL;

namespace Danburite
{
	ForwardRenderingPipeline::ForwardRenderingPipeline(
		LightManager &lightManager, PerspectiveCamera &camera,
		BatchProcessor<Drawable> &drawer, Skybox &skybox, PostProcessingPipeline &ppPipeline) :
		RenderingPipeline(RenderingPipelineType::FORWARD, lightManager, camera, drawer, skybox, ppPipeline)
	{}

	void ForwardRenderingPipeline::_onRender(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<Drawable> &drawer, Skybox &skybox, PostProcessingPipeline &ppPipeline) noexcept
	{
		// 순서 중요.
		lightManager.process(&Light::bakeDepthMap, drawer);
		lightManager.selfDeploy();

		camera.selfDeploy();

		ppPipeline.bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

		drawer.process(&Drawable::draw);
		skybox.draw();

		PostProcessingPipeline::unbind();

		ppPipeline.render();
	}
}