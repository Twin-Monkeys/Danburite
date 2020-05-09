#include "UniformBuffer.h"
#include <algorithm>

using namespace std;
using namespace glm;

namespace ObjectGL
{
	UniformBuffer::UniformBuffer(const string &blockName, const GLuint bindingPoint) :
		Buffer(BufferType::UNIFORM), __blockName(blockName), __bindingPoint(bindingPoint)
	{
		glBindBufferBase(__RAW_TYPE, __bindingPoint, ID);
	}

	GLint UniformBuffer::_getBlockElementOffset(const std::string &name) noexcept
	{
		if (__blockSizeSorter.empty())
			return -1;

		Program &target = *__blockSizeSorter.begin()->second;
		return target.getUniformBlockElementOffset(name);
	}

	bool UniformBuffer::registerProgram(Program &program) noexcept
	{
		if (!__registeredPrograms.emplace(&program).second)
			return false;

		const GLuint BLOCK_IDX = program.getUniformBlockIndex(__blockName);
		if (BLOCK_IDX == GL_INVALID_INDEX)
			return false;

		GLint blockSize;
		glGetActiveUniformBlockiv(program.ID, BLOCK_IDX, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

		__blockSizeSorter.emplace(blockSize, &program);
		return true;
	}

	bool UniformBuffer::memoryAllocFit(const BufferUpdatePatternType updatePattern)
	{
		if (__blockSizeSorter.empty())
			return false;

		memoryAlloc(__blockSizeSorter.begin()->first, updatePattern);
		return true;
	}

	bool UniformBuffer::isExistent(const string &name) noexcept
	{
		return (_getBlockElementOffset(name) >= 0);
	}

	bool UniformBuffer::setUniformValue(const string &name, const void *const pValue, const GLsizeiptr size) noexcept
	{
		const GLint OFFSET = _getBlockElementOffset(name);
		if (OFFSET < 0)
			return false;

		memoryCopy(pValue, size, OFFSET);
		return true;
	}

	bool UniformBuffer::setUniformInt(const string &name, const GLint value) noexcept
	{
		return setUniformValue(name, &value, sizeof(value));
	}

	bool UniformBuffer::setUniformUint(const string &name, const GLuint value) noexcept
	{
		return setUniformValue(name, &value, sizeof(value));
	}

	bool UniformBuffer::setUniformFloatArray(
		const string &name, const GLfloat *const pValues, const GLsizei numElements) noexcept
	{
		return setUniformValue(name, pValues, sizeof(GLfloat) * numElements);
	}

	bool UniformBuffer::setUniformMat4Array(
		const string &name, const GLfloat *const pValues, const GLsizei numElements, const bool transposition) noexcept
	{
		const size_t MEM_SIZE = (sizeof(GLfloat) * 16 * numElements);

		if (transposition)
		{
			vector<GLfloat> arrTransposed;
			arrTransposed.resize(16 * numElements);
			
			for (GLsizei i = 0; i < numElements; i++)
				for (GLsizei j = 0; j < 4; j++)
				{
					arrTransposed[(4 * ((4 * i) + j)) + 0] = pValues[(16 * i) + (0 + j)];
					arrTransposed[(4 * ((4 * i) + j)) + 1] = pValues[(16 * i) + (4 + j)];
					arrTransposed[(4 * ((4 * i) + j)) + 2] = pValues[(16 * i) + (8 + j)];
					arrTransposed[(4 * ((4 * i) + j)) + 3] = pValues[(16 * i) + (12 + j)];
				}

			return setUniformValue(name, arrTransposed.data(), MEM_SIZE);
		}

		return setUniformValue(name, pValues, MEM_SIZE);
	}

	bool UniformBuffer::setUniformUvec2(const string &name, const GLuint *const pValues) noexcept
	{
		return setUniformValue(name, pValues, sizeof(GLuint) * 2);
	}

	bool UniformBuffer::setUniformVec3(const string &name, const GLfloat *const pValues) noexcept
	{
		return setUniformValue(name, pValues, sizeof(GLfloat) * 3);
	}

	bool UniformBuffer::setUniformVec4(const string &name, const GLfloat *const pValues) noexcept
	{
		return setUniformValue(name, pValues, sizeof(GLfloat) * 4);
	}

	bool UniformBuffer::setUniformMat3(const string &name, const GLfloat *const pValues, const bool transposition) noexcept
	{
		const size_t MEM_SIZE = (sizeof(GLfloat) * 9);

		if (transposition)
		{
			const GLfloat arrTransposed[] =
			{
				pValues[0], pValues[3], pValues[6],
				pValues[1], pValues[4], pValues[7],
				pValues[2], pValues[5], pValues[8]
			};

			return setUniformValue(name, arrTransposed, MEM_SIZE);
		}

		return setUniformValue(name, pValues, MEM_SIZE);
	}
}