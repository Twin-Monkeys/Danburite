#include "Bone.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	Bone::Bone(const GLuint id, const mat4 &offsetMatrix, vector<mat4> &boneMatricesRef) noexcept :
		Object(id), __offsetMat(offsetMatrix), __offsetInvMat(inverse(offsetMatrix)),
		__boneMatrices(boneMatricesRef)
	{}

	void Bone::__setboneMatrix(const mat4 &boneMatrix) const noexcept
	{
		__boneMatrices[ID] = boneMatrix;
	}

	void Bone::updateMatrix(const mat4 &nodeMatrix) noexcept
	{
		__setboneMatrix(__offsetMat * nodeMatrix * __offsetInvMat);
	}
}