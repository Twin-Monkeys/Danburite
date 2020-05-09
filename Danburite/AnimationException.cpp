#include "AnimationException.h"

using namespace std;

namespace Danburite
{
	AnimationException::AnimationException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}