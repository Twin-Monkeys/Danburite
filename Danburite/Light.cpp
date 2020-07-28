#include "Light.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Light::LightIDAllocator &Light::__getAllocator() noexcept
	{
		static LightIDAllocator instance;
		return instance;
	}

	Light::Light(const LightType type, const DepthBakingType depthBakingType) :
		Object(__getAllocator().allocate()),
		__lightSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::LIGHT), ID),

		__lightPrePassSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::LIGHT_PREPASS))
	{
		__lightSetter.setUniformUint(ShaderIdentifier::Name::Light::TYPE, GLenum(type));
		__lightSetter.setUniformUint(ShaderIdentifier::Name::Light::DEPTH_BAKING_TYPE, GLenum(depthBakingType));
	}

	void Light::__release() noexcept
	{
		setEnabled(false);
		__getAllocator().deallocate(ID);
	}

	void Light::selfDeploy() noexcept
	{
		__lightSetter.setUniformBool(ShaderIdentifier::Name::Light::ENABLED, __enabled);
		if (!__enabled)
			return;

		_onDeploy(__lightSetter);

		__lightSetter.setUniformBool(ShaderIdentifier::Name::Light::SHADOW_ENABLED, __shadowEnabled);
		if (!__shadowEnabled)
			return;

		_onDeployShadowData(__lightSetter);
	}

	void Light::bakeDepthMap(Drawer &drawer) noexcept
	{
		if (!isShadowEnabled())
			return;

		_onBakeDepthMap(drawer);
	}

	void Light::volumeDrawcall() noexcept
	{
		__lightPrePassSetter.setUniformUint(
			ShaderIdentifier::Name::LightPrePass::CURRENT_LIGHT_IDX, ID);

		_onVolumeDrawcall();
	}

	Light::~Light() noexcept
	{
		__release();
	}

	uint Light::LightIDAllocator::allocate()
	{
		for (size_t i = 0; i < __occupationMap.size(); i++)
		{
			if (!__occupationMap[i])
			{
				const uint RET_VAL = uint(i);
				__occupationMap[RET_VAL] = true;

				return RET_VAL;
			}
		}

		throw LightException("Cannot allocate Light ID");
	}

	void Light::LightIDAllocator::deallocate(const uint id) noexcept
	{
		__occupationMap[id] = false;
	}
}
