#pragma once

#include <unordered_map>
#include <memory>
#include "SceneNodeConnecterManager.h"
#include "Object.h"
#include "AnimationPlayingOrderType.h"
#include "AnimationRepeatType.h"

namespace Danburite
{
	class Animation : public ObjectGL::Object<size_t>
	{
	private:
		const float __playTime;
		float __timestamp = 0.f;

		AnimationPlayingOrderType __playingOrderType = AnimationPlayingOrderType::FORWARD;
		AnimationRepeatType __animationRepeatType = AnimationRepeatType::ONE_WAY;

		float __playSpeed = 1.f;
		int __repCnt = 0;

		const std::string __name;
		SceneNodeConnecterManager __connecterMgr;

	public:
		Animation(const size_t id, const float playTime, const std::string &name = "") noexcept;

		constexpr float getPlayTime() const noexcept;
		constexpr const std::string &getName() const noexcept;

		constexpr SceneNodeConnecterManager& getConnecterManager() noexcept;
		constexpr const SceneNodeConnecterManager &getConnecterManager() const noexcept;

		Animation &setTimestamp(const float timestamp) noexcept;
		Animation &adjustTimestamp(const float deltaTime) noexcept;

		constexpr float getPlaySpeed() const noexcept;
		constexpr Animation &setPlaySpeed(const float speed) noexcept;

		constexpr AnimationPlayingOrderType getPlayingOrder() const noexcept;
		constexpr void setPlayingOrder(const AnimationPlayingOrderType type, const bool rewindIfChanged = true) noexcept;

		constexpr AnimationRepeatType getAnimationRepeatType() const noexcept;
		constexpr void setAnimationRepeatType(const AnimationRepeatType type) noexcept;

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

	constexpr SceneNodeConnecterManager& Animation::getConnecterManager() noexcept
	{
		return __connecterMgr;
	}

	constexpr const SceneNodeConnecterManager& Animation::getConnecterManager() const noexcept
	{
		return __connecterMgr;
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

	constexpr void Animation::setPlayingOrder(const AnimationPlayingOrderType type, const bool rewindIfChanged) noexcept
	{
		if (__playingOrderType == type)
			return;

		__playingOrderType = type;

		if (!rewindIfChanged)
			return;

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

	constexpr AnimationRepeatType Animation::getAnimationRepeatType() const noexcept
	{
		return __animationRepeatType;
	}

	constexpr void Animation::setAnimationRepeatType(const AnimationRepeatType type) noexcept
	{
		__animationRepeatType = type;
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
