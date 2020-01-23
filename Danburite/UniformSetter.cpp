#include "UniformSetter.h"
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

namespace ObjectGL
{
	bool UniformSetter::setUniformFloat(const string &name, const GLfloat value) noexcept
	{
		return setUniformFloatArray(name, &value, 1);
	}

	bool UniformSetter::setUniformBool(const string &name, const GLboolean value) noexcept
	{
		return setUniformUint(name, value);
	}

	bool UniformSetter::setTextureLocation(const string &name, const GLuint location) noexcept
	{
		return setUniformInt(name, location);
	}

	bool UniformSetter::setUniformVec3(const string &name, const initializer_list<GLfloat> &values) noexcept
	{
		return setUniformVec3(name, values.begin());
	}

	bool UniformSetter::setUniformVec3(const string &name, const vec3 &values) noexcept
	{
		return setUniformVec3(name, value_ptr(values));
	}

	bool UniformSetter::setUniformVec3(const string &name, const float x, const float y, const float z) noexcept
	{
		return setUniformVec3(name, { x, y, z });
	}

	bool UniformSetter::setUniformVec4(const string &name, const initializer_list<GLfloat> &values) noexcept
	{
		return setUniformVec4(name, values.begin());
	}

	bool UniformSetter::setUniformVec4(const string &name, const vec4 &values) noexcept
	{
		return setUniformVec4(name, value_ptr(values));
	}

	bool UniformSetter::setUniformVec4(const string &name, const float x, const float y, const float z, const float w) noexcept
	{
		return setUniformVec4(name, { x, y, z, w });
	}

	bool UniformSetter::setUniformMat3(const string &name, const initializer_list<GLfloat> &values, const bool transposition) noexcept
	{
		return setUniformMat3(name, values.begin(), transposition);
	}

	bool UniformSetter::setUniformMat3(const string &name, const mat4 &values, const bool transposition) noexcept
	{
		return setUniformMat3(name, value_ptr(values), transposition);
	}

	bool UniformSetter::setUniformMat4(const string &name, const initializer_list<GLfloat> &values, const bool transposition) noexcept
	{
		return setUniformMat4(name, values.begin(), transposition);
	}

	bool UniformSetter::setUniformMat4(const string &name, const mat4 &values, const bool transposition) noexcept
	{
		return setUniformMat4(name, value_ptr(values), transposition);
	}
}