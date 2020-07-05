#include "Bone.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	Bone::Bone(
		const GLuint id, const JointManager &jointManager,
		const string_view &targetNodeName, const string_view &srcNodeName,
		const mat4& offsetMatrix) noexcept :
		Object(id), __jointMgr(jointManager),
		__targetNodeName(targetNodeName), __srcNodeName(srcNodeName), __offsetMat(offsetMatrix)
	{}

	void Bone::calcMatrix(mat4 &retVal) const noexcept
	{
		const Joint *const pTargetJoint = __jointMgr.getJoint(__targetNodeName);
		const Joint *const pSrcJoint = __jointMgr.getJoint(__srcNodeName);

		const mat4& targetJointMat = pTargetJoint->getMatrix();
		const mat4& srcJointMat = pSrcJoint->getMatrix();

		retVal = (inverse(srcJointMat) * targetJointMat * __offsetMat);
	}
}