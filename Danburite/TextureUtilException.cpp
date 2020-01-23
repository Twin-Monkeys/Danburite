#include "TextureUtilException.h"

using namespace std;

namespace Danburite
{
	TextureUtilException::TextureUtilException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}