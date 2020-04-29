#pragma once

#include "Animation.h"
#include "Transform.h"

namespace Danburite
{
	class AnimatableTransform : public Transform
	{
	private:
		Animation __animation;
		TransformComponent __animatedTransformComponent;

	public:
		constexpr Animation &getAnimation() noexcept;
		constexpr const Animation &getAnimation() const noexcept;

		constexpr const glm::vec3 &getAnimatedPosition() const noexcept;
		constexpr const glm::vec3 &getAnimatedScale() const noexcept;
		constexpr const Quaternion &getAnimatedRotation() const noexcept;

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

	constexpr const glm::vec3 &AnimatableTransform::getAnimatedPosition() const noexcept
	{
		return __animatedTransformComponent.position;
	}

	constexpr const glm::vec3 &AnimatableTransform::getAnimatedScale() const noexcept
	{
		return __animatedTransformComponent.scale;
	}

	constexpr const Quaternion &AnimatableTransform::getAnimatedRotation() const noexcept
	{
		return __animatedTransformComponent.rotation;
	}
}
