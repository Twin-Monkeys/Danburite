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
			$ReturnType($TargetType::*memberFunc)($Args ...args), $Args ...args);

		template <typename ...$Args>
		void process(const std::function<void($TargetType &iter)> &forEach);

		template <typename $ReturnType, typename ...$Args>
		void processIf(
			bool($TargetType::*const discriminant)() const,
			$ReturnType($TargetType::*memberFunc)($Args ...args), $Args ...args);

		template <typename $ReturnType, typename ...$Args>
		void processIf(
			const std::function<bool(const $TargetType &iter)> &discriminant,
			$ReturnType($TargetType::*memberFunc)($Args ...args), $Args ...args);
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
		$ReturnType($TargetType::*memberFunc)($Args ...args), $Args ...args)
	{
		for ($TargetType *const pTarget : __targets)
			(pTarget->*memberFunc)(std::forward<$Args>(args)...);
	}

	template <typename $TargetType>
	template <typename ...$Args>
	void BatchProcessor<$TargetType>::process(const std::function<void($TargetType &iter)> &forEach)
	{
		for ($TargetType* const pTarget : __targets)
			forEach(*pTarget);
	}

	template <typename $TargetType>
	template <typename $ReturnType, typename ...$Args>
	void BatchProcessor<$TargetType>::processIf(
		bool($TargetType::*const discriminant)() const,
		$ReturnType($TargetType::*memberFunc)($Args ...args), $Args ...args)
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
		$ReturnType($TargetType::*memberFunc)($Args ...args), $Args ...args)
	{
		for ($TargetType *const pTarget : __targets)
		{
			if (discriminant(*pTarget))
				(pTarget->*memberFunc)(std::forward<$Args>(args)...);
		}
	}
}
