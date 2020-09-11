#include "Light.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Light::Light(
		const LightType type, const LightVolumeType volumeType,
		const DepthBakingType depthBakingType, const GLuint index) :
		__TYPE { GLuint(type) }, __VOLUME_TYPE { GLuint(volumeType) },
		__DEPTH_BAKING_TYPE { GLuint(depthBakingType) }, __index { index }
	{
		setIndex(index);
	}

	void Light::__release() noexcept
	{
		setEnabled(false);
	}

	void Light::selfDeploy() noexcept
	{
		LightUniformInterface &lightUniformInterface = __lightUB.getInterface();

		lightUniformInterface.enabled = { __index, GLuint(__enabled) };
		if (!__enabled)
			return;

		lightUniformInterface.type = { __index, __TYPE };
		lightUniformInterface.depthBakingType = { __index, __DEPTH_BAKING_TYPE };
		_onDeploy(lightUniformInterface);

		lightUniformInterface.shadowEnabled = { __index, GLuint(__shadowEnabled) };
		if (!__shadowEnabled)
			return;

		_onDeployShadowData(lightUniformInterface);
	}

	void Light::setShadowEnabled(const bool enabled) noexcept
	{
		__shadowEnabled = enabled;
		_onChangeShadowEnabled(enabled);
	}

	void Light::bakeDepthMap(BatchProcessor<SceneObject> &drawer) noexcept
	{
		if (!isShadowEnabled())
			return;

		_onBakeDepthMap(drawer);
	}

	void Light::volumeDrawcall() noexcept
	{
		LightPrePassUniformInterface &lightPrepassUniformInterface = __lightPrepassUB.getInterface();
		lightPrepassUniformInterface.currentLightIdx = getIndex();
		lightPrepassUniformInterface.lightVolumeType = __VOLUME_TYPE;

		__lightPrepassUB.selfDeploy();
		_onVolumeDrawcall();
	}

	Light::~Light() noexcept
	{
		__release();
	}
}
