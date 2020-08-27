#include "CameraUniformInterface.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	CameraUniformInterface::CameraUniformInterface() noexcept :
		UniformInterface
	{
		ShaderIdentifier::Name::UniformBuffer::CAMERA,
		ShaderIdentifier::Value::UniformBlockBindingPoint::CAMERA
	}
	{}
}