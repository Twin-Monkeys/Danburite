#include "Program.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

using namespace std;
using namespace glm;

namespace ObjectGL
{
	Program::Program(const std::unordered_set<std::shared_ptr<Shader>> &shaders) :
		BindableObject(glCreateProgram()),
		__attribLocationCache(*this), __uniformLocationCache(*this),
		__uniformBlockIndexCache(*this), __uniformBlockElementOffsetCache(*this)
	{
		if (!ID)
			throw ProgramException("Cannot create program");

		for (const shared_ptr<Shader>& pShader : shaders)
			glAttachShader(ID, pShader->ID);

		glLinkProgram(ID);
		__linkingCheck();
	}

	Program::Program(const vector<uint8_t> &binary) :
		BindableObject(glCreateProgram()),
		__attribLocationCache(*this), __uniformLocationCache(*this),
		__uniformBlockIndexCache(*this), __uniformBlockElementOffsetCache(*this)
	{
		if (!ID)
			throw ProgramException("Cannot create program");

		const uint8_t *const rawPtr = binary.data();

		const GLenum BINARY_FORMAT = *reinterpret_cast<const GLenum *>(rawPtr);
		constexpr size_t OFFSET = sizeof(GLenum);

		glProgramBinary(ID, BINARY_FORMAT, rawPtr + OFFSET, GLsizei(binary.size() - OFFSET));
		__linkingCheck();
	}

	void Program::__linkingCheck()
	{
		GLint success;
		glGetProgramiv(ID, GL_LINK_STATUS, &success);

		if (!success)
		{
			string msg = "Link error occurred: ";

			char log[512];
			glGetProgramInfoLog(ID, sizeof(log), nullptr, log);

			msg += log;

			throw ProgramException(msg.c_str());
		}
	}

	void Program::__release() noexcept
	{
		glDeleteProgram(ID);
	}

	GLint Program::__getUniformLocation(const string &name) noexcept
	{
		return __uniformLocationCache.getValue(name);
	}

	void Program::_onBind() noexcept
	{
		glUseProgram(ID);
	}

	GLint Program::getAttributeLocation(const string &name) noexcept
	{
		return __attribLocationCache.getValue(name);
	}

	GLuint Program::getUniformBlockIndex(const string &name) noexcept
	{
		return __uniformBlockIndexCache.getValue(name);
	}
	
	GLint Program::getUniformBlockElementOffset(const string &name) noexcept
	{
		return __uniformBlockElementOffsetCache.getValue(name);
	}

	bool Program::isExistent(const string &name) noexcept
	{
		return (__getUniformLocation(name) >= 0);
	}

	bool Program::setUniformInt(const string &name, const GLint value) noexcept
	{
		const GLint LOCATION = __getUniformLocation(name);
		if (LOCATION < 0)
			return false;

		bind();
		glUniform1i(LOCATION, value);
		return true;
	}

	bool Program::setUniformUint(const std::string &name, const GLuint value) noexcept
	{
		const GLint LOCATION = __getUniformLocation(name);
		if (LOCATION < 0)
			return false;

		bind();
		glUniform1ui(LOCATION, value);
		return true;
	}

	bool Program::setUniformFloatArray(
		const string &name, const GLfloat *const pValues, const GLsizei numElements) noexcept
	{
		const GLint LOCATION = __getUniformLocation(name);
		if (LOCATION < 0)
			return false;

		bind();
		glUniform1fv(LOCATION, numElements, pValues);
		return true;
	}

	bool Program::setUniformMat4Array(
		const string &name, const GLfloat *const pValues, const GLsizei numElements, const bool transposition) noexcept
	{
		const GLint LOCATION = __getUniformLocation(name);
		if (LOCATION < 0)
			return false;

		bind();
		glUniformMatrix4fv(LOCATION, numElements, transposition, pValues);
		return true;
	}

	bool Program::setUniformUvec2(const string &name, const GLuint *const pValues) noexcept
	{
		const GLint LOCATION = __getUniformLocation(name);
		if (LOCATION < 0)
			return false;

		bind();
		glUniform2uiv(LOCATION, 1, pValues);
		return true;
	}

	bool Program::setUniformVec3(const string &name, const GLfloat *const pValues) noexcept
	{
		const GLint LOCATION = __getUniformLocation(name);
		if (LOCATION < 0)
			return false;

		bind();
		glUniform3fv(LOCATION, 1, pValues);
		return true;
	}

	bool Program::setUniformVec4(const string &name, const GLfloat *const pValues) noexcept
	{
		const GLint LOCATION = __getUniformLocation(name);
		if (LOCATION < 0)
			return false;

		bind();
		glUniform4fv(LOCATION, 1, pValues);
		return true;
	}

	bool Program::setUniformMat3(const string &name, const GLfloat *const pValues, const bool transposition) noexcept
	{
		const GLint LOCATION = __getUniformLocation(name);
		if (LOCATION < 0)
			return false;

		bind();
		glUniformMatrix3fv(LOCATION, 1, transposition, pValues);
		return true;
	}

	vector<uint8_t> Program::exportBinary()
	{
		GLint binaryLength = 0;
		glGetProgramiv(ID, GL_PROGRAM_BINARY_LENGTH, &binaryLength);

		vector<uint8_t> retVal;
		retVal.resize(binaryLength);

		GLenum format = 0;
		glGetProgramBinary(ID, binaryLength, nullptr, &format, retVal.data());

		const uint8_t *const pFormatRaw = reinterpret_cast<const uint8_t *>(&format);
		retVal.insert(retVal.begin(), { pFormatRaw[0], pFormatRaw[1], pFormatRaw[2], pFormatRaw[3] });

		return retVal;
	}

	Program::~Program() noexcept
	{
		__release();
	}

	Program::AttributeLocationCache::AttributeLocationCache(Program &program) noexcept :
		ProgramDependentCache(program)
	{}

	GLint Program::AttributeLocationCache::_onProvideValue(const string &key)
	{
		const GLint retVal = glGetAttribLocation(_program.ID, key.c_str());

		return retVal;
	}

	Program::UniformLocationCache::UniformLocationCache(Program &program) noexcept :
		ProgramDependentCache(program)
	{}

	GLint Program::UniformLocationCache::_onProvideValue(const string &key)
	{
		const GLint retVal = glGetUniformLocation(_program.ID, key.c_str());

		return retVal;
	}

	Program::UniformBlockIndexCache::UniformBlockIndexCache(Program &program) noexcept :
		ProgramDependentCache(program)
	{}

	GLuint Program::UniformBlockIndexCache::_onProvideValue(const string &key)
	{
		const GLuint retVal = glGetUniformBlockIndex(_program.ID, key.c_str());

		return retVal;
	}

	Program::UniformBlockElementOffsetCache::UniformBlockElementOffsetCache(Program &program) noexcept :
		ProgramDependentCache(program)
	{}

	GLint Program::UniformBlockElementOffsetCache::_onProvideValue(const string &key)
	{
		GLuint index = GL_INVALID_INDEX;
		const char *const pRaw = key.c_str();

		glGetUniformIndices(_program.ID, 1, &pRaw, &index);

		GLint retVal = -1;
		glGetActiveUniformsiv(_program.ID, 1, &index, GL_UNIFORM_OFFSET, &retVal);

		return retVal;
	}
}
