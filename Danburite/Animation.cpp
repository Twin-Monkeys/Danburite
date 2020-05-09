#include "Animation.h"
#include "AnimationException.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	Animation::Animation(const GLuint numBones) :
		__NUM_BONES(numBones),
		__animSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::ANIMATION))
	{
		if (numBones > Constant::Animation::MAX_NUM_BONES)
			throw AnimationException("the numBones cannot be greater than MAX_NUM_BONES.");

		__boneMatrices.resize(numBones);
		__bones.reserve(numBones);

		for (GLuint i = 0U; i < numBones; i++)
			__bones.emplace_back(make_shared<Bone>(__playTime, __boneMatrices[i]));
	}

	void Animation::selfDeploy() const noexcept
	{
		__animSetter.setUniformValue(
			ShaderIdentifier::Name::Animation::BONE_MATRICES,
			__boneMatrices.data(), __NUM_BONES * sizeof(mat4));
	}

	shared_ptr<Bone> Animation::getBone(const GLuint index) noexcept
	{
		return __bones[index];
	}

	shared_ptr<const Bone> Animation::getBone(const GLuint index) const noexcept
	{
		return __bones[index];
	}

	void Animation::update(const float deltaTime) noexcept
	{
		__bones[__rootIdx]->adjustTimestamp(deltaTime).updateMatrix();
	}
}