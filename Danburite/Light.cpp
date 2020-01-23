#include "Light.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Light::Light(UniformSetter &uniformSetter, const LightType type) noexcept :
		Object(__getAllocatorMap()[&uniformSetter].allocate()),
		__uniformSetter(uniformSetter),
		__lightUniformSetter(uniformSetter, ID),
		__enabledName(move("light[" + to_string(ID) + "]." + ShaderIdentifier::Name::Light::ENABLED))
	{
		const string typeName =
			move("light[" + to_string(ID) + "]." + ShaderIdentifier::Name::Light::TYPE);

		setEnabled(true);
		__uniformSetter.setUniformUint(typeName, GLenum(type));
	}

	void Light::__release() noexcept
	{
		setEnabled(false);
		__getAllocatorMap()[&__uniformSetter].deallocate(ID);
	}

	unordered_map<UniformSetter *, Light::LightIDAllocator> &Light::__getAllocatorMap() noexcept
	{
		static unordered_map<UniformSetter *, LightIDAllocator> instance;
		return instance;
	}

	void Light::setEnabled(const bool enabled) noexcept
	{
		__uniformSetter.setUniformBool(__enabledName, enabled);
	}

	void Light::selfDeploy() noexcept
	{
		_onDeploy(__lightUniformSetter);
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
