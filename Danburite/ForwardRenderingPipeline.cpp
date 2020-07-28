#include "ForwardRenderingPipeline.h"
#include "GLFunctionWrapper.h"

using namespace ObjectGL;

namespace Danburite
{
	ForwardRenderingPipeline::ForwardRenderingPipeline(
		LightManager &lightManager, PerspectiveCamera &camera,
		BatchProcessor<Drawable> &drawer, PostProcessingPipeline &ppPipeline) :
		RenderingPipeline(RenderingPipelineType::FORWARD, lightManager, camera, drawer, ppPipeline)
	{}

	void ForwardRenderingPipeline::_onRender(
		LightManager &lightManager, PerspectiveCamera &camera,
		BatchProcessor<Drawable> &drawer, PostProcessingPipeline &ppPipeline) noexcept
	{
		// ���� �߿�.
		lightManager.process(&Light::bakeDepthMap, drawer);
		lightManager.selfDeploy();

		camera.selfDeploy();

		ppPipeline.bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

		drawer.process(&Drawable::draw);
		PostProcessingPipeline::unbind();

		ppPipeline.render();
	}
}