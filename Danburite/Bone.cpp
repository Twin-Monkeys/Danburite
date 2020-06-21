#include "Bone.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	Bone::Bone(const string &name, const float &timestampReference) noexcept :
		__name(name), __timestamp(timestampReference)
	{}

	void Bone::__updateTransform() noexcept
	{
		const auto &[position, rotation, scale] = __timeline.sample(__timestamp);

		__boneTransform.setPosition(position);
		__boneTransform.setRotation(rotation);
		__boneTransform.setScale(scale);
	}

	Bone &Bone::updateMatrix() noexcept
	{
		__updateTransform();
		__boneTransform.updateMatrix();
		__boneMat = __boneTransform.getModelMatrix();

		return *this;
	}

	Bone &Bone::updateMatrix(const mat4 &parentBoneMatrix) noexcept
	{
		__updateTransform();
		__boneTransform.updateMatrix();
		__boneMat = (parentBoneMatrix * __boneTransform.getModelMatrix());

		return *this;
	}
}