#include "LightException.h"

using namespace std;

namespace Danburite
{
	LightException::LightException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}