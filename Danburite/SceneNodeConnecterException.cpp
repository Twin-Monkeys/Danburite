#include "SceneNodeConnecterException.h"

using namespace std;

namespace Danburite
{
	SceneNodeConnecterException::SceneNodeConnecterException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}