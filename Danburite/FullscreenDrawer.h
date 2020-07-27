#pragma once

#include "VertexArray.h"

namespace Danburite
{
	class FullscreenDrawer
	{
	private:
		ObjectGL::VertexArray __fullscreenQuadVA { 6 };

	public:
		void draw() noexcept;
	};
}