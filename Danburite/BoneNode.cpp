#include "BoneNode.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	BoneNode::BoneNode(const string &name, const float &timestampReference) noexcept :
		__name(name), __timestamp(timestampReference)
	{}

	void BoneNode::__updateTransform() noexcept
	{
		const auto &[position, rotation, scale] = __timeline.sample(__timestamp);

		__boneTransform.setPosition(position);
		__boneTransform.setRotation(rotation);
		__boneTransform.setScale(scale);
	}

	BoneNode &BoneNode::updateMatrix() noexcept
	{
		__updateTransform();
		__boneTransform.updateMatrix();
		__boneMat = __boneTransform.getModelMatrix();

		return *this;
	}

	BoneNode &BoneNode::updateMatrix(const mat4 &parentNodeMatrix) noexcept
	{
		__updateTransform();
		__boneTransform.updateMatrix();
		__boneMat = (parentNodeMatrix * __boneTransform.getModelMatrix());

		return *this;
	}
}