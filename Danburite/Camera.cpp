#include "Camera.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void Camera::_onDeploy(UniformSetter &target) noexcept
	{
		target.setUniformMat4(ShaderIdentifier::Name::Camera::VIEW_MATRIX, __viewMat);
		target.setUniformMat4(ShaderIdentifier::Name::Camera::PROJECTION_MATRIX, __projMat);
	}

	void Camera::updateViewMatrix() noexcept
	{
		_onUpdateViewMatrix(__viewMat);
	}

	void Camera::updateProjMatrix() noexcept
	{
		_onUpdateProjMatrix(__projMat);
	}

	void Camera::update() noexcept
	{
		updateViewMatrix();
		updateProjMatrix();
	}
}