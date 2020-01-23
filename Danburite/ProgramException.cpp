#include "ProgramException.h"

using namespace std;

namespace ObjectGL
{
	ProgramException::ProgramException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}