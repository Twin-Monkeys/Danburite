#include "JointBase.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	JointBase::JointBase(const string_view &name) noexcept :
		__name(name)
	{}

	JointBase &JointBase::updateMatrix() noexcept
	{
		_onUpdateMatrix(__targetJointMat);
		__observers.safeTraverse(&JointUpdateObserver::onUpdateJointMatrix, __name, __targetJointMat);
		return *this;
	}
}