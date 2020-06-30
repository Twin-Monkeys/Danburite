#include "AnimatingSceneNodeConnecter.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	AnimatingSceneNodeConnecter::AnimatingSceneNodeConnecter(const string_view &name, const float &timestampReference) noexcept :
		SceneNodeConnecterBase(name), __timestampRef(timestampReference)
	{}

	void AnimatingSceneNodeConnecter::_onUpdateLocalMatrix(mat4 &localConnectingMat) noexcept
	{
		const auto &[position, rotation, scale] = __timeline.sample(__timestampRef);
		localConnectingMat = Transform::calcMatrix(position, rotation, scale);
	}
}