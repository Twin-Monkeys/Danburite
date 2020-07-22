#include "ForwardRenderingPipeline.h"
#include "GLFunctionWrapper.h"

using namespace ObjectGL;

namespace Danburite
{
	ForwardRenderingPipeline::ForwardRenderingPipeline(
		LightHandler &lightHandler, Camera &camera, Drawer &drawer, PostProcessingPipeline &ppPipeline) :
		RenderingPipeline(lightHandler, camera, drawer, ppPipeline)
	{}

	void ForwardRenderingPipeline::render() noexcept
	{
		_lightHandler.batchDeploy();
		_lightHandler.batchBakeDepthMap(_drawer);

		_cameraSetter.directDeploy(_camera);

		_ppPipeline.bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

		_drawer.batchDraw();
		PostProcessingPipeline::unbind();

		_ppPipeline.render();
	}
}