#pragma once

#include <unordered_map>
#include "BoneNode.h"
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

		std::unordered_map<std::string, BoneNode> __boneNodeMap;

	public:
		Animation(const size_t id, const float playTime, const std::string &name = "") noexcept;

		constexpr float getPlayTime() const noexcept;
		constexpr const std::string &getName() const noexcept;

		BoneNode &createBoneNode(const std::string &name) noexcept;

		BoneNode *getBoneNode(const std::string &name) noexcept;
		const BoneNode *getBoneNode(const std::string &name) const noexcept;

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
