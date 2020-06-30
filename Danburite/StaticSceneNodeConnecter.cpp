#include "StaticSceneNodeConnecter.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	StaticSceneNodeConnecter::StaticSceneNodeConnecter(const string_view &name, const mat4 &localConnectingMatrix) noexcept :
		SceneNodeConnecterBase(name), __localConnectingMat(localConnectingMatrix)
	{}

	void StaticSceneNodeConnecter::_onUpdateLocalMatrix(mat4 &localConnectingMatrix) noexcept
	{
		localConnectingMatrix = __localConnectingMat;
	}
}