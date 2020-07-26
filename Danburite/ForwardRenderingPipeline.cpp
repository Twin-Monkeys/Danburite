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
		glViewport(0, 0, width, height);
		_camera.setAspectRatio(width, height);
		_ppPipeline.setScreenSize(width, height);
	}

	void ForwardRenderingPipeline::render() noexcept
	{
		// 순서 중요.
		_lightHandler.batchBakeDepthMap(_drawer);
		_lightHandler.batchDeploy();

		_cameraSetter.directDeploy(_camera);

		_ppPipeline.bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

		_drawer.batchDraw();
		PostProcessingPipeline::unbind();

		_ppPipeline.render();
	}
}