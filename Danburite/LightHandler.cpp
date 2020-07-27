#include "LightHandler.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void LightHandler::addLight(const weak_ptr<Light> &pLight) noexcept
	{
		__lights.add(pLight);
	}

	void LightHandler::batchDeploy() noexcept
	{
		__lights.safeTraverse(&Light::selfDeploy);
	}

	void LightHandler::batchBakeDepthMap(Drawer &drawer) noexcept
	{
		__lights.safeTraverse(&Light::bakeDepthMap, drawer);
	}

	void LightHandler::batchVolumeDrawcall() noexcept
	{
		__lights.safeTraverse(&Light::volumeDrawcall);
	}
}