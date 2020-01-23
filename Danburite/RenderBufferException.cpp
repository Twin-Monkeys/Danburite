#include "RenderBufferException.h"

using namespace std;

namespace ObjectGL
{
	RenderBufferException::RenderBufferException(char const *const _Message) noexcept :
		exception(_Message)
	{}
}