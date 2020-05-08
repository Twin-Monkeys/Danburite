#include "Animation.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	void Animation::__validateTimestamp() noexcept
	{
		__timestamp -= ((floor(__timestamp / __playTime)) * __playTime);
	}

	Animation &Animation::addKeyframe(const float timestamp, const TransformComponent &transformComponent) noexcept
	{
		assert(__timestamp >= -Constant::Common::EPSILON);

		__playTime = max(__playTime, timestamp);
		__keyframes.emplace(timestamp, transformComponent);

		return *this;
	}

	Animation &Animation::addKeyframe(
		const float timestamp, const vec3 &position, const vec3 &scale, const Quaternion &rotation) noexcept
	{
		return addKeyframe(timestamp, {position, scale, rotation });
	}

	void Animation::updateMatrix() noexcept
	{
		if (__keyframes.empty())
			return;

		__validateTimestamp();

		if (__keyframes.size() == 1ULL)
		{
			__currentTransform = __keyframes.begin()->second;
			return;
		}

		auto lowerIt = __keyframes.lower_bound(__timestamp + Constant::Common::EPSILON);
		lowerIt--;

		// 현재 timestamp가 모든 keyframe보다 이전에 있는 경우
		if (lowerIt == __keyframes.end())
		{
			auto firstIt = __keyframes.begin();

			__currentTransform = TransformComponent::mix(
				__DEFAULT_STATE, firstIt->second, __timestamp / firstIt->first);
		}
		else
		{
			auto upperIt = lowerIt;
			upperIt++;

			const float timeGap = (upperIt->first - lowerIt->first);
			const float relativeTimestamp = (__timestamp - lowerIt->first);

			__currentTransform = TransformComponent::mix(
				lowerIt->second, upperIt->second, relativeTimestamp / timeGap);
		}

		__currentTransform.updateMatrix();
	}
}