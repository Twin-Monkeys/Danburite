#include "FrameBufferException.h"

using namespace std;

namespace ObjectGL
{
	FrameBufferException::FrameBufferException(char const *const _Message) noexcept :
		exception(_Message)
	{}
}