#include "CameraTransform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

namespace Danburite
{
	void CameraTransform::_onUpdateRotation(mat4 &rotationMat) const noexcept
	{
		// == inverse
		rotationMat = transpose(__viewRotationMat);
	}

	void CameraTransform::update() noexcept
	{
		const vec3 &position = getPosition();
		const vec3 &rotation = getRotation();

		__viewTranslationMat = translate(-position);
		__viewRotationMat = eulerAngleXYZ(-rotation.x, -rotation.y, -rotation.z);

		Transform::update();
	}
}