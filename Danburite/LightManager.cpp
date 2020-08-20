#include "LightManager.h"

using namespace std;
using namespace ObjectGL;

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

	void LightManager::selfDeploy() noexcept
	{
		__lightSetter.setUniformUint(
			ShaderIdentifier::Name::Light::NUM_LIGHTS, GLuint(__lights.size()));

		process(&Light::selfDeploy);
	}
}