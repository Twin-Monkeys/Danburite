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

		AnimationNode &getNode(const std::string &nodeName) noexcept;
		const AnimationNode &getNode(const std::string &nodeName) const noexcept;

		bool isExistentNode(const std::string &nodeName) const noexcept;

		Animation &setTimestamp(const float timestamp) noexcept;
		Animation &adjustTimestamp(const float deltaTime) noexcept;
	};

	constexpr float Animation::getPlayTime() const noexcept
	{
		return __playTime;
	}

	constexpr const std::string &Animation::getName() const noexcept
	{
		return __name;
	}
}
