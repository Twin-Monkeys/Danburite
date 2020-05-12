#pragma once

#include "Transform.h"
#include <map>
#include "Constant.h"
#include "WeakPointerContainer.h"

namespace Danburite
{
	class Bone
	{
	private:
		static constexpr inline TransformComponent __DEFAULT_STATE {};

		std::map<float, TransformComponent> __keyframes;

		float __timestamp = 0.f;

		Transform __currentTransform;
		ObjectGL::WeakPointerContainer<Bone> __children;

		float &__playTime;
		glm::mat4 &__boneMat;

		glm::mat4 __offsetMat		{ 1.f };
		glm::mat4 __offsetInvMat	{ 1.f };

		void __validateTimestamp() noexcept;
		void __updateTransform() noexcept;

	public:
		explicit Bone(float &playTimeReference, glm::mat4& boneMatrixReference) noexcept;

		Bone &addKeyframe(const float timestamp, const TransformComponent &transformComponent) noexcept;
		Bone &addKeyframe(
			const float timestamp,
			const glm::vec3 &position, const glm::vec3 &scale, const Quaternion &rotation) noexcept;

		Bone &setTimestamp(const float timestamp) noexcept;
		Bone &adjustTimestamp(const float deltaTime) noexcept;

		Bone &rewind() noexcept;
		Bone &moveToEnd() noexcept;

		void updateMatrix() noexcept;
		void updateMatrix(const glm::mat4 &parentMatrix) noexcept;

		void setOffsetMatrix(const glm::mat4 &offsetMatrix) noexcept;

		constexpr const glm::mat4 &getBoneMatrix() const noexcept;

		constexpr ObjectGL::WeakPointerContainer<Bone> &getChildren() noexcept;
		constexpr const ObjectGL::WeakPointerContainer<Bone> &getChildren() const noexcept;
	};

	constexpr const glm::mat4 &Bone::getBoneMatrix() const noexcept
	{
		return __boneMat;
	}

	constexpr ObjectGL::WeakPointerContainer<Bone> &Bone::getChildren() noexcept
	{
		return __children;
	}

	constexpr const ObjectGL::WeakPointerContainer<Bone> &Bone::getChildren() const noexcept
	{
		return __children;
	}
}
