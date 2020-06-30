#include "Bone.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Bone::Bone(const GLuint id, const mat4 &offsetMatrix) noexcept :
		Object(id), __offsetMat(offsetMatrix)
	{}

	void Bone::updateMatrix() noexcept
	{
		__boneMat = (inverse(__srcJointMat) * __targetJointMat * __offsetMat);
	}
}