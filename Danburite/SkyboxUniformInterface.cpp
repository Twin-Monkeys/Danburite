#include "SkyboxUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	SkyboxUniformInterface::SkyboxUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::SKYBOX }
	{}
}