#pragma once

#include "Program.h"
#include "FrameBuffer.h"
#include "AttachableTexture.h"
#include "Camera.h"
#include <memory>

namespace Danburite
{
	class DepthBaker
	{
	private:
		ObjectGL::Program &__depthBakingProgram;

		std::unique_ptr<ObjectGL::FrameBuffer> __pFrameBuffer;
		std::unique_ptr<ObjectGL::AttachableTexture> __pDepthAttachment;

		GLsizei __mapWidth;
		GLsizei __mapHeight;

		GLint __viewportArgs[4];

		const Camera &__camera;

	public:
		DepthBaker(const Camera &camera);

		void setResolution(const GLsizei width, const GLsizei height) noexcept;
		void selfDeploy() noexcept;

		void bind() noexcept;
		void unbind() noexcept;

		ObjectGL::AttachableTexture &getDepthAttachment() const noexcept;
	};
}