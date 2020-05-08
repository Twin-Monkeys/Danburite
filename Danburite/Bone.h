#pragma once

#include "Transform.h"
#include <map>
#include "Constant.h"
#include "WeakPointerContainer.h"

namespace Danburite
{
	class Bone
	{
	private:
		static constexpr inline TransformComponent __DEFAULT_STATE {};

		std::map<float, TransformComponent> __keyframes;

		float __timestamp = 0.f;
		float __playTime = 0.f;

		Transform __currentTransform;
		ObjectGL::WeakPointerContainer<Bone> __children;

		void __validateTimestamp() noexcept;

	public:
		Bone &addKeyframe(const float timestamp, const TransformComponent &transformComponent) noexcept;
		Bone &addKeyframe(
			const float timestamp,
			const glm::vec3 &position, const glm::vec3 &scale, const Quaternion &rotation) noexcept;

		constexpr Bone &setTimestamp(const float timestamp) noexcept;
		constexpr Bone &adjustTimestamp(const float deltaTime) noexcept;

		constexpr Bone &rewind() noexcept;
		constexpr Bone &moveToEnd() noexcept;

		void updateMatrix() noexcept;
	};

	constexpr Bone &Bone::setTimestamp(const float timestamp) noexcept
	{
		__timestamp = timestamp;
		return *this;
	}

	constexpr Bone &Bone::adjustTimestamp(const float deltaTime) noexcept
	{
		return setTimestamp(__timestamp + deltaTime);
	}

	constexpr Bone &Bone::rewind() noexcept
	{
		return setTimestamp(0.f);
	}

	constexpr Bone &Bone::moveToEnd() noexcept
	{
		return setTimestamp(__playTime - Constant::Common::EPSILON);
	}
}
