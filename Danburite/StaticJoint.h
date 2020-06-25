#pragma once

#include "JointBase.h"

namespace Danburite
{
	class StaticJoint : public JointBase
	{
	private:
		const glm::mat4 __localJointMat;

	protected:
		virtual void _onUpdateMatrix(glm::mat4 &jointMat) noexcept override;

	public:
		StaticJoint(const std::string_view &name, const glm::mat4 &localJointMatrix) noexcept;
	};
}
