#pragma once

namespace ObjectGL
{
	class RenderContext;

	class ContextStateManager
	{
		friend RenderContext;

	private:
		bool __validFlag = false;

	public:
		constexpr bool isValid() const noexcept;
	};

	constexpr bool ContextStateManager::isValid() const noexcept
	{
		return __validFlag;
	}
}
