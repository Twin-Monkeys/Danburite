#include "Light.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Light::Light(const LightType type, const DepthBakingType depthBakingType, const GLuint index) :
		__TYPE(GLenum(type)), __DEPTH_BAKING_TYPE(GLenum(depthBakingType)),

		__lightSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::LIGHT), index),

		__lightPrePassSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::LIGHT_PREPASS))
	{
		setIndex(index);
	}

	void Light::__release() noexcept
	{
		setEnabled(false);
	}

	void Light::selfDeploy() noexcept
	{
		__lightSetter.setUniformUint(ShaderIdentifier::Name::Light::TYPE, __TYPE);
		__lightSetter.setUniformUint(ShaderIdentifier::Name::Light::DEPTH_BAKING_TYPE, __DEPTH_BAKING_TYPE);
		__lightSetter.setUniformBool(ShaderIdentifier::Name::Light::ENABLED, __enabled);

		if (!__enabled)
			return;

		_onDeploy(__lightSetter);

		__lightSetter.setUniformBool(ShaderIdentifier::Name::Light::SHADOW_ENABLED, __shadowEnabled);
		if (!__shadowEnabled)
			return;

		_onDeployShadowData(__lightSetter);
	}

	void Light::setIndex(const GLuint index) noexcept
	{
		__lightSetter.setIndex(index);
	}

	void Light::bakeDepthMap(BatchProcessor<Drawable> &drawer) noexcept
	{
		if (!isShadowEnabled())
			return;

		_onBakeDepthMap(drawer);
	}

	void Light::volumeDrawcall() noexcept
	{
		__lightPrePassSetter.setUniformUint(
			ShaderIdentifier::Name::LightPrePass::CURRENT_LIGHT_IDX, getIndex());

		_onVolumeDrawcall();
	}

	Light::~Light() noexcept
	{
		__release();
	}
}
