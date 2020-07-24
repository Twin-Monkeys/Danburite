#include "AttachmentServerException.h"

using namespace std;

namespace Danburite
{
	AttachmentServerException::AttachmentServerException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}