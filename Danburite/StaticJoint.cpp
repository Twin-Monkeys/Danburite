#include "StaticJoint.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	StaticJoint::StaticJoint(const string_view &name, const mat4 &localJointMatrix) noexcept :
		JointBase(name), __localJointMat(localJointMatrix)
	{}

	void StaticJoint::_onUpdateMatrix(mat4 &jointMat) noexcept
	{
		jointMat = __localJointMat;
	}
}