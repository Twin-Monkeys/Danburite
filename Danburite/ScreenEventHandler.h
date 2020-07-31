#pragma once

namespace ObjectGL
{
	class ScreenEventHandler abstract
	{
	public:
		virtual void onDisplay() noexcept;
		virtual void onResize(const int width, const int height) noexcept;
		virtual void onMouseDelta(const int xDelta, const int yDelta) noexcept;
		virtual void onMouseMButtonDown(const int x, const int y) noexcept;
		virtual void onMouseMButtonUp(const int x, const int y) noexcept;
		virtual void onMouseWheel(const short zDelta) noexcept;
		virtual bool onIdle(const float deltaTime) noexcept;

		virtual ~ScreenEventHandler() = default;
	};
}
