#pragma once

#include "FrameBuffer.h"
#include <memory>
#include "Constant.h"

namespace Danburite
{
	class DepthBakerBase abstract
	{
	private:
		std::unique_ptr<ObjectGL::FrameBuffer> __pFrameBuffer;

		bool __enabled = false;
		bool __allocated = false;

		glm::ivec2 __depthMapSize =
		{
			Constant::DepthBaking::DEFAULT_MAP_WIDTH,
			Constant::DepthBaking::DEFAULT_MAP_HEIGHT
		};

		GLint __viewportArgs[4];

	protected:
		virtual void _releaseDepthMap() noexcept = 0;
		virtual void _allocDepthMap(const GLsizei width, const GLsizei height) noexcept = 0;

		void _attachTextureToFrameBuffer(
			const ObjectGL::AttachmentType attachmentType, ObjectGL::Attachable &attachment) noexcept;

		virtual void _onBind() noexcept = 0;

	public:
		DepthBakerBase();

		constexpr bool isEnabled() const noexcept;
		void setEnabled(const bool enabled) noexcept;

		void setDepthMapSize(const GLsizei width, const GLsizei height) noexcept;
		constexpr const glm::ivec2 &getDepthMapSize() const noexcept;

		void bind() noexcept;
		void unbind() noexcept;

		virtual GLuint64 getDepthMapHandle() noexcept = 0;
	};

	constexpr bool DepthBakerBase::isEnabled() const noexcept
	{
		return __enabled;
	}

	constexpr const glm::ivec2 &DepthBakerBase::getDepthMapSize() const noexcept
	{
		return __depthMapSize;
	}
}