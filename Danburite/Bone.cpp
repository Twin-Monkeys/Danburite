#include "Bone.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Bone::Bone(
		const GLuint id, const string &name,
		const mat4 &offsetMatrix, const glm::mat4 &hierarchyMatrix) noexcept :
		Object(id), __name(name), __offsetMat(offsetMatrix), __hierarchyInvMat(inverse(hierarchyMatrix))
	{}

	void Bone::calcBoneMatrix(const mat4 &nodeAnimMatrix, mat4 &retVal) const noexcept
	{
		retVal = (__hierarchyInvMat * nodeAnimMatrix * __offsetMat);
	}
}