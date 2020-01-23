#include "Win32ScreenException.h"

using namespace std;

namespace Danburite
{
	Win32ScreenException::Win32ScreenException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}