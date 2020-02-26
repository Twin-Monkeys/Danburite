#pragma once

#include <Windows.h>

namespace Danburite
{
	template <typename T = float>
	class Timer
	{
	private:
		bool __runningFlag = false;

		LARGE_INTEGER __tFreq, __tStart, __tEnd;
		T __elapsedTime {};

	public:
		Timer() noexcept;

		bool start() noexcept;
		bool end() noexcept;

		constexpr T getElapsedTime() const noexcept;

		virtual ~Timer() = default;
	};

	template <typename T>
	Timer<T>::Timer() noexcept
	{
		static_assert(std::is_floating_point_v<T>, "The type parameter T must be one of the floating point types.");
		QueryPerformanceFrequency(&__tFreq);
	}

	template <typename T>
	bool Timer<T>::start() noexcept
	{
		if (!__runningFlag)
		{
			QueryPerformanceCounter(&__tStart);
			__runningFlag = true;

			return true;
		}

		return false;
	}

	template <typename T>
	bool Timer<T>::end() noexcept
	{
		if (__runningFlag)
		{
			QueryPerformanceCounter(&__tEnd);
			__elapsedTime = (
				((__tEnd.QuadPart - __tStart.QuadPart) / static_cast<T>(__tFreq.QuadPart)) * T(1000));

			if (__elapsedTime < T(0))
				__elapsedTime = T(0);

			__runningFlag = false;

			return true;
		}

		return false;
	}

	template <typename T>
	constexpr T Timer<T>::getElapsedTime() const noexcept
	{
		return __elapsedTime;
	}
}