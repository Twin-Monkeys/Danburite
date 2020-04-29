#pragma once

#include "TransformComponent.h"
#include "Updatable.h"
#include <map>

namespace Danburite
{
	class Animation : public Updatable
	{
	private:
		static constexpr inline TransformComponent __DEFAULT_STATE {};

		std::map<float, TransformComponent> __keyframes;

		float __timestamp = 0.f;
		float __playTime = 0.f;

		TransformComponent __currentComponent;

	public:
		constexpr const TransformComponent &getCurrentState() const noexcept;
		void addKeyframe(const float timestamp, const TransformComponent &transformComponent) noexcept;
		void addKeyframe(
			const float timestamp,
			const glm::vec3 &position, const glm::vec3 &scale, const Quaternion &rotation) noexcept;

		virtual void update(const float deltaTime) noexcept override;
	};

	constexpr const TransformComponent &Animation::getCurrentState() const noexcept
	{
		return __currentComponent;
	}
}
