#pragma once

#include "Program.h"
#include "FrameBuffer.h"
#include "AttachableTexture.h"
#include <memory>

namespace Danburite
{
	class DepthBaker
	{
	private:
		ObjectGL::Program &__depthBakingProgram;

		std::unique_ptr<ObjectGL::FrameBuffer> __pFrameBuffer;
		std::unique_ptr<ObjectGL::AttachableTexture> __pDepthMap;

		GLsizei __mapWidth;
		GLsizei __mapHeight;

		GLint __viewportArgs[4];

		ObjectGL::UniformSetter &__uniformSetter;

	public:
		DepthBaker(ObjectGL::UniformSetter &uniformSetter);

		void setResolution(const GLsizei width, const GLsizei height) noexcept;
		void deployViewProjMatrix(const glm::mat4 &viewMat, const glm::mat4 &projMat) noexcept;

		void bind() noexcept;
		void unbind() noexcept;

		ObjectGL::AttachableTexture &getDepthMap() const noexcept;
	};
}