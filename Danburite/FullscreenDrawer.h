#pragma once

#include "RenderContext.h"
#include "VertexArray.h"

namespace Danburite
{
	class FullscreenDrawer : public ObjectGL::ContextDependentSingleton<FullscreenDrawer>
	{
		friend ObjectGL::ContextDependentSingleton<FullscreenDrawer>;

	private:
		ObjectGL::VertexArray __fullscreenQuadVA { 6 };
		FullscreenDrawer() = default;

	public:
		void draw() noexcept;
	};
}