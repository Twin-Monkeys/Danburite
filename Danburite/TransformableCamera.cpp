#include "TransformableCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void TransformableCamera::_onUpdateViewMatrix(mat4& viewMatrix) noexcept
	{
		const mat4 &viewRotationMat		= __transform.getViewRotationMatrix();
		const mat4 &viewTranslationMat	= __transform.getViewTranslationMatrix();

		viewMatrix = (viewRotationMat * viewTranslationMat);
	}

	void TransformableCamera::_onDeploy(UniformSetter &uniformSetter) const noexcept
	{
		Camera::_onDeploy(uniformSetter);
		uniformSetter.setUniformVec3(ShaderIdentifier::Name::Camera::POSITION, __transform.getPosition());
	}

	void TransformableCamera::update() noexcept
	{
		__transform.update();
		Camera::update();
	}
}