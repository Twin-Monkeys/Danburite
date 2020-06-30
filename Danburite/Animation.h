#pragma once

#include <unordered_map>
#include <memory>
#include "AnimatingSceneNodeConnecter.h"
#include "StaticSceneNodeConnecter.h"
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
		std::unordered_map<std::string, std::unique_ptr<SceneNodeConnecterBase>> __connecterMap;

	public:
		Animation(
			const size_t id, const float playTime,
			const std::weak_ptr<JointUpdateObserver> &pDefaultJointUpdateObserver = {},
			const std::string &name = "") noexcept;

		constexpr float getPlayTime() const noexcept;
		constexpr const std::string &getName() const noexcept;

		AnimatingSceneNodeConnecter &createAnimatingSceneNodeConnecter(const std::string &nodeName) noexcept;
		StaticSceneNodeConnecter &createStaticSceneNodeConnecter(const std::string &nodeName, const glm::mat4 &localConnectingMat) noexcept;

		SceneNodeConnecterBase *getSceneNodeConnecter(const std::string &nodeName) noexcept;
		const SceneNodeConnecterBase *getSceneNodeConnecter(const std::string &nodeName) const noexcept;

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
