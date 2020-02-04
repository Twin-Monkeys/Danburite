#pragma once

#include "FrameBuffer.h"
#include "AttachableTexture.h"

namespace Danburite
{
	class DepthMapBaker
	{
	private:
		std::unique_ptr<ObjectGL::FrameBuffer> __pFrameBuffer;
		std::unique_ptr<ObjectGL::AttachableTexture> __pDepthAttachment;

		GLsizei __mapWidth;
		GLsizei __mapHeight;

	public:
		DepthMapBaker();

		void setResolution(const GLsizei width, const GLsizei height) noexcept;

		void startBaking() noexcept;
		static void endBaking() noexcept;
	};
}