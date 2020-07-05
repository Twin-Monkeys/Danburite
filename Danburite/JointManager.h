#pragma once

#include "Joint.h"

namespace Danburite
{
	class JointManager
	{
	private:
		AnimationManager &__animMgr;
		std::vector<std::unique_ptr<Joint>> __joints;
		std::unordered_map<std::string, Joint *> __nameToJointMap;

	public:
		JointManager(AnimationManager &animationManager) noexcept;

		Joint &createJoint(const std::string &nodeName) noexcept;
		Joint *getJoint(const std::string &nodeName) noexcept;
		const Joint *getJoint(const std::string &nodeName) const noexcept;
	};
}