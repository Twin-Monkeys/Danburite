#include "RenderingPipeline.h"
#include "UniformBufferFactory.h"

namespace Danburite
{
	RenderingPipeline::RenderingPipeline(
		LightHandler &lightHandler, Camera &camera, Drawer &drawer, PostProcessingPipeline &ppPipeline) noexcept :
		_lightHandler(lightHandler),
		_cameraSetter(UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::CAMERA)),
		_camera(camera), _drawer(drawer), _ppPipeline(ppPipeline)
	{}
}