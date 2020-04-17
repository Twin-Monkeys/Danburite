#pragma once

#include "Buffer.h"
#include "UniformSetter.h"
#include "Program.h"
#include <unordered_map>
#include <map>

namespace ObjectGL
{
	class UniformBuffer : public Buffer, public UniformSetter
	{
	private:
		std::string __blockName;

		GLuint __bindingPoint;
		std::unordered_set<Program *> __registeredPrograms;
		std::multimap<GLuint, Program *, std::greater<GLuint>> __blockSizeSorter;

	protected:
		GLint _getBlockElementOffset(const std::string &name) noexcept;
		bool _setUniformValue(const std::string &name, const void *const pValue, const GLsizeiptr size) noexcept;

	public:
		UniformBuffer(const std::string &blockName, const GLuint bindingPoint);

		bool registerProgram(Program &program) noexcept;
		bool memoryAllocFit(const BufferUpdatePatternType updatePattern);

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
			const std::string &name, const GLfloat *const pValues, const GLsizei numElements, const bool transposition = false) noexcept override;

		virtual bool setUniformUvec2(const std::string &name, const GLuint *const pValues) noexcept override;
		virtual bool setUniformVec3(const std::string &name, const GLfloat *const pValues) noexcept override;
		virtual bool setUniformVec4(const std::string &name, const GLfloat *const pValues) noexcept override;
		virtual bool setUniformMat3(const std::string &name, const GLfloat *const pValues, const bool transposition) noexcept override;

		virtual ~UniformBuffer() = default;
	};
}