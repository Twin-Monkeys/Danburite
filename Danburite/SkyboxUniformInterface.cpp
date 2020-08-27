#include "SkyboxUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	SkyboxUniformInterface::SkyboxUniformInterface() noexcept :
		UniformInterface
		{
			ShaderIdentifier::Name::UniformBuffer::SKYBOX,
			ShaderIdentifier::Value::UniformBlockBindingPoint::SKYBOX
		}
	{}
}