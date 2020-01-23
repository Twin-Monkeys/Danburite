#pragma once

#include "ShaderCompiler.h"

namespace ObjectGL
{
	class GeometryShaderCompiler : public ShaderCompiler
	{
	public:
		GeometryShaderCompiler() noexcept;
		virtual ~GeometryShaderCompiler() = default;
	};
}