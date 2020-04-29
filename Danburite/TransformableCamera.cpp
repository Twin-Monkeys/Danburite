#include "TransformableCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void TransformableCamera::_onUpdateViewMatrix(const float deltaTime, mat4& viewMatrix) noexcept
	{
		__transform.updateMatrix(deltaTime);
		viewMatrix = __transform.getViewMatrix();
	}

	void TransformableCamera::_onDeploy(UniformSetter &uniformSetter) const noexcept
	{
		Camera::_onDeploy(uniformSetter);

		uniformSetter.setUniformVec3(
			ShaderIdentifier::Name::Camera::POSITION, __transform.getPosition());
	}
}