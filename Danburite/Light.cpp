#include "Light.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Light::Light(
		const LightType type, UniformSetter &lightParamSetter, UniformSetter &cameraParamSetter) :
		Object(__getAllocatorMap()[&lightParamSetter].allocate()),
		__lightParamSetter(lightParamSetter),
		__lightParamSetterWrapper(lightParamSetter, ID),
		__depthBaker(cameraParamSetter)
	{
		__lightParamSetterWrapper.setUniformBool(ShaderIdentifier::Name::Light::ENABLED, true);
		__lightParamSetterWrapper.setUniformUint(ShaderIdentifier::Name::Light::TYPE, GLenum(type));
	}

	void Light::__release() noexcept
	{
		__lightParamSetterWrapper.setUniformBool(ShaderIdentifier::Name::Light::ENABLED, false);
		__getAllocatorMap()[&__lightParamSetter].deallocate(ID);
	}

	unordered_map<UniformSetter *, Light::LightIDAllocator> &Light::__getAllocatorMap() noexcept
	{
		static unordered_map<UniformSetter *, LightIDAllocator> instance;
		return instance;
	}

	void Light::selfDeploy() noexcept
	{
		__lightParamSetterWrapper.setUniformUvec2(
			ShaderIdentifier::Name::Light::DEPTH_MAP, __depthBaker.getDepthMap().getHandle());

		_onDeploy(__lightParamSetterWrapper);
	}

	void Light::setDepthMapResolution(const GLsizei width, const GLsizei height) noexcept
	{
		__depthBaker.setResolution(width, height);
	}

	void Light::startDepthBaking() noexcept
	{
		const mat4 &viewMat = _getViewMatrix();
		const mat4 &projMat = _getProjMatrix();

		__depthBaker.deployViewProjMatrix(viewMat, projMat);
		__depthBaker.bind();
	}

	void Light::endDepthBaking() noexcept
	{
		__depthBaker.unbind();
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
