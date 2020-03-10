#include "DirectionalLight.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DirectionalLight::DirectionalLight(UniformSetter &uniformSetter) noexcept :
		OrthoLight(uniformSetter, LightType::DIRECTIONAL)
	{}

	void DirectionalLight::_onDeploy(LightUniformSetter &target) noexcept
	{
		LightBaseComponent::_onDeploy(target);

		CameraTransform &transform = getTransform();
		const vec4 &forward = transform.getForward();

		target.setUniformVec3(
			ShaderIdentifier::Name::Light::DIRECTION, -forward.x, -forward.y, -forward.z);
	}
}
