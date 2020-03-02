#pragma once

#include "BindableObject.h"
#include "UniformBatchDeployer.h"
#include "Shader.h"
#include "ProgramException.h"
#include "Cache.h"
#include <unordered_set>

namespace ObjectGL
{
	class UniformBuffer;

	class Program : public BindableObject<Program, GLuint>, public UniformBatchDeployer
	{
	private:
		template <typename KeyType, typename ValueType>
		class ProgramDependentCache abstract : public Cache<KeyType, ValueType>
		{
		protected:
			Program &_program;

			ProgramDependentCache(Program &program) noexcept;

		public:
			virtual ~ProgramDependentCache() = default;
		};

		class AttributeLocationCache : public ProgramDependentCache<std::string, GLint>
		{
		protected:
			virtual GLint _onProvideValue(const std::string &key) override;

		public:
			AttributeLocationCache(Program &program) noexcept;

			virtual ~AttributeLocationCache() = default;
		};

		class UniformLocationCache : public ProgramDependentCache<std::string, GLint>
		{
		protected:
			virtual GLint _onProvideValue(const std::string &key) override;

		public:
			UniformLocationCache(Program &program) noexcept;

			virtual ~UniformLocationCache() = default;
		};

		class UniformBlockIndexCache : public ProgramDependentCache<std::string, GLuint>
		{
		protected:
			virtual GLuint _onProvideValue(const std::string &key) override;

		public:
			UniformBlockIndexCache(Program &program) noexcept;

			virtual ~UniformBlockIndexCache() = default;
		};

		class UniformBlockElementOffsetCache : public ProgramDependentCache<std::string, GLint>
		{
		protected:
			virtual GLint _onProvideValue(const std::string &key) override;

		public:
			UniformBlockElementOffsetCache(Program &program) noexcept;

			virtual ~UniformBlockElementOffsetCache() = default;
		};

		AttributeLocationCache __attribLocationCache;
		UniformLocationCache __uniformLocationCache;
		UniformBlockIndexCache __uniformBlockIndexCache;
		UniformBlockElementOffsetCache __uniformBlockElementOffsetCache;

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

		GLint getAttributeLocation(const std::string &name) noexcept;
		GLuint getUniformBlockIndex(const std::string &name) noexcept;
		GLint getUniformBlockElementOffset(const std::string &name) noexcept;

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

		virtual bool setUniformUvec2(const std::string &name, const GLuint *const pValues) noexcept override;
		virtual bool setUniformVec3(const std::string &name, const GLfloat *const pValues) noexcept override;
		virtual bool setUniformVec4(const std::string &name, const GLfloat *const pValues) noexcept override;
		virtual bool setUniformMat3(const std::string &name, const GLfloat *const pValues, const bool transposition) noexcept override;
		virtual bool setUniformMat4(const std::string &name, const GLfloat *const pValues, const bool transposition) noexcept override;

		std::vector<uint8_t> exportBinary();

		virtual ~Program() noexcept;
	};

	template <typename KeyType, typename ValueType>
	Program::ProgramDependentCache<KeyType, ValueType>::ProgramDependentCache(Program &program) noexcept :
		_program(program)
	{}
}
