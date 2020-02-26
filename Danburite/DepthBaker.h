#pragma once

#include "FrameBuffer.h"
#include "AttachableTexture.h"
#include <memory>

namespace Danburite
{
	class DepthBaker
	{
	private:
		std::unique_ptr<ObjectGL::FrameBuffer> __pFrameBuffer;
		std::unique_ptr<ObjectGL::AttachableTexture> __pDepthAttachment;

		GLsizei __mapWidth;
		GLsizei __mapHeight;

		GLsizei __scrWidth = 0;
		GLsizei __scrHeight = 0;

	public:
		DepthBaker();

		void setResolution(const GLsizei width, const GLsizei height) noexcept;
		constexpr void setScreenSize(const GLsizei width, const GLsizei height) noexcept;

		void bind() noexcept;
		void unbind() noexcept;

		ObjectGL::AttachableTexture &getDepthAttachment() const noexcept;
	};

	constexpr void DepthBaker::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__scrWidth = width;
		__scrHeight = height;
	}
}