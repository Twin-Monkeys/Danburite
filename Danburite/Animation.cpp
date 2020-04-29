#include "Animation.h"
#include "Constant.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	void Animation::update(const float deltaTime) noexcept
	{
		if (__keyframes.empty())
			return;

		__timestamp += deltaTime;
		__timestamp -= ((int(__timestamp / __playTime)) * __playTime);

		if (__keyframes.size() == 1ULL)
		{
			__currentComponent = __keyframes.begin()->second;
			return;
		}

		auto lowerIt = __keyframes.lower_bound(__timestamp + Constant::Common::EPSILON);
		lowerIt--;

		// ���� timestamp�� ��� keyframe���� ������ �ִ� ���
		if (lowerIt == __keyframes.end())
		{
			auto firstIt = __keyframes.begin();
			__currentComponent = TransformComponent::mix(__DEFAULT_STATE, firstIt->second, __timestamp / firstIt->first);
			return;
		}

		auto upperIt = lowerIt;
		upperIt++;

		const float timeGap = (upperIt->first - lowerIt->first);
		const float relativeTimestamp = (__timestamp - lowerIt->first);

		__currentComponent = TransformComponent::mix(lowerIt->second, upperIt->second, relativeTimestamp / timeGap);
	}

	void Animation::addKeyframe(const float timestamp, const TransformComponent &transformComponent) noexcept
	{
		assert(__timestamp >= -Constant::Common::EPSILON);

		__playTime = max(__playTime, timestamp);
		__keyframes.emplace(timestamp, transformComponent);
	}

	void Animation::addKeyframe(
		const float timestamp, const vec3 &position, const vec3 &scale, const Quaternion &rotation) noexcept
	{
		addKeyframe(timestamp, {position, scale, rotation });
	}
}