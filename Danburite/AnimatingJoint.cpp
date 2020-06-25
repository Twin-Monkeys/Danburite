#include "AnimatingJoint.h"
#include "Transform.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	AnimatingJoint::AnimatingJoint(const string_view &name, const float &timestampReference) noexcept :
		JointBase(name), __timestampRef(timestampReference)
	{}

	void AnimatingJoint::_onUpdateMatrix(mat4 &jointMat) noexcept
	{
		const auto &[position, rotation, scale] = __timeline.sample(__timestampRef);
		jointMat = Transform::calcModelMatrix(position, rotation, scale);
	}
}