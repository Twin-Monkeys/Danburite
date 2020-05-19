#pragma once

#include <map>
#include "Lerp.h"
#include "TimelineWrappingType.h"

namespace Danburite
{
	template <typename ComponentType>
	class Timeline
	{
	private:
		const ComponentType __defaultVal;

		std::map<float, ComponentType> __keyframes;
		float __playTime = 0.f;

		TimelineWrappingType __preStateWrappingType;
		TimelineWrappingType __postStateWrappingType;

		ComponentType(*const __pInterpolateFunc)(
			const ComponentType &lhs, const ComponentType &rhs, const float weight) noexcept;

		ComponentType(*const __pExtrapolateFunc)(
			const ComponentType &lhs, const ComponentType &rhs, const float weight) noexcept;

		ComponentType (Timeline<ComponentType>::*__preStateFunc)(const float) const noexcept;
		ComponentType (Timeline<ComponentType>::*__postStateFunc)(const float) const noexcept;

		ComponentType __preStateFunc_default(const float timestamp) const noexcept;
		ComponentType __preStateFunc_nearest(const float timestamp) const noexcept;
		ComponentType __preStateFunc_extrapolate(const float timestamp) const noexcept;
		ComponentType __preStateFunc_repeat(const float timestamp) const noexcept;

		ComponentType __postStateFunc_nearest(const float timestamp) const noexcept;
		ComponentType __postStateFunc_extrapolate(const float timestamp) const noexcept;

	public:
		constexpr Timeline(const ComponentType &defaultValue = {}) noexcept;

		constexpr Timeline(
			ComponentType(*const pInterpolateFunc)(const ComponentType &, const ComponentType &, const float) noexcept,
			ComponentType(*const pExtrapolateFunc)(const ComponentType &, const ComponentType &, const float) noexcept,
			const ComponentType &defaultValue = {}
		) noexcept;

		constexpr TimelineWrappingType getPreStateWrappingType() const noexcept;
		constexpr Timeline &setPreStateWrappingType(const TimelineWrappingType type) noexcept;

		constexpr TimelineWrappingType getPostStateWrappingType() const noexcept;
		constexpr Timeline& setPostStateWrappingType(const TimelineWrappingType type) noexcept;

		Timeline &addKeyframe(const float timestamp, const ComponentType &component) noexcept;

		ComponentType sample(const float timestamp) const noexcept;
	};

	template <typename ComponentType>
	constexpr Timeline<ComponentType>::Timeline(const ComponentType &defaultValue) noexcept :
		Timeline(Lerp::interpolate<ComponentType>, Lerp::extrapolate<ComponentType>, defaultValue)
	{}

	template <typename ComponentType>
	constexpr Timeline<ComponentType>::Timeline(
		ComponentType(*const pInterpolateFunc)(const ComponentType &, const ComponentType &, const float) noexcept,
		ComponentType(*const pExtrapolateFunc)(const ComponentType &, const ComponentType &, const float) noexcept,
		const ComponentType &defaultValue) noexcept :
		__pInterpolateFunc(pInterpolateFunc), __pExtrapolateFunc(pExtrapolateFunc), __defaultVal(defaultValue)
	{
		setPreStateWrappingType(TimelineWrappingType::DEFAULT);
		setPostStateWrappingType(TimelineWrappingType::DEFAULT);
	}

	template <typename ComponentType>
	ComponentType Timeline<ComponentType>::__preStateFunc_default(const float) const noexcept
	{
		return ComponentType {};
	}

	template <typename ComponentType>
	ComponentType Timeline<ComponentType>::__preStateFunc_nearest(const float) const noexcept
	{
		return __keyframes.begin()->second;
	}

	template <typename ComponentType>
	ComponentType Timeline<ComponentType>::__preStateFunc_extrapolate(const float timestamp) const noexcept
	{
		auto firstIt = __keyframes.begin();
		auto secondIt = firstIt;
		secondIt++;

		const float weight = ((firstIt->first - timestamp) / (secondIt->first - firstIt->first));
		return __pExtrapolateFunc(firstIt->second, secondIt->second, weight);
	}

	template <typename ComponentType>
	ComponentType Timeline<ComponentType>::__preStateFunc_repeat(const float timestamp) const noexcept
	{
		auto firstIt = __keyframes.begin();
		auto lastIt = __keyframes.rbegin();

		return sample((timestamp - ((floor(timestamp / __playTime)) * __playTime)));
	}

	template <typename ComponentType>
	ComponentType Timeline<ComponentType>::__postStateFunc_nearest(const float) const noexcept
	{
		return __keyframes.rbegin()->second;
	}

	template <typename ComponentType>
	ComponentType Timeline<ComponentType>::__postStateFunc_extrapolate(const float timestamp) const noexcept
	{
		auto lastIt = __keyframes.rbegin();
		auto lastPrevIt = lastIt;
		lastPrevIt++;

		const float weight = ((timestamp - lastIt->first) / (lastIt->first - lastPrevIt->first));
		return __pExtrapolateFunc(lastIt->second, lastPrevIt->second, weight);
	}

	template <typename ComponentType>
	constexpr TimelineWrappingType Timeline<ComponentType>::getPreStateWrappingType() const noexcept
	{
		return __preStateWrappingType;
	}

	template <typename ComponentType>
	constexpr Timeline<ComponentType> &
		Timeline<ComponentType>::setPreStateWrappingType(const TimelineWrappingType type) noexcept
	{
		__preStateWrappingType = type;

		switch (type)
		{
		case TimelineWrappingType::DEFAULT:
			__preStateFunc = &Timeline<ComponentType>::__preStateFunc_default;
			break;

		case TimelineWrappingType::NEAREST:
			__preStateFunc = &Timeline<ComponentType>::__preStateFunc_nearest;
			break;

		case TimelineWrappingType::EXTRAPOLATED:
			__preStateFunc = &Timeline<ComponentType>::__preStateFunc_extrapolate;
			break;

		case TimelineWrappingType::REPEAT:
			__preStateFunc = &Timeline<ComponentType>::__preStateFunc_repeat;
			break;

		// Invalid type
		default:
			assert(false);
			break;
		}

		return *this;
	}

	template <typename ComponentType>
	constexpr TimelineWrappingType Timeline<ComponentType>::getPostStateWrappingType() const noexcept
	{
		return __postStateWrappingType;
	}

	template <typename ComponentType>
	constexpr Timeline<ComponentType> &
		Timeline<ComponentType>::setPostStateWrappingType(const TimelineWrappingType type) noexcept
	{
		__postStateWrappingType = type;

		switch (type)
		{
		case TimelineWrappingType::DEFAULT:
			__postStateFunc = &Timeline<ComponentType>::__preStateFunc_default;
			break;

		case TimelineWrappingType::NEAREST:
			__postStateFunc = &Timeline<ComponentType>::__postStateFunc_nearest;
			break;

		case TimelineWrappingType::EXTRAPOLATED:
			__postStateFunc = &Timeline<ComponentType>::__postStateFunc_extrapolate;
			break;

		case TimelineWrappingType::REPEAT:
			__postStateFunc = &Timeline<ComponentType>::__preStateFunc_repeat;
			break;

		// Invalid type
		default:
			assert(false);
			break;
		}

		return *this;
	}

	template <typename ComponentType>
	Timeline<ComponentType> &Timeline<ComponentType>::addKeyframe(
		const float timestamp, const ComponentType &component) noexcept
	{
		__keyframes.emplace(timestamp, component);
		__playTime = glm::max(__playTime, timestamp);

		return *this;
	}

	template <typename ComponentType>
	ComponentType Timeline<ComponentType>::sample(const float timestamp) const noexcept
	{
		if (__keyframes.empty())
			return {};

		if (__keyframes.size() == 1ULL)
			return __keyframes.begin()->second;

		auto lowerIt = __keyframes.lower_bound(timestamp);
		lowerIt--;

		// preState
		if (lowerIt == __keyframes.end())
			return (this->*__preStateFunc)(timestamp);

		auto upperIt = lowerIt;
		upperIt++;

		// postState
		if (upperIt == __keyframes.end())
			return (this->*__postStateFunc)(timestamp);

		const float timeGap = (upperIt->first - lowerIt->first);
		const float relativeTimestamp = (timestamp - lowerIt->first);

		return __pInterpolateFunc(lowerIt->second, upperIt->second, relativeTimestamp / timeGap);
	}
}
