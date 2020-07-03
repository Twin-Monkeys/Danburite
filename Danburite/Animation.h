#pragma once

#include <unordered_map>
#include <memory>
#include "AnimatingSceneNodeConnecter.h"
#include "StaticSceneNodeConnecter.h"
#include "Object.h"
#include "AnimationPlayingOrderType.h"

namespace Danburite
{
	class Animation : public ObjectGL::Object<size_t>
	{
	private:
		const float __playTime;
		float __timestamp = 0.f;

		AnimationPlayingOrderType __playingOrderType = AnimationPlayingOrderType::FORWARD;
		float __playSpeed = 1.f;
		int __repCnt = 0;

		const std::string __name;

		std::unordered_map<std::string, std::unique_ptr<SceneNodeConnecterBase>> __connecterMap;

	public:
		Animation(const size_t id, const float playTime, const std::string &name = "") noexcept;

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

		constexpr AnimationPlayingOrderType getPlayingOrder() const noexcept;
		constexpr void setPlayingOrder(const AnimationPlayingOrderType type) noexcept;

		constexpr int getRepeatCount() const noexcept;
		constexpr Animation &setRepeatCount(const int count) noexcept;
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

	constexpr AnimationPlayingOrderType Animation::getPlayingOrder() const noexcept
	{
		return __playingOrderType;
	}

	constexpr void Animation::setPlayingOrder(const AnimationPlayingOrderType type) noexcept
	{
		__playingOrderType = type;
		switch (type)
		{
		case AnimationPlayingOrderType::FORWARD:
			__timestamp = 0.f;
			break;

		case AnimationPlayingOrderType::REVERSE:
			__timestamp = __playTime;
			break;
		}
	}

	constexpr int Animation::getRepeatCount() const noexcept
	{
		return __repCnt;
	}

	constexpr Animation &Animation::setRepeatCount(const int count) noexcept
	{
		__repCnt = count;
		return *this;
	}
}
