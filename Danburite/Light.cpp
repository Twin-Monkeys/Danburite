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

	Light::Light(const LightType type) :
		Object(__getAllocator().allocate()),

		__lightSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::LIGHT), ID)
	{
		__lightSetter.setUniformUint(ShaderIdentifier::Name::Light::TYPE, GLenum(type));
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

		__lightSetter.setUniformMat4(ShaderIdentifier::Name::Light::VIEW_MATRIX, _getViewMatrix());
		__lightSetter.setUniformMat4(ShaderIdentifier::Name::Light::PROJECTION_MATRIX, _getProjMatrix());
		__lightSetter.setUniformUvec2(ShaderIdentifier::Name::Light::DEPTH_MAP, __depthBaker.getDepthMapHandle());
	}

	void Light::setDepthMapResolution(const GLsizei width, const GLsizei height) noexcept
	{
		__depthBaker.setResolution(width, height);
	}

	void Light::startDepthBaking() noexcept
	{
		const mat4 &viewMat = _getViewMatrix();
		const mat4 &projMat = _getProjMatrix();

		__depthBaker.setViewProjMatrix(viewMat, projMat);
		__depthBaker.bind();
	}

	void Light::endDepthBaking() noexcept
	{
		__depthBaker.unbind();
	}

	void Light::bakeDepthMap(Drawer &drawer, const bool cancelIfShadowDisabled) noexcept
	{
		if (cancelIfShadowDisabled && !isShadowEnabled())
			return;

		startDepthBaking();
		drawer.batchRawDrawCall();
		endDepthBaking();
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
