#pragma once

#include "UniformSetter.h"
#include "Cache.h"

namespace Danburite
{
	class LightUniformSetter : public ObjectGL::UniformSetter
	{
	private:
		class LightUniformNameCache : public ObjectGL::Cache<std::string, std::string>
		{
		private:
			const glm::uint __id;

		protected:
			virtual std::string _onProvideValue(const std::string &key) override;

		public:
			LightUniformNameCache(const glm::uint id) noexcept;
		};

		ObjectGL::UniformSetter &__uniformSetter;
		LightUniformNameCache __uniformNameCache;

	public:
		LightUniformSetter(ObjectGL::UniformSetter &lightSetter, const glm::uint id);

		using UniformSetter::setUniformUvec2;
		using UniformSetter::setUniformVec3;
		using UniformSetter::setUniformVec4;
		using UniformSetter::setUniformMat3;
		using UniformSetter::setUniformMat4;

		virtual bool isExistent(const std::string &name) noexcept override;
		virtual bool setUniformInt(const std::string &name, const GLint value) noexcept override;
		virtual bool setUniformUint(const std::string &name, const GLuint value) noexcept override;
		virtual bool setUniformFloatArray(
			const std::string &name, const GLfloat *const pValues, const GLsizei numElements) noexcept override;

		virtual bool setUniformMat4Array(
			const std::string& name, const GLfloat* const pValues, const GLsizei numElements, const bool transposition = false) noexcept override;

		virtual bool setUniformUvec2(const std::string &name, const GLuint *const pValue) noexcept override;
		virtual bool setUniformVec3(const std::string &name, const GLfloat *const pValues) noexcept override;
		virtual bool setUniformVec4(const std::string &name, const GLfloat *const pValues) noexcept override;
		virtual bool setUniformMat3(const std::string &name, const GLfloat *const pValues, const bool transposition = false) noexcept override;

		virtual ~LightUniformSetter() = default;
	};
}