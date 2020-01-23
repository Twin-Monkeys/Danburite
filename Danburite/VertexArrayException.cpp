#include "VertexArrayException.h"

using namespace std;

namespace ObjectGL
{
	VertexArrayException::VertexArrayException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}