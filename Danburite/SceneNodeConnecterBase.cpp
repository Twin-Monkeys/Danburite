#include "SceneNodeConnecterBase.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	SceneNodeConnecterBase::SceneNodeConnecterBase(const string_view &nodeName) noexcept :
		__nodeName(nodeName)
	{}

	SceneNodeConnecterBase &SceneNodeConnecterBase::updateMatrix() noexcept
	{
		_onUpdateLocalMatrix(__connectingMat);
		return *this;
	}
}