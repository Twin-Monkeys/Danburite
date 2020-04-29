#pragma once

#include "TransformComponent.h"
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

		TransformComponent __currentComponent;

		void __validateTimestamp() noexcept;

	public:
		constexpr const TransformComponent &getCurrentState() const noexcept;

		Animation &addKeyframe(const float timestamp, const TransformComponent &transformComponent) noexcept;
		Animation &addKeyframe(
			const float timestamp,
			const glm::vec3 &position, const glm::vec3 &scale, const Quaternion &rotation) noexcept;

		constexpr Animation &setTimestamp(const float timestamp) noexcept;
		constexpr Animation &adjustTimestamp(const float deltaTime) noexcept;

		constexpr Animation &rewind() noexcept;
		constexpr Animation &moveToEnd() noexcept;

		void updateState() noexcept;
	};

	constexpr const TransformComponent &Animation::getCurrentState() const noexcept
	{
		return __currentComponent;
	}

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
