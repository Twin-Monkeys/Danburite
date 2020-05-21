#include "Bone.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Bone::Bone(const GLuint id, const string &name, const mat4 &offsetMatrix) noexcept :
		Object(id), __name(name), __offsetMat(offsetMatrix), __offsetInvMat(inverse(offsetMatrix))
	{}

	void Bone::calcBoneMatrix(const mat4 &nodeMatrix, mat4 &retVal) const noexcept
	{
		retVal = (__offsetMat * nodeMatrix * __offsetInvMat);
	}
}