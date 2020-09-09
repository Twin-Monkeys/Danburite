#include "SpotLight.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SpotLight::SpotLight(const GLuint index) :
		PointLight(LightType::SPOT, index)
	{}

	void SpotLight::_onDeploy(LightUniformInterface &lightUI) noexcept
	{
		PointLight::_onDeploy(lightUI);
		_deploySpotComponent(getIndex(), lightUI);
		_deployDirection(lightUI);
	}
}