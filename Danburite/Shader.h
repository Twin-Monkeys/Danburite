#pragma once

#include "Object.h"
#include <memory>

namespace ObjectGL
{
	class Shader : public Object<GLuint>
	{
		friend class ShaderCompiler;

	private:
		Shader(const Shader &) = delete;
		Shader& operator=(const Shader &) = delete;

		void __release() noexcept;

	protected:
		explicit Shader(const GLuint id) noexcept;

	public:
		virtual ~Shader() noexcept;
	};
}
