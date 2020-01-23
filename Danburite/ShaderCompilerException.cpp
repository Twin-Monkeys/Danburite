#include "ShaderCompilerException.h"

using namespace std;

namespace ObjectGL
{
	ShaderCompilerException::ShaderCompilerException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}