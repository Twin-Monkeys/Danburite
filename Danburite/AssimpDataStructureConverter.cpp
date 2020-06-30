#include "AssimpDataStructureConverter.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	mat4 AssimpDataStructureConverter::toMat4(const aiMatrix4x4 &src) noexcept
	{
		mat4 retVal;
		aiMatrix4x4 srcCopied = src;
		std::memcpy(&retVal, &srcCopied.Transpose(), sizeof(mat4));

		return retVal;
	}
}