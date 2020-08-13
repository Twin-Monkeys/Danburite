#include "RenderingPipeline.h"
#include "UniformBufferFactory.h"

namespace Danburite
{
	RenderingPipeline::RenderingPipeline(
		const RenderingPipelineType pipelineType, LightManager &lightManager, PerspectiveCamera &camera,
		BatchProcessor<SceneObject> &drawer, Skybox &skybox) noexcept :
		__TYPE(pipelineType), __lightManager(lightManager), __skybox(skybox),

		__pipelineSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::RENDERING_PIPELINE)),

		__camera(camera), __drawer(drawer)
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
		_onRender(__lightManager, __camera, __drawer, __skybox, __ppPipeline);
	}
}