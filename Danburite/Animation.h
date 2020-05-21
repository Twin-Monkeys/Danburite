#pragma once

#include <unordered_map>
#include "Bone.h"
#include "Object.h"

namespace Danburite
{
	class Animation : public ObjectGL::Object<size_t>
	{
	private:
		const float __playTime;
		float __timestamp = 0.f;

		const std::string __name;

		std::unordered_map<std::string, Bone> __boneMap;
		Bone *__pRootBone = nullptr;

	public:
		Animation(const size_t id, const float playTime, const std::string &name = "") noexcept;

		constexpr float getPlayTime() const noexcept;
		constexpr const std::string &getName() const noexcept;

		Bone &createBone(const std::string &name) noexcept;

		Bone *getBone(const std::string &name) noexcept;
		const Bone *getBone(const std::string &name) const noexcept;

		constexpr Bone *getRootBone() noexcept;
		constexpr const Bone *getRootBone() const noexcept;

		constexpr void setRootBone(Bone *const pBone) noexcept;

		void updateBones() noexcept;

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

	constexpr Bone *Animation::getRootBone() noexcept
	{
		return __pRootBone;
	}

	constexpr const Bone *Animation::getRootBone() const noexcept
	{
		return __pRootBone;
	}

	constexpr void Animation::setRootBone(Bone *const pBone) noexcept
	{
		__pRootBone = pBone;
	}
}
