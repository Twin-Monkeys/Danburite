#pragma once

#include "FrameBuffer.h"
#include "AttachableTexture.h"

namespace Danburite
{
	class DepthBaker
	{
	private:
		std::unique_ptr<ObjectGL::FrameBuffer> __pFrameBuffer;
		std::unique_ptr<ObjectGL::AttachableTexture> __pDepthAttachment;

		GLsizei __mapWidth;
		GLsizei __mapHeight;

		GLsizei __scrWidth;
		GLsizei __scrHeight;

	public:
		DepthBaker();

		void setResolution(const GLsizei width, const GLsizei height) noexcept;
		void setScreenSize(const GLsizei width, const GLsizei height) noexcept;

		void bind() noexcept;
		void unbind() noexcept;

		ObjectGL::AttachableTexture &getDepthAttachment() const noexcept;

	};
}