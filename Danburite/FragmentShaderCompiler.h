#pragma once

#include "ShaderCompiler.h"

namespace ObjectGL
{
	class FragmentShaderCompiler : public ShaderCompiler
	{
	public:
		FragmentShaderCompiler() noexcept;
		virtual ~FragmentShaderCompiler() = default;
	};
}