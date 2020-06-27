#pragma once

#include "Animation.h"
#include "BoneManager.h"
#include <memory>

namespace Danburite
{
	class AnimationManager : public std::enable_shared_from_this<AnimationManager>, public JointUpdateObserver
	{
	private:
		std::vector<std::unique_ptr<Animation>> __animations;
		size_t __activeAnimID = 0ULL;

		std::vector<std::unique_ptr<BoneManager>> __boneMgrs;

	public:
		Animation &createAnimation(const float playTime, const std::string &name = "") noexcept;
		Animation &getAnimation(const size_t id = 0U) noexcept;
		const Animation &getAnimation(const size_t id = 0U) const noexcept;

		size_t getNumAnimations() const noexcept;

		bool activateAnimation(const size_t animationID) noexcept;

		Animation *getActiveAnimation() noexcept;
		const Animation *getActiveAnimation() const noexcept;

		BoneManager &createBoneManager() noexcept;

		virtual void onUpdateJointMatrix(
			const std::string &jointName, const glm::mat4 &jointMatrix) noexcept override;
	};
}
