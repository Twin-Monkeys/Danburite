#pragma once

namespace ObjectGL
{
	class RenderContext;

	class ContextStateManager
	{
		friend RenderContext;

	private:
		bool __validFlag = false;

	protected:
		constexpr void _setValid(const bool valid) noexcept;

	public:
		constexpr bool isValid() const noexcept;
	};

	constexpr void ContextStateManager::_setValid(const bool valid) noexcept
	{
		__validFlag = valid;
	}

	constexpr bool ContextStateManager::isValid() const noexcept
	{
		return __validFlag;
	}
}
