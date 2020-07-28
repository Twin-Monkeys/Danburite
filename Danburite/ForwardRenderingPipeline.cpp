#include "ForwardRenderingPipeline.h"
#include "GLFunctionWrapper.h"

using namespace ObjectGL;

namespace Danburite
{
	ForwardRenderingPipeline::ForwardRenderingPipeline(
		LightHandler &lightHandler, PerspectiveCamera &camera,
		Drawer &drawer, PostProcessingPipeline &ppPipeline) :
		RenderingPipeline(RenderingPipelineType::FORWARD, lightHandler, camera, drawer, ppPipeline)
	{}

	void ForwardRenderingPipeline::_onRender(
		LightHandler &lightHandler, UniformBuffer &cameraSetter,
		PerspectiveCamera &camera, Drawer &drawer, PostProcessingPipeline &ppPipeline) noexcept
	{
		// 순서 중요.
		lightHandler.batchBakeDepthMap(drawer);
		lightHandler.batchDeploy();

		cameraSetter.directDeploy(camera);

		ppPipeline.bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

		drawer.batchDraw();
		PostProcessingPipeline::unbind();

		ppPipeline.render();
	}
}