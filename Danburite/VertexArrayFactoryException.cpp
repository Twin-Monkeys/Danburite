#include "VertexArrayFactoryException.h"

using namespace std;

namespace Danburite
{
	VertexArrayFactoryException::VertexArrayFactoryException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}