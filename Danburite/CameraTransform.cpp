#include "CameraTransform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

namespace Danburite
{
	void CameraTransform::updateMatrix() noexcept
	{
		Transform::updateMatrix();
		__viewMat = inverse(getModelMatrix());
	}
}