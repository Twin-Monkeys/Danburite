#include "PointLight.h"
#include "VertexArrayFactory.h"
#include "RawDrawcallMaterial.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	PointLight::PointLight(const LightType type) :
		PerspectiveLight(type)
	{
		setLuminanceTolerance(Constant::Light::AttenuatedComponent::LUMINANCE_TOLERANCE);

		const shared_ptr<VertexArray> &pVolumeVA =
			VertexArrayFactory::createSphere(VertexAttributeFlag::POS, 1.f, 9ULL, 18ULL);

		const shared_ptr<RawDrawcallMaterial> &pVolumeMaterial =
			make_shared<RawDrawcallMaterial>(VertexAttributeFlag::POS);

		__pVolume->createNode(pVolumeVA, pVolumeMaterial);
	}

	PointLight::PointLight() :
		PerspectiveLight(LightType::POINT)
	{}

	void PointLight::__setValidDistance() noexcept
	{
		/*
			parameter:
			luminanceTolerance, albedo,
			ambient/diffuse/specular strength,
			constant/linear/quadratic attenuation
		*/
		_setValidDistance(
			__luminanceTolerance, getAlbedo(),
			getAmbientStrength(), getDiffuseStrength(), getSpecularStrength());

		__pVolume->getTransform().setScale(_getValidDistance());
	}

	void PointLight::_onDeploy(LightUniformSetter &lightSetter) noexcept
	{
		_deployBaseComponent(lightSetter);
		_deployAttenuatedComponent(lightSetter);
		_deployPosition(lightSetter);
	}

	void PointLight::setLuminanceTolerance(const float tolerance) noexcept
	{
		__luminanceTolerance = tolerance;
		__setValidDistance();
	}

	void PointLight::setAlbedo(const vec3 &albedo) noexcept
	{
		LightBaseComponent::setAlbedo(albedo);
		__setValidDistance();
	}

	void PointLight::setAmbientStrength(const float strength) noexcept
	{
		LightBaseComponent::setAmbientStrength(strength);
		__setValidDistance();
	}

	void PointLight::setDiffuseStrength(const float strength) noexcept
	{
		LightBaseComponent::setDiffuseStrength(strength);
		__setValidDistance();
	}

	void PointLight::setSpecularStrength(const float strength) noexcept
	{
		LightBaseComponent::setSpecularStrength(strength);
		__setValidDistance();
	}

	void PointLight::setAttenuation(const float constant, const float linear, const float quadratic) noexcept
	{
		AttenuatedLightComponent::setAttenuation(constant, linear, quadratic);
		__setValidDistance();
	}

	void PointLight::volumeDrawcall() noexcept
	{
		__pVolume->rawDrawcall();
	}
}
