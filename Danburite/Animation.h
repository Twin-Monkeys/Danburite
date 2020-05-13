#pragma once

#include "Updatable.h"
#include "Constant.h"
#include "Bone.h"
#include "UniformBuffer.h"

namespace Danburite
{
	class Animation : public Updatable
	{
	private:
		const GLuint __NUM_BONES;
		GLuint __rootIdx = 0U;

		float __playTime = 0.f;

		std::vector<glm::mat4> __boneMatrices;
		std::vector<std::shared_ptr<Bone>> __bones;

		ObjectGL::UniformBuffer &__animSetter;

	public:
		Animation(const GLuint numBones);
		virtual ~Animation() = default;

		constexpr GLuint getNumBones() const noexcept;

		void selfDeploy() const noexcept;

		std::shared_ptr<Bone> getBone(const GLuint index) noexcept;
		std::shared_ptr<const Bone> getBone(const GLuint index) const noexcept;

		constexpr GLuint getRootBone() const noexcept;
		constexpr Animation &setRootBone(const GLuint rootIndex) noexcept;

		virtual void update(const float deltaTime) noexcept override;
	};

	constexpr GLuint Animation::getNumBones() const noexcept
	{
		return __NUM_BONES;
	}

	constexpr GLuint Animation::getRootBone() const noexcept
	{
		return __rootIdx;
	}

	constexpr Animation &Animation::setRootBone(const GLuint rootIndex) noexcept
	{
		__rootIdx = rootIndex;
		return *this;
	}
}