#pragma once

#include "FrameBuffer.h"
#include "VertexArray.h"
#include "Program.h"
#include "ProgramType.h"
#include "Attachable.h"

namespace Danburite
{
	class PostProcessor abstract
	{
	private:
		std::unique_ptr<ObjectGL::FrameBuffer> __pFrameBuffer;
		ObjectGL::VertexArray __fullscreenQuadVA { 6 };

		ObjectGL::Program *const __pProgram;

		PostProcessor(const PostProcessor &) = delete;
		PostProcessor &operator=(const PostProcessor &) = delete;

	protected:
		PostProcessor(const ProgramType type);
		
		void _attach(const ObjectGL::AttachmentType attachmentType, ObjectGL::Attachable &attachment) noexcept;
		bool _detach(const ObjectGL::AttachmentType attachmentType) noexcept;

		virtual void _onRender() noexcept = 0;

	public:
		void bind() noexcept;
		void render() noexcept;
		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept = 0;

		virtual ~PostProcessor() = default;

		static void unbind() noexcept;
	};
}