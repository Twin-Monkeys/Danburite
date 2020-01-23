#include "AssetImporterException.h"

using namespace std;

namespace Danburite
{
	AssetImporterException::AssetImporterException(char const* const _Message) noexcept :
		exception(_Message)
	{}
}