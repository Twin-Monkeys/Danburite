#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void Transform::orbit(const float angle, const vec3 &pivot, const vec3& axis) noexcept
	{
		vec3 movedPos = (__pos - pivot);
		movedPos = (mat3(rotate(angle, axis)) * movedPos);

		__pos = movedPos + pivot;
	}

	void Transform::setRotationAxis(const vec3 &axis) noexcept
	{
		__rotation.second = normalize(axis);
	}

	void Transform::setRotation(const float angle, const vec3 &axis) noexcept
	{
		setRotationAngle(angle);
		setRotationAxis(axis);
	}

	void Transform::calcModelMatrix(const mat4 &parentModelMat, mat4 &retVal) noexcept
	{
		retVal = translate(parentModelMat, __pos);
		retVal = rotate(retVal, __rotation.first, __rotation.second);
		retVal = scale(retVal, __scale);
	}
}