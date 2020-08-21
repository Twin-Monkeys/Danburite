#pragma once

#include "RenderingPipeline.h"
#include "UniformBufferFactory.h"

namespace Danburite
{
	class ForwardRenderingPipeline : public RenderingPipeline
	{
	private:
		ObjectGL::UniformBuffer &__phongSetter =
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::PHONG);

		SetupTransaction __setupTransaction;

	protected:
		virtual void _onRender(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<SceneObject> &drawer, Skybox &skybox, PostProcessorPipeline &ppPipeline) noexcept override;

	public:
		ForwardRenderingPipeline(
			LightManager &lightManager, PerspectiveCamera &camera, BatchProcessor<SceneObject> &drawer, Skybox &skybox);
	};
}
