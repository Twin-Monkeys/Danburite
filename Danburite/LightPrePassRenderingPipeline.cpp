#include "LightPrePassRenderingPipeline.h"
#include "GLFunctionWrapper.h"
#include "ProgramFactory.h"

using namespace ObjectGL;

namespace Danburite
{
	LightPrePassRenderingPipeline::LightPrePassRenderingPipeline(
		LightHandler& lightHandler, PerspectiveCamera& camera,
		Drawer& drawer, PostProcessingPipeline& ppPipeline) :
		RenderingPipeline(lightHandler, camera, drawer, ppPipeline),
		__extractionProgram(ProgramFactory::getInstance().
			getProgram(ProgramType::LIGHT_PREPASS_NORMAL_SHININESS_EXTRACTION))
	{}

	void LightPrePassRenderingPipeline::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		glViewport(0, 0, width, height);
		_camera.setAspectRatio(width, height);
	}

	void LightPrePassRenderingPipeline::render() noexcept
	{
		_lightHandler.batchDeploy();
		_lightHandler.batchBakeDepthMap(_drawer);

		_cameraSetter.directDeploy(_camera);

		FrameBuffer::unbind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

		__extractionProgram.bind();
		_drawer.batchRawDrawcall();
	}
}