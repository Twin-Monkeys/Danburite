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
		std::unique_ptr<ObjectGL::AttachableTexture> __pDepthAttachment;

		GLsizei __mapWidth;
		GLsizei __mapHeight;

		GLint __viewportArgs[4];

		ObjectGL::UniformSetter &__viewProjSetter;

	public:
		DepthBaker(ObjectGL::UniformSetter &viewProjSetter);

		void setResolution(const GLsizei width, const GLsizei height) noexcept;
		constexpr void deployViewMatrix(const glm::mat4 &viewMat) noexcept;
		constexpr void deployProjectionMatrix(const glm::mat4 &projMat) noexcept;

		void bind() noexcept;
		void unbind() noexcept;

		ObjectGL::AttachableTexture &getDepthAttachment() const noexcept;
	};

	constexpr void DepthBaker::deployViewMatrix(const glm::mat4 &viewMat) noexcept
	{

	}

	constexpr void DepthBaker::deployProjectionMatrix(const glm::mat4 &projMat) noexcept
	{

	}
}