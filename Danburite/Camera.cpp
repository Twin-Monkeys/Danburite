#include "Camera.h"
#include "ShaderIdentifier.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Camera::Camera() :
		__cameraSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::CAMERA))
	{}

	void Camera::update(const float deltaTime) noexcept
	{
		_onUpdateViewMatrix(__viewMat);
		_onUpdateProjMatrix(__projMat);
	}

	void Camera::selfDeploy() noexcept
	{
		__cameraSetter.setUniformMat4(ShaderIdentifier::Name::Camera::VIEW_MATRIX, __viewMat);
		__cameraSetter.setUniformMat4(ShaderIdentifier::Name::Camera::PROJECTION_MATRIX, __projMat);
		_onDeploy(__cameraSetter);
	}
}