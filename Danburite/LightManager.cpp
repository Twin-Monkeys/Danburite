#include "LightManager.h"

using namespace std;

namespace Danburite
{
	void LightManager::deleteLight(const Light &light) noexcept
	{
		auto targetIt = (__lights.begin() + light.getIndex());
		targetIt = __lights.erase(targetIt);

		for (auto it = targetIt; it != __lights.end(); it++)
		{
			Light &curLight = *(*it);
			curLight.setIndex(curLight.getIndex() - 1);
		}
	}
}