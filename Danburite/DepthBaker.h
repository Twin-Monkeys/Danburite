#pragma once

#include "Program.h"
#include "FrameBuffer.h"
#include "AttachableTexture.h"
#include <memory>
#include "Camera.h"

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

		ObjectGL::UniformSetter &__uniformSetter;

	public:
		DepthBaker(ObjectGL::UniformSetter &uniformSetter);

		void setResolution(const GLsizei width, const GLsizei height) noexcept;
		
		void bind() noexcept;
		void unbind() noexcept;

		void deployCamera(const Camera &camera) noexcept;

		ObjectGL::AttachableTexture &getDepthAttachment() const noexcept;
	};
}