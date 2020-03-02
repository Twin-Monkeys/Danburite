#include "LightDeployer.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void LightDeployer::addLight(const weak_ptr<Light> &pLight) noexcept
	{
		__lights.add(pLight);
	}

	void LightDeployer::batchDeploy() noexcept
	{
		__lights.safeTraverse(&Light::selfDeploy);
	}

	void LightDeployer::batchBakeDepthMap() noexcept
	{
		__lights.safeTraverse(&Light::bakeDepthMap);
	}
}