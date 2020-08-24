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

	bool UniformSetter::setUniformUvec2(const string &name, const uvec2 &value) noexcept
	{
		return setUniformUvec2(name, value_ptr(value));
	}

	bool UniformSetter::setUniformUvec2(const string &name, const GLuint64 valueAsStream) noexcept
	{
		return setUniformUvec2(name, reinterpret_cast<const GLuint *>(&valueAsStream));
	}

	bool UniformSetter::setUniformVec3(const string &name, const vec3 &values) noexcept
	{
		return setUniformVec3(name, value_ptr(values));
	}

	bool UniformSetter::setUniformVec3(const string &name, const float x, const float y, const float z) noexcept
	{
		return setUniformVec3(name, { x, y, z });
	}

	bool UniformSetter::setUniformVec4(const string &name, const vec4 &values) noexcept
	{
		return setUniformVec4(name, value_ptr(values));
	}

	bool UniformSetter::setUniformVec4(
		const string &name, const float x, const float y, const float z, const float w) noexcept
	{
		return setUniformVec4(name, { x, y, z, w });
	}

	bool UniformSetter::setUniformMat3(const string &name, const mat3 &values) noexcept
	{
		return setUniformMat3(name, value_ptr(values));
	}

	bool UniformSetter::setUniformMat4(const string &name, const GLfloat *const pValues) noexcept
	{
		return setUniformMat4Array(name, pValues, 1);
	}

	bool UniformSetter::setUniformMat4(const string &name, const mat4 &values) noexcept
	{
		return setUniformMat4(name, value_ptr(values));
	}

	bool UniformSetter::setUniformMat4Array(
		const string &name, const mat4 *const pValues, const GLsizei numElements) noexcept
	{
		return setUniformMat4Array(name, reinterpret_cast<const GLfloat *>(pValues), numElements);
	}
}