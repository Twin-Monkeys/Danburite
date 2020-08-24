#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace ObjectGL
{
	class UniformSetter abstract
	{
	public:
		virtual bool isExistent(const std::string &name) noexcept = 0;
		virtual bool setUniformInt(const std::string &name, const GLint value) noexcept = 0;
		virtual bool setUniformUint(const std::string &name, const GLuint value) noexcept = 0;
		virtual bool setUniformFloatArray(
			const std::string &name, const GLfloat *const pValues, const GLsizei numElements) noexcept = 0;

		virtual bool setUniformMat4Array(
			const std::string &name, const GLfloat* const pValues, const GLsizei numElements) noexcept = 0;

		virtual bool setUniformUvec2(const std::string &name, const GLuint *const pValues) noexcept = 0;
		virtual bool setUniformVec3(const std::string &name, const GLfloat *const pValues) noexcept = 0;
		virtual bool setUniformVec4(const std::string &name, const GLfloat *const pValues) noexcept = 0;
		virtual bool setUniformMat3(const std::string &name, const GLfloat *const pValues) noexcept = 0;

		bool setUniformFloat(const std::string &name, const GLfloat value) noexcept;
		bool setUniformBool(const std::string &name, const GLboolean value) noexcept;
		bool setUniformUvec2(const std::string &name, const glm::uvec2 &value) noexcept;
		bool setUniformUvec2(const std::string &name, const GLuint64 valueAsStream) noexcept;
		bool setUniformVec3(const std::string &name, const glm::vec3 &values) noexcept;
		bool setUniformVec3(const std::string &name, const float x, const float y, const float z) noexcept;
		bool setUniformVec4(const std::string &name, const glm::vec4 &values) noexcept;
		bool setUniformVec4(const std::string &name, const float x, const float y, const float z, const float w) noexcept;
		bool setUniformMat3(const std::string &name, const glm::mat3 &values) noexcept;
		bool setUniformMat4(const std::string &name, const GLfloat *const pValues) noexcept;
		bool setUniformMat4(const std::string &name, const glm::mat4 &values) noexcept;

		bool setUniformMat4Array(
			const std::string& name, const glm::mat4* const pValues, const GLsizei numElements) noexcept;

		/*
			정 transpose 하고 싶다면 layout qualifier를 사용할 것.
		*/
		template <GLsizei NUM_ELEMS>
		bool setUniformMat4Array(const std::string &name, const glm::mat4 (&arrValues)[NUM_ELEMS]) noexcept;

		virtual ~UniformSetter() = default;
	};

	template <GLsizei NUM_ELEMS>
	bool UniformSetter::setUniformMat4Array(const std::string &name, const glm::mat4(&arrValues)[NUM_ELEMS]) noexcept
	{
		return setUniformMat4Array(name, arrValues, NUM_ELEMS);
	}
}