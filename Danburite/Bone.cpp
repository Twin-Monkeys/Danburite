#include "Bone.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	Bone::Bone(const GLuint id, const mat4 &offsetMatrix, vector<mat4> &boneMatricesRef) noexcept :
		Object(id), __offsetMat(offsetMatrix), __offsetInvMat(inverse(offsetMatrix)),
		__boneMatrices(boneMatricesRef)
	{}

	mat4 &Bone::__getboneMatrix() const noexcept
	{
		return __boneMatrices[ID];
	}

	void Bone::updateMatrix(const mat4 &nodeMatrix) noexcept
	{
		__getboneMatrix() = (__offsetMat * nodeMatrix * __offsetInvMat);
	}
}