#include "DCException.h"

using namespace std;

namespace ObjectGL
{
	DCException::DCException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}