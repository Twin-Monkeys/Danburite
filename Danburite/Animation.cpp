#include "Animation.h"

using namespace ObjectGL;
using namespace std;
using namespace glm;

namespace Danburite
{
	Animation::Animation(const size_t id, const float playTime, const string &name) noexcept :
		Object(id), __playTime(playTime), __name(name), __connecterMgr(__timestamp)
	{}

	Animation& Animation::setTimestamp(const float timestamp) noexcept
	{
		if (!__repCnt)
			return *this;

		__timestamp = timestamp;
		
		if ((__timestamp > __playTime) || (__timestamp < 0.f))
		{
			if (__repCnt > 0)
			{
				__repCnt--;
			}

			if (__animationRepeatType == Danburite::AnimationRepeatType::PINGPONG)
			{
				if (__playingOrderType == AnimationPlayingOrderType::FORWARD)
					setPlayingOrder(AnimationPlayingOrderType::REVERSE);
				else
					setPlayingOrder(AnimationPlayingOrderType::FORWARD);
			}
			else
			{
				if (__repCnt)
					__timestamp -= (__playTime * floorf(__timestamp / __playTime));
			}
		}

		return *this;
	}

	Animation& Animation::adjustTimestamp(const float deltaTime) noexcept
	{
		return setTimestamp(__timestamp + (deltaTime * __playSpeed * float(__playingOrderType)));
	}
}