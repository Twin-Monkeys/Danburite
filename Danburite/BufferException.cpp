#include "BufferException.h"

using namespace std;

namespace ObjectGL
{
	BufferException::BufferException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}