#include "ShaderCompiler.h"
#include <fstream>
#include <sstream>
#include "TextReader.h"
#include <stack>
#include <cassert>
#include <regex>
#include "RenderContext.h"

using namespace std;
using namespace filesystem;
using namespace std;

namespace ObjectGL
{
	ShaderCompiler::ShaderCompiler(const ShaderType type) noexcept :
		_TYPE(GLenum(type))
	{}

	string ShaderCompiler::__preprocess(const path &srcPath, const bool recursive)
	{
		static const regex
			includeDirectiveRegex	{ R"_(^[ \t]*#include[ \t]+"(.*)"[ \t]*$)_" },
			extensionDirectiveRegex	{ R"_(^[ \t]*#extension[ \t]+\w+[ \t]*:[ \t]*\w*[ \t]*$)_" },
			versionDirectiveRegex	{ R"_(^[ \t]*#version[ \t]+\d+[ \t]+\w*[ \t]*$)_" };

		const path &sourceParentPath = srcPath.parent_path();
		string retVal = move(TextReader::read(srcPath.string()));

		smatch matched;
		
		// #include directive processing

		while (regex_search(retVal, matched, includeDirectiveRegex))
		{
			const path includedPath = matched.str(1ULL);

			if (!includedPath.has_filename())
				throw ShaderCompilerException("Invalid include syntax");

			retVal.replace(matched.position(), matched.length(), __preprocess(sourceParentPath / includedPath, true));
		}

		if (recursive)
			return retVal;

		// #extension directive processing

		vector<string> extensionStrList;
		while (regex_search(retVal, matched, extensionDirectiveRegex))
		{
			extensionStrList.emplace_back(move(matched.str()));
			retVal.erase(matched.position(), matched.length());
		}

		if (!extensionStrList.empty())
		{
			size_t insertionPos {};
			if (regex_search(retVal, matched, versionDirectiveRegex))
				insertionPos = (matched.position() + matched.length());

			for (const string &extensionStr : extensionStrList)
				retVal.insert(insertionPos, "\n" + extensionStr);
		}

		return retVal;
	}

	void ShaderCompiler::addSource(const string &srcPath) noexcept
	{
		__sourcePaths.emplace(srcPath);
	}

	void ShaderCompiler::clear() noexcept
	{
		__sourcePaths.clear();
	}

	shared_ptr<Shader> ShaderCompiler::compile() const
	{
		const GLuint SHADER_ID = glCreateShader(_TYPE);

		if (!SHADER_ID)
			throw ShaderCompilerException("Cannot create shader");

		vector<string> preprocessedSources;
		for (const string &srcPath : __sourcePaths)
			preprocessedSources.emplace_back(move(__preprocess(srcPath)));

		vector<const char*> rawSources;
		for (const string &preprocessedSrc : preprocessedSources)
			rawSources.emplace_back(preprocessedSrc.c_str());

		glShaderSource(SHADER_ID, GLsizei(rawSources.size()), rawSources.data(), nullptr);
		assert(glGetError() == GL_NO_ERROR);

		glCompileShader(SHADER_ID);
		assert(glGetError() == GL_NO_ERROR);

		GLint success;
		glGetShaderiv(SHADER_ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char log[512];
			glGetShaderInfoLog(SHADER_ID, sizeof(log), nullptr, log);

			throw ShaderCompilerException(log);
		}

		return shared_ptr<Shader>(new Shader(SHADER_ID));
	}

	file_time_type ShaderCompiler::getLastModifiedTime(const string_view &srcPath)
	{
		static constexpr string_view SEARCH_TARGET = "#include";

		const path sourcePath = srcPath;
		const path &sourceParentPath = sourcePath.parent_path();
		const path &sourceFilePath = sourcePath.filename();

		file_time_type retVal;

		// <parent path, header> pair
		stack<pair<path, path>> inclusions;
		inclusions.emplace(sourceParentPath, sourceFilePath);

		while (!inclusions.empty())
		{
			const path parentPath = move(inclusions.top().first);
			const path headerPath = move(inclusions.top().second);
			inclusions.pop();

			const path inclusion = move(parentPath / headerPath);

			file_time_type curLastModifiedTime = last_write_time(inclusion);
			if (retVal < curLastModifiedTime)
				retVal = curLastModifiedTime;

			const string &src = TextReader::read(inclusion.string());
			const size_t DIRECTIVE_POS = src.find(SEARCH_TARGET);
			if (DIRECTIVE_POS == string::npos)
				continue;

			const size_t QUOTE_START = src.find('\"', DIRECTIVE_POS + SEARCH_TARGET.length());
			if ((QUOTE_START == string::npos))
				throw ShaderCompilerException("invalid include syntax");

			const size_t QUOTE_END = src.find('\"', QUOTE_START + 1);
			if ((QUOTE_END == string::npos))
				throw ShaderCompilerException("invalid include syntax");

			const path includedPath = src.substr(QUOTE_START + 1, (QUOTE_END - 1) - QUOTE_START);
			if (!includedPath.has_filename())
				throw ShaderCompilerException("invalid include syntax");

			inclusions.emplace(parentPath / includedPath.parent_path(), includedPath.filename());
		}

		return retVal;
	}
}