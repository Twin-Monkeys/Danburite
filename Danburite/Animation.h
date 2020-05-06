#pragma once

#include "Transform.h"
#include <map>
#include "Constant.h"

namespace Danburite
{
	class Animation
	{
	private:
		static constexpr inline TransformComponent __DEFAULT_STATE {};

		std::map<float, TransformComponent> __keyframes;

		float __timestamp = 0.f;
		float __playTime = 0.f;

		Transform __currentTransform;

		void __validateTimestamp() noexcept;

	public:
		Animation &addKeyframe(const float timestamp, const TransformComponent &transformComponent) noexcept;
		Animation &addKeyframe(
			const float timestamp,
			const glm::vec3 &position, const glm::vec3 &scale, const Quaternion &rotation) noexcept;

		constexpr Animation &setTimestamp(const float timestamp) noexcept;
		constexpr Animation &adjustTimestamp(const float deltaTime) noexcept;

		constexpr Animation &rewind() noexcept;
		constexpr Animation &moveToEnd() noexcept;

		void updateMatrix() noexcept;
	};

	constexpr Animation &Animation::setTimestamp(const float timestamp) noexcept
	{
		__timestamp = timestamp;
		return *this;
	}

	constexpr Animation &Animation::adjustTimestamp(const float deltaTime) noexcept
	{
		return setTimestamp(__timestamp + deltaTime);
	}

	constexpr Animation &Animation::rewind() noexcept
	{
		return setTimestamp(0.f);
	}

	constexpr Animation &Animation::moveToEnd() noexcept
	{
		return setTimestamp(__playTime - Constant::Common::EPSILON);
	}
}
