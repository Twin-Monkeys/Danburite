#pragma once

#include <unordered_set>
#include <GL/glew.h>
#include <string>
#include "ShaderType.h"
#include "Shader.h"
#include <filesystem>
#include "ShaderCompilerException.h"

namespace ObjectGL
{
	class ShaderCompiler abstract
	{
	private:
		std::unordered_set<std::string> __sourcePaths;
		const GLenum _TYPE;

		static std::string __preprocess(const std::filesystem::path &srcPath, const bool recursive = false);

	protected:
		ShaderCompiler(const ShaderType type) noexcept;

	public:
		void addSource(const std::string &srcPath) noexcept;
		void clear() noexcept;

		std::shared_ptr<Shader> compile() const;
		virtual ~ShaderCompiler() = default;

		static std::filesystem::file_time_type getLastModifiedTime(const std::string_view &srcPath);
	};
}
