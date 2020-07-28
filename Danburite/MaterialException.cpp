#include "MaterialException.h"

using namespace std;

namespace ObjectGL
{
	MaterialException::MaterialException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}