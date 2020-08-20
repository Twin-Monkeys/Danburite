#pragma once

#include <unordered_set>
#include <functional>

namespace Danburite
{
	template <typename $TargetType>
	class BatchProcessor
	{
	private:
		std::unordered_set<$TargetType *> __targets;

	public:
		void add($TargetType &target) noexcept;
		void remove($TargetType &target) noexcept;

		template <typename $ReturnType, typename ...$Args>
		void process(
			$ReturnType($TargetType::*memberFunc)($Args...), $Args ...args);

		template <typename $ReturnType, typename ...$Args>
		void processIf(
			bool($TargetType::*discriminant)(), $ReturnType($TargetType::*memberFunc)($Args...), $Args ...args);

		template <typename $ReturnType, typename ...$Args>
		void processIf(
			const std::function<bool(const $TargetType &iter)> &discriminant, $ReturnType($TargetType::*memberFunc)($Args...), $Args ...args);
	};

	template <typename $TargetType>
	void BatchProcessor<$TargetType>::add($TargetType &target) noexcept
	{
		__targets.emplace(&target);
	}

	template <typename $TargetType>
	void BatchProcessor<$TargetType>::remove($TargetType &target) noexcept
	{
		__targets.erase(&target);
	}

	template <typename $TargetType>
	template <typename $ReturnType, typename ...$Args>
	void BatchProcessor<$TargetType>::process(
		$ReturnType($TargetType::*memberFunc)($Args...), $Args ...args)
	{
		for ($TargetType *const pTarget : __targets)
			(pTarget->*memberFunc)(std::forward<$Args>(args)...);
	}

	template <typename $TargetType>
	template <typename $ReturnType, typename ...$Args>
	void BatchProcessor<$TargetType>::processIf(
		bool($TargetType::*discriminant)(), $ReturnType($TargetType::*memberFunc)($Args...), $Args ...args)
	{
		for ($TargetType *const pTarget : __targets)
		{
			if ((pTarget->*discriminant)())
				(pTarget->*memberFunc)(std::forward<$Args>(args)...);
		}
	}

	template <typename $TargetType>
	template <typename $ReturnType, typename ...$Args>
	void BatchProcessor<$TargetType>::processIf(
		const std::function<bool(const $TargetType &iter)> &discriminant,
		$ReturnType($TargetType::*memberFunc)($Args...), $Args ...args)
	{
		for ($TargetType *const pTarget : __targets)
		{
			if (discriminant(*pTarget))
				(pTarget->*memberFunc)(std::forward<$Args>(args)...);
		}
	}
}
