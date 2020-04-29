#include "AnimatableTransform.h"
#include "Constant.h"
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;

namespace Danburite
{
	void AnimatableTransform::_onUpdateTranslationMatrix(mat4 &translationMat) noexcept
	{
		Transform::_onUpdateRotationMatrix(translationMat);
	}

	void AnimatableTransform::_onUpdateScaleMatrix(mat4 &scaleMat) noexcept
	{
		Transform::_onUpdateScaleMatrix(scaleMat);
	}
	
	void AnimatableTransform::_onUpdateRotationMatrix(mat4 &rotationMat) noexcept
	{
		Transform::_onUpdateRotationMatrix(rotationMat);
	}

	vec3 AnimatableTransform::getAnimatedPosition() const noexcept
	{
		return (getPosition() + __animation.getCurrentState().position);
	}

	glm::vec3 AnimatableTransform::getAnimatedScale() const noexcept
	{
		return (getScale() * __animation.getCurrentState().scale);
	}

	Quaternion AnimatableTransform::getAnimatedRotation() const noexcept
	{
		return (getRotation() * __animation.getCurrentState().rotation);
	}

	void AnimatableTransform::updateMatrix(const float deltaTime) noexcept
	{
		__animation.update(deltaTime);
		Transform::updateMatrix(deltaTime);
	}
}