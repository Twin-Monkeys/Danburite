#include "ForwardRenderingPipeline.h"
#include "GLFunctionWrapper.h"

using namespace ObjectGL;

namespace Danburite
{
	ForwardRenderingPipeline::ForwardRenderingPipeline(
		LightHandler &lightHandler, PerspectiveCamera &camera,
		Drawer &drawer, PostProcessingPipeline &ppPipeline) :
		RenderingPipeline(lightHandler, camera, drawer, ppPipeline)
	{}

	void ForwardRenderingPipeline::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		_camera.setAspectRatio(width, height);
		_ppPipeline.setScreenSize(width, height);
	}

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