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
		_onUpdateMatrix(__jointMat);
		return *this;
	}
}