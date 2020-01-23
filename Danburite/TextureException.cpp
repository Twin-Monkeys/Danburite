#include "TextureException.h"

using namespace std;

namespace ObjectGL
{
	TextureException::TextureException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}