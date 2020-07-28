#include "RenderingPipeline.h"
#include "UniformBufferFactory.h"

namespace Danburite
{
	RenderingPipeline::RenderingPipeline(
		const RenderingPipelineType pipelineType,
		LightHandler &lightHandler, PerspectiveCamera &camera,
		Drawer &drawer, PostProcessingPipeline &ppPipeline) noexcept :
		__TYPE(pipelineType), __lightHandler(lightHandler),

		__pipelineSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::RENDERING_PIPELINE)),

		__cameraSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::CAMERA)),

		__camera(camera), __drawer(drawer), __ppPipeline(ppPipeline)
	{}

	void RenderingPipeline::_onSetScreenSize(const GLsizei width, const GLsizei height) noexcept
	{}

	void RenderingPipeline::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__screenSize.x = width;
		__screenSize.y = height;

		glViewport(0, 0, width, height);
		__camera.setAspectRatio(width, height);
		__ppPipeline.setScreenSize(width, height);

		_onSetScreenSize(width, height);
	}

	void RenderingPipeline::render() noexcept
	{
		__pipelineSetter.setUniformUint(ShaderIdentifier::Name::RenderingPipeline::TYPE, GLuint(__TYPE));
		_onRender(__lightHandler, __cameraSetter, __camera, __drawer, __ppPipeline);
	}
}