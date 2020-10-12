#include "PointLight.h"
#include "VertexArrayFactory.h"
#include "RawDrawcallMaterial.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	PointLight::PointLight(const LightType type, const GLuint index) :
		PerspectiveLight(type, index)
	{
		const shared_ptr<VertexArray> &pVolumeVA =
			VertexArrayFactory::createTweakedTwinSphere(VertexAttributeFlag::POS, 1.f);

		const shared_ptr<RawDrawcallMaterial> &pVolumeMaterial =
			make_shared<RawDrawcallMaterial>(VertexAttributeFlag::POS);

		__pVolume->createNode(pVolumeVA, pVolumeMaterial);

		__lightingVolumeSetup.setup([this](ContextStateManager &stateMgr)
		{
			stateMgr.setState(GLStateType::DEPTH_TEST, false);
			stateMgr.setState(GLStateType::CULL_FACE, true);
			stateMgr.setCulledFace(FacetType::FRONT);
		});

		setLuminanceTolerance(Constant::Light::AttenuatedComponent::LUMINANCE_TOLERANCE);
	}

	PointLight::PointLight(const GLuint index) :
		PointLight(LightType::POINT, index)
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

	void PointLight::_onDeploy(LightUniformInterface &lightUI) noexcept
	{
		const GLuint lightIdx = getIndex();

		_deployBaseComponent(lightIdx, lightUI);
		_deployAttenuatedComponent(lightIdx, lightUI);
		_deployPosition(lightUI);
	}

	void PointLight::_onVolumeDrawcall() noexcept
	{
		__lightingVolumeSetup();
		__pVolume->rawDrawcall();
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

	void PointLight::update(const float delta) noexcept
	{
		PerspectiveLight::update(delta);

		__pVolume->getTransform().setPosition(getTransform().getPosition());
		__pVolume->update(delta);
	}
}
