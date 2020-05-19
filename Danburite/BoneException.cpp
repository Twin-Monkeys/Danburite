#include "BoneException.h"

using namespace std;

namespace Danburite
{
	BoneException::BoneException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}