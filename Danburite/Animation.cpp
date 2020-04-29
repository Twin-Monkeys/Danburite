#include "Animation.h"
#include "Constant.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	Animation::Animation() noexcept :
		__keyframes
		(
			[](const float lhs, const float rhs)
			{
				return ((lhs + Constant::Common::EPSILON) < rhs);
			}
		)
	{}

	void Animation::update(const float deltaTime) noexcept
	{
		__timestamp += deltaTime;

		if (__timestamp > __playTime)
			__timestamp -= __playTime;

		if (__keyframes.size() == 1ULL)
			__currentComponent = __keyframes.begin()->second;
		else
		{
			// circular iteration

			auto lower = __keyframes.lower_bound(__playTime);
			if (lower == __keyframes.end())
				lower--;

			auto upper = __keyframes.upper_bound(__playTime);
			if (upper == __keyframes.end())
				upper = __keyframes.begin();

			float timeGap = (upper->first - lower->first);
			if (timeGap < 0.f)
				timeGap += __playTime;

			float relativeTimestamp = (__timestamp - lower->first);
			if (relativeTimestamp < 0.f)
				relativeTimestamp += __playTime;

			__currentComponent = TransformComponent::mix(lower->second, lower->second, relativeTimestamp / timeGap);
		}
	}

	void Animation::addKeyframe(const float timestamp, const TransformComponent &transformComponent) noexcept
	{
		__playTime = max(__playTime, timestamp);
		__keyframes.emplace(timestamp, transformComponent);
	}
}