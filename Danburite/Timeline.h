#pragma once

#include <map>

namespace Danburite
{
	template <typename ComponentType>
	class Timeline
	{
	private:
		std::map<float, ComponentType> __keyframes;
		static const inline ComponentType __DEFAULT_VALUE {};

	public:
		Timeline &addKeyframe(const float timestamp, const ComponentType &component) noexcept;

		ComponentType sample(
			const float timestamp,
			ComponentType(*const pLerpFunc)(const ComponentType &lhs, const ComponentType &rhs, const float weight));
	};

	template <typename ComponentType>
	Timeline<ComponentType> &Timeline<ComponentType>::addKeyframe(
		const float timestamp, const ComponentType& component) noexcept
	{
		__keyframes.emplace(timestamp, transformComponent);
		return *this;
	}

	template <typename ComponentType>
	ComponentType Timeline<ComponentType>::sample(
		const float timestamp,
		ComponentType(*const pLerpFunc)(const ComponentType& lhs, const ComponentType& rhs, const float weight))
	{
		if (__keyframes.empty())
			return {};

		if (__keyframes.size() == 1ULL)
			return __keyframes.begin()->second;

		auto lowerIt = __keyframes.lower_bound(__timestamp);
		lowerIt--;

		// 현재 timestamp가 모든 keyframe보다 이전에 있는 경우
		if (lowerIt == __keyframes.end())
		{
			auto firstIt = __keyframes.begin();

			pLerpFunc(__DEFAULT_VALUE, firstIt->second, timestamp / firstIt->first);

			return;
		}

		auto upperIt = lowerIt;
		upperIt++;

		const float timeGap = (upperIt->first - lowerIt->first);
		const float relativeTimestamp = (__timestamp - lowerIt->first);

		__currentTransform = TransformComponent::mix(
			lowerIt->second, upperIt->second, relativeTimestamp / timeGap);
	}
}
