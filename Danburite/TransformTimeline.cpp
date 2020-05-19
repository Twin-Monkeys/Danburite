#include "TransformTimeline.h"

using namespace std;
using namespace glm;

namespace Danburite
{
	tuple<vec3, Quaternion, vec3> TransformTimeline::sample(const float timestamp) const noexcept
	{
		return
		{
			posTimeline.sample(timestamp),
			rotationTimeline.sample(timestamp),
			scaleTimeline.sample(timestamp)
		};
	}
}