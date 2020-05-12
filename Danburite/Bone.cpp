#include "Bone.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	Bone::Bone(float &playTimeReference, mat4 &boneMatrixReference) noexcept :
		__playTime(playTimeReference), __boneMat(boneMatrixReference)
	{}

	void Bone::__validateTimestamp() noexcept
	{
		__timestamp -= ((floor(__timestamp / __playTime)) * __playTime);
	}

	void Bone::__updateTransform() noexcept
	{
		if (__keyframes.empty())
			return;

		if (__keyframes.size() == 1ULL)
		{
			__currentTransform = __keyframes.begin()->second;
			return;
		}

		__validateTimestamp();

		auto lowerIt = __keyframes.lower_bound(__timestamp + Constant::Common::EPSILON);
		lowerIt--;

		// 현재 timestamp가 모든 keyframe보다 이전에 있는 경우
		if (lowerIt == __keyframes.end())
		{
			auto firstIt = __keyframes.begin();

			__currentTransform = TransformComponent::mix(
				__DEFAULT_STATE, firstIt->second, __timestamp / firstIt->first);

			return;
		}

		auto upperIt = lowerIt;
		upperIt++;

		const float timeGap = (upperIt->first - lowerIt->first);
		const float relativeTimestamp = (__timestamp - lowerIt->first);

		__currentTransform = TransformComponent::mix(
			lowerIt->second, upperIt->second, relativeTimestamp / timeGap);
	}

	Bone &Bone::addKeyframe(const float timestamp, const TransformComponent &transformComponent) noexcept
	{
		assert(__timestamp >= -Constant::Common::EPSILON);

		__playTime = max(__playTime, timestamp);
		__keyframes.emplace(timestamp, transformComponent);

		return *this;
	}

	Bone &Bone::addKeyframe(
		const float timestamp, const vec3 &position, const vec3 &scale, const Quaternion &rotation) noexcept
	{
		return addKeyframe(timestamp, {position, scale, rotation });
	}

	Bone &Bone::setTimestamp(const float timestamp) noexcept
	{
		__timestamp = timestamp;
		__children.safeTraverse(&Bone::setTimestamp, timestamp);

		return *this;
	}

	Bone &Bone::adjustTimestamp(const float deltaTime) noexcept
	{
		return setTimestamp(__timestamp + deltaTime);
	}

	Bone &Bone::rewind() noexcept
	{
		return setTimestamp(0.f);
	}

	Bone &Bone::moveToEnd() noexcept
	{
		return setTimestamp(__playTime - Constant::Common::EPSILON);
	}

	void Bone::updateMatrix() noexcept
	{
		__updateTransform();
		__currentTransform.updateMatrix();

		__boneMat = (__offsetMat * __currentTransform.getModelMatrix() * __offsetInvMat);

		__children.safeTraverse<void (Bone::*)(const mat4 &)>(&Bone::updateMatrix, __boneMat);
	}

	void Bone::updateMatrix(const mat4 &parentMatrix) noexcept
	{
		__updateTransform();
		__currentTransform.updateMatrix();

		__boneMat = (parentMatrix * __offsetMat * __currentTransform.getModelMatrix() * __offsetInvMat);

		__children.safeTraverse<void (Bone::*)(const mat4 &)>(&Bone::updateMatrix, __boneMat);
	}

	void Bone::setOffsetMatrix(const mat4 &offsetMatrix) noexcept
	{
		__offsetMat		= offsetMatrix;
		__offsetInvMat	= inverse(offsetMatrix);
	}
}