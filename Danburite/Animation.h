#pragma once

#include <unordered_map>
#include "AnimationNode.h"
#include "Object.h"

namespace Danburite
{
	class Animation : public ObjectGL::Object<size_t>
	{
	private:
		const float __playTime;
		float __timestamp = 0.f;

		const std::string __name;

		std::unordered_map<std::string, AnimationNode> __nodeMap;

	public:
		Animation(const size_t id, const float playTime, const std::string &name = "") noexcept;

		constexpr float getPlayTime() const noexcept;
		constexpr const std::string &getName() const noexcept;

		AnimationNode &createNode(const std::string &nodeName) noexcept;

		AnimationNode *getNode(const std::string &nodeName) noexcept;
		const AnimationNode *getNode(const std::string &nodeName) const noexcept;

		constexpr Animation &setTimestamp(const float timestamp) noexcept;
		constexpr Animation &adjustTimestamp(const float deltaTime) noexcept;

		void updateNodes() noexcept;
	};

	constexpr float Animation::getPlayTime() const noexcept
	{
		return __playTime;
	}

	constexpr const std::string &Animation::getName() const noexcept
	{
		return __name;
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
}
