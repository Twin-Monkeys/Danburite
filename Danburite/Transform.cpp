#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	const vec3 &Transform::getPosition() const noexcept
	{
		return __pos;
	}

	void Transform::setPosition(const vec3 &position) noexcept
	{
		__pos = position;
	}

	void Transform::setPosition(const float xPos, const float yPos, const float zPos) noexcept
	{
		setPosition({ xPos, yPos, zPos });
	}

	void Transform::setPositionX(const float xPos) noexcept
	{
		setPosition({ xPos, __pos.y, __pos.z });
	}

	void Transform::setPositionY(const float yPos) noexcept
	{
		setPosition({ __pos.x, yPos, __pos.z });
	}

	void Transform::setPositionZ(const float zPos) noexcept
	{
		setPosition({ __pos.x, __pos.y, zPos });
	}

	void Transform::adjustPosition(const vec3 &delta) noexcept
	{
		setPosition(__pos + delta);
	}

	void Transform::adjustPosition(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		adjustPosition({ xDelta, yDelta, zDelta });
	}

	void Transform::adjustPositionX(const float xDelta) noexcept
	{
		adjustPosition({ xDelta, 0.f, 0.f });
	}

	void Transform::adjustPositionY(const float yDelta) noexcept
	{
		adjustPosition({ 0.f, yDelta, 0.f });
	}

	void Transform::adjustPositionZ(const float zDelta) noexcept
	{
		adjustPosition({ 0.f, 0.f, zDelta });
	}

	void Transform::orbit(const float angle, const vec3 &pivot, const vec3& axis) noexcept
	{
		vec3 movedPos = (__pos - pivot);
		movedPos = (mat3(rotate(angle, axis)) * movedPos);

		__pos = movedPos + pivot;
	}

	const vec3 &Transform::getScale() const noexcept
	{
		return __scale;
	}

	void Transform::setScale(const float scale) noexcept
	{
		setScale(scale, scale, scale);
	}

	void Transform::setScale(const vec3 &scale) noexcept
	{
		__scale = scale;
	}

	void Transform::setScale(const float xScale, const float yScale, const float zScale) noexcept
	{
		setScale({ xScale, yScale, zScale });
	}

	void Transform::setScaleX(const float xScale) noexcept
	{
		setScale({ xScale, __scale.y, __scale.z });
	}

	void Transform::setScaleY(const float yScale) noexcept
	{
		setScale({ __scale.x, yScale, __scale.z });
	}

	void Transform::setScaleZ(const float zScale) noexcept
	{
		setScale({ __scale.x, __scale.y, zScale });
	}

	void Transform::adjustScale(const vec3 &delta) noexcept
	{
		setScale(__scale + delta);
	}

	void Transform::adjustScale(const float xDelta, const float yDelta, const float zDelta) noexcept
	{
		adjustScale({ xDelta, yDelta, zDelta });
	}

	void Transform::adjustScaleX(const float xDelta) noexcept
	{
		adjustScale({ xDelta, 0.f, 0.f });
	}

	void Transform::adjustScaleY(const float yDelta) noexcept
	{
		adjustScale({ 0.f, yDelta, 0.f });
	}

	void Transform::adjustScaleZ(const float zDelta) noexcept
	{
		adjustScale({ 0.f, 0.f, zDelta });
	}

	const pair<float, vec3> &Transform::getRotation() const noexcept
	{
		return __rotation;
	}

	void Transform::setRotationAngle(const float angle) noexcept
	{
		constexpr float TWO_PI = two_pi<float>();
		float validAngle = angle;

		if (validAngle > TWO_PI)
			validAngle -= TWO_PI;
		else if (validAngle < -TWO_PI)
			validAngle += TWO_PI;

		__rotation.first = validAngle;
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

	void Transform::adjustRotationAngle(const float delta) noexcept
	{
		setRotationAngle(__rotation.first + delta);
	}

	void Transform::calcModelMatrix(const mat4 &parentModelMat, mat4 &retVal) noexcept
	{
		retVal = translate(parentModelMat, __pos);
		retVal = rotate(retVal, __rotation.first, __rotation.second);
		retVal = scale(retVal, __scale);
	}
}