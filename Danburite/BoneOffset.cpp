#include "BoneOffset.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Bone::Bone(
		const GLuint id, const string &boneNodeName,
		const mat4 &offsetMatrix, const mat4 &hierarchyMatrix) noexcept :
		Object(id), __boneNodeName(boneNodeName), __offsetMat(offsetMatrix), __hierarchyMat(hierarchyMatrix)
	{}

	void Bone::calcBoneMatrix(const mat4 &nodeMatrix, mat4 &retVal) const noexcept
	{
		retVal = (__hierarchyMat * nodeMatrix * __offsetMat);
	}
}