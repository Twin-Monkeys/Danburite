#pragma once

#include "Animation.h"
#include "Transform.h"

namespace Danburite
{
	class AnimatableTransform : public Transform
	{
	private:
		Animation __animation;

	protected:
		virtual void _onUpdateTranslationMatrix(glm::mat4 &translationMat) noexcept;
		virtual void _onUpdateScaleMatrix(glm::mat4 &scaleMat) noexcept;
		virtual void _onUpdateRotationMatrix(glm::mat4 &rotationMat) noexcept;

	public:
		constexpr Animation &getAnimation() noexcept;
		constexpr const Animation &getAnimation() const noexcept;

		glm::vec3 getAnimatedPosition() const noexcept;
		glm::vec3 getAnimatedScale() const noexcept;
		Quaternion getAnimatedRotation() const noexcept;

		virtual void updateMatrix(const float deltaTime) noexcept;
	};

	constexpr Animation &AnimatableTransform::getAnimation() noexcept
	{
		return __animation;
	}

	constexpr const Animation &AnimatableTransform::getAnimation() const noexcept
	{
		return __animation;
	}
}
