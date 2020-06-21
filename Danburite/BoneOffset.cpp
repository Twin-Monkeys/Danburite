#include "BoneOffset.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	BoneOffset::BoneOffset(
		const GLuint id, const string &boneName,
		const mat4 &offsetMatrix, const glm::mat4 &hierarchyMatrix) noexcept :
		Object(id), __boneName(boneName), __offsetMat(offsetMatrix), __hierarchyMat((hierarchyMatrix))
	{}

	void BoneOffset::calcMatrix(const mat4 &boneMatrix, mat4 &retVal) const noexcept
	{
		retVal = (__hierarchyMat * boneMatrix * __offsetMat);
	}
}