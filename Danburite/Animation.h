#pragma once

#include <unordered_map>
#include <memory>
#include "AnimatingJoint.h"
#include "StaticJoint.h"
#include "Object.h"

namespace Danburite
{
	class Animation : public ObjectGL::Object<size_t>
	{
	private:
		const float __playTime;
		float __timestamp = 0.f;

		float __playSpeed = 1.f;

		const std::string __name;

		const std::weak_ptr<JointUpdateObserver> __pDefaultJointUpdateObserver;
		std::unordered_map<std::string, std::unique_ptr<JointBase>> __jointMap;

	public:
		Animation(
			const size_t id, const float playTime,
			const std::weak_ptr<JointUpdateObserver> &pDefaultJointUpdateObserver = {},
			const std::string &name = "") noexcept;

		constexpr float getPlayTime() const noexcept;
		constexpr const std::string &getName() const noexcept;

		AnimatingJoint &createAnimatingJoint(const std::string &name) noexcept;
		StaticJoint &createStaticJoint(const std::string &name, const glm::mat4 &localJointMatrix) noexcept;

		JointBase *getJoint(const std::string &name) noexcept;
		const JointBase *getJoint(const std::string &name) const noexcept;

		Animation &setTimestamp(const float timestamp) noexcept;
		Animation &adjustTimestamp(const float deltaTime) noexcept;

		constexpr float getPlaySpeed() const noexcept;
		constexpr Animation &setPlaySpeed(const float speed) noexcept;
	};

	constexpr float Animation::getPlayTime() const noexcept
	{
		return __playTime;
	}

	constexpr const std::string &Animation::getName() const noexcept
	{
		return __name;
	}

	constexpr float Animation::getPlaySpeed() const noexcept
	{
		return __playSpeed;
	}

	constexpr Animation &Animation::setPlaySpeed(const float speed) noexcept
	{
		__playSpeed = speed;
		return *this;
	}
}
