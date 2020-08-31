#include "LightBaseComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	void LightBaseComponent::_deployBaseComponent(const size_t lightIndex, DeferredUniformBuffer<LightUniformInterface> &lightUB) noexcept
	{
		LightUniformInterface &lightUniformInterface = lightUB.getInterface();

		lightUniformInterface.albedo.set(lightIndex, __albedo);
		lightUniformInterface.ambientStrength.set(lightIndex, __ambientStrength);
		lightUniformInterface.diffuseStrength.set(lightIndex, __diffuseStrength);
		lightUniformInterface.specularStrength.set(lightIndex, __specularStrength);
	}

	void LightBaseComponent::setAlbedo(const glm::vec3 &albedo) noexcept
	{
		__albedo = albedo;
	}

	void LightBaseComponent::setAlbedo(const float r, const float g, const float b) noexcept
	{
		setAlbedo({ r, g, b });
	}

	void LightBaseComponent::setAmbientStrength(const float strength) noexcept
	{
		__ambientStrength = strength;
	}

	void LightBaseComponent::setDiffuseStrength(const float strength) noexcept
	{
		__diffuseStrength = strength;
	}

	void LightBaseComponent::setSpecularStrength(const float strength) noexcept
	{
		__specularStrength = strength;
	}
}