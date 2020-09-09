#include "CameraUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	CameraUniformInterface::CameraUniformInterface() noexcept :
		UniformInterface { ShaderIdentifier::Value::UniformBlockBindingPoint::CAMERA }
	{}
}