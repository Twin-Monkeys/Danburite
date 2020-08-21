#include "RenderingPipeline.h"
#include "UniformBufferFactory.h"

namespace Danburite
{
	RenderingPipeline::RenderingPipeline(
		LightManager &lightManager, PerspectiveCamera &camera,
		BatchProcessor<SceneObject> &drawer, Skybox &skybox) noexcept :
		__lightManager(lightManager), __skybox(skybox), __camera(camera), __drawer(drawer)
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
		_onRender(__lightManager, __camera, __drawer, __skybox, __ppPipeline);
	}
}