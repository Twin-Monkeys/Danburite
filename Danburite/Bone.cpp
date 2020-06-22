#include "Bone.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Bone::Bone(const GLuint id, const string &boneNodeName, const mat4 &offsetMatrix) noexcept :
		Object(id), __boneNodeName(boneNodeName), __offsetMat(offsetMatrix)
	{}

	mat4 Bone::calcBoneMatrix(const mat4 &nodeMatrix) const noexcept
	{
		return (nodeMatrix * __offsetMat);
	}
}