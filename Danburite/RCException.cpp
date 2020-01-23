#include "RCException.h"

using namespace std;

namespace ObjectGL
{
	RCException::RCException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}