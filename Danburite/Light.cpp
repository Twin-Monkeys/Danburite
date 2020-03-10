#include "Light.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Light::Light(
		const LightType type,
		ObjectGL::UniformSetter &lightParamSetter,
		ObjectGL::UniformSetter &cameraParamSetter) noexcept :
		Object(__getAllocatorMap()[&lightParamSetter].allocate()),
		__lightParamSetter(lightParamSetter),
		__lightParamSetterWrapper(lightParamSetter, ID),
		__enabledName(move("light[" + to_string(ID) + "]." + ShaderIdentifier::Name::Light::ENABLED)),
		__depthBaker(cameraParamSetter)
	{
		const string &typeName =
			("light[" + to_string(ID) + "]." + ShaderIdentifier::Name::Light::TYPE);

		setEnabled(true);
		__lightParamSetter.setUniformUint(typeName, GLenum(type));
	}

	void Light::__release() noexcept
	{
		setEnabled(false);
		__getAllocatorMap()[&__lightParamSetter].deallocate(ID);
	}

	unordered_map<UniformSetter *, Light::LightIDAllocator> &Light::__getAllocatorMap() noexcept
	{
		static unordered_map<UniformSetter *, LightIDAllocator> instance;
		return instance;
	}

	void Light::setEnabled(const bool enabled) noexcept
	{
		__lightParamSetter.setUniformBool(__enabledName, enabled);
	}

	void Light::selfDeploy() noexcept
	{
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

	AttachableTexture &Light::getDepthMap() const noexcept
	{
		return __depthBaker.getDepthMap();
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
