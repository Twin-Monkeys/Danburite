#include "Camera.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void Camera::_onDeploy(UniformSetter &uniformSetter) const noexcept
	{
		uniformSetter.setUniformMat4(ShaderIdentifier::Name::Camera::VIEW_MATRIX, __viewMat);
		uniformSetter.setUniformMat4(ShaderIdentifier::Name::Camera::PROJECTION_MATRIX, __projMat);
	}

	void Camera::update(const float deltaTime) noexcept
	{
		_onUpdateViewMatrix(deltaTime ,__viewMat);
		_onUpdateProjMatrix(deltaTime ,__projMat);
	}
}