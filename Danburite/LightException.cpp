#include "LightException.h"

using namespace std;

namespace ObjectGL
{
	LightException::LightException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}