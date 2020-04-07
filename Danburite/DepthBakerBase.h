#pragma once

#include "FrameBuffer.h"
#include <memory>

namespace Danburite
{
	class DepthBakerBase abstract
	{
	private:
		std::unique_ptr<ObjectGL::FrameBuffer> __pFrameBuffer;

		bool __resolutionInit = false;
		GLsizei __mapWidth;
		GLsizei __mapHeight;
		GLint __viewportArgs[4];

	protected:
		virtual void _onSetResolution(const GLsizei width, const GLsizei height) noexcept = 0;
		void _attachTextureToFrameBuffer(const ObjectGL::AttachmentType attachmentType, ObjectGL::Attachable &attachment) noexcept;

		virtual void _onBind() noexcept = 0;

	public:
		DepthBakerBase();

		void setResolution(const GLsizei width, const GLsizei height) noexcept;

		void bind() noexcept;
		void unbind() noexcept;

		virtual GLuint64 getDepthMapHandle() noexcept = 0;
	};
}