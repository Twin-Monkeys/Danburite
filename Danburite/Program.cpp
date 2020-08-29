#include "Program.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

using namespace std;
using namespace glm;

namespace ObjectGL
{
	Program::UniformLocationCache::UniformLocationCache(Program &program) noexcept :
		__program { program }
	{}

	GLint Program::UniformLocationCache::_onProvideValue(const string &key)
	{
		return glGetUniformLocation(__program.ID, key.c_str());
	}

	Program::Program(const std::unordered_set<std::shared_ptr<Shader>> &shaders) :
		BindableObject(glCreateProgram())
	{
		if (!ID)
			throw ProgramException("Cannot create program");

		for (const shared_ptr<Shader> &pShader : shaders)
			glAttachShader(ID, pShader->ID);

		glLinkProgram(ID);
		__linkingCheck();

		for (const shared_ptr<Shader> &pShader : shaders)
			glDetachShader(ID, pShader->ID);
	}

	Program::Program(const vector<uint8_t> &binary) :
		BindableObject(glCreateProgram())
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

			char log[4096];
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

	bool Program::setUniformMat4Array(const string &name, const GLfloat *const pValues, const GLsizei numElements) noexcept
	{
		const GLint LOCATION = __getUniformLocation(name);
		if (LOCATION < 0)
			return false;

		bind();
		glUniformMatrix4fv(LOCATION, numElements, false, pValues);
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

	bool Program::setUniformMat3(const string &name, const GLfloat *const pValues) noexcept
	{
		const GLint LOCATION = __getUniformLocation(name);
		if (LOCATION < 0)
			return false;

		bind();
		glUniformMatrix3fv(LOCATION, 1, false, pValues);
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
}
