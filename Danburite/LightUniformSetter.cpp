#include "LightUniformSetter.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	LightUniformSetter::LightUniformSetter(UniformSetter &lightSetter, const uint id) :
		__uniformSetter(lightSetter), __uniformNameCache(id)
	{}

	bool LightUniformSetter::isExistent(const string &name) noexcept
	{
		return __uniformSetter.isExistent(name);
	}

	bool LightUniformSetter::setUniformInt(const string &name, const GLint value) noexcept
	{
		return __uniformSetter.setUniformInt(__uniformNameCache.getValue(name), value);
	}

	bool LightUniformSetter::setUniformUint(const string &name, const GLuint value) noexcept
	{
		return __uniformSetter.setUniformUint(__uniformNameCache.getValue(name), value);
	}

	bool LightUniformSetter::setUniformFloatArray(const string &name, const GLfloat *const pValues, const GLsizei numElements) noexcept
	{
		return __uniformSetter.setUniformFloatArray(__uniformNameCache.getValue(name), pValues, numElements);
	}

	bool LightUniformSetter::setUniformUvec2(const string &name, const GLuint *const pValue) noexcept
	{
		return __uniformSetter.setUniformUvec2(__uniformNameCache.getValue(name), pValue);
	}

	bool LightUniformSetter::setUniformVec3(const string &name, const GLfloat *const pValues) noexcept
	{
		return __uniformSetter.setUniformVec3(__uniformNameCache.getValue(name), pValues);
	}

	bool LightUniformSetter::setUniformVec4(const string &name, const GLfloat *const pValues) noexcept
	{
		return __uniformSetter.setUniformVec4(__uniformNameCache.getValue(name), pValues);
	}

	bool LightUniformSetter::setUniformMat3(const string &name, const GLfloat *const pValues, const bool transposition) noexcept
	{
		return __uniformSetter.setUniformMat3(__uniformNameCache.getValue(name), pValues, transposition);
	}

	bool LightUniformSetter::setUniformMat4(const string &name, const GLfloat *const pValues, const bool transposition) noexcept
	{
		return __uniformSetter.setUniformMat4(__uniformNameCache.getValue(name), pValues, transposition);
	}

	LightUniformSetter::LightUniformNameCache::LightUniformNameCache(const uint id) noexcept :
		__id(id)
	{}

	string LightUniformSetter::LightUniformNameCache::_onProvideValue(const string &key)
	{
		string retVal = "light[";
		retVal += to_string(__id);
		retVal += "].";
		retVal += key;

		return retVal;
	}
}