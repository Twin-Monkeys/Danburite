#pragma once

#include "BindableObject.h"
#include "Shader.h"
#include "ProgramException.h"
#include "Cache.h"
#include <unordered_set>

namespace ObjectGL
{
	class UniformBuffer;

	class Program : public BindableObject<Program, GLuint>
	{
	private:
		class UniformLocationCache : public Cache<std::string, GLint>
		{
		private:
			Program &__program;

		protected:
			virtual GLint _onProvideValue(const std::string &key) override;

		public:
			UniformLocationCache(Program &program) noexcept;
			virtual ~UniformLocationCache() = default;
		};

		UniformLocationCache __uniformLocationCache { *this };

		Program(const Program &) = delete;
		Program &operator=(const Program &) = delete;

		void __linkingCheck();
		void __release() noexcept;

		GLint __getUniformLocation(const std::string &name) noexcept;

	protected:
		virtual void _onBind() noexcept override;

	public:
		Program(const std::unordered_set<std::shared_ptr<Shader>> &shaders);
		Program(const std::vector<uint8_t> &binary);

		bool isExistent(const std::string &name) noexcept;
		bool setUniformInt(const std::string &name, const GLint value) noexcept;
		bool setUniformUint(const std::string &name, const GLuint value) noexcept;

		bool setUniformFloatArray(
			const std::string &name, const GLfloat *const pValues, const GLsizei numElements) noexcept;

		bool setUniformMat4Array(
			const std::string& name, const GLfloat* const pValues, const GLsizei numElements) noexcept;

		bool setUniformUvec2(const std::string &name, const GLuint *const pValues) noexcept;
		bool setUniformVec3(const std::string &name, const GLfloat *const pValues) noexcept;
		bool setUniformVec4(const std::string &name, const GLfloat *const pValues) noexcept;
		bool setUniformMat3(const std::string &name, const GLfloat *const pValues) noexcept;

		std::vector<uint8_t> exportBinary();

		virtual ~Program() noexcept;
	};
}
