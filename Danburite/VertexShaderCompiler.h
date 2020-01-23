#pragma once

#include "ShaderCompiler.h"

namespace ObjectGL
{
	class VertexShaderCompiler : public ShaderCompiler
	{
	public:
		VertexShaderCompiler() noexcept;
		virtual ~VertexShaderCompiler() = default;
	};
}