#include "SSAOException.h"

using namespace std;

namespace Danburite
{
	SSAOException::SSAOException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}