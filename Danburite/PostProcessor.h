#pragma once

#include "FrameBuffer.h"
#include "VertexArray.h"
#include "UniformBuffer.h"
#include "Attachable.h"

namespace Danburite
{
	class PostProcessor abstract
	{
	private:
		std::unique_ptr<ObjectGL::FrameBuffer> __pFrameBuffer;
		ObjectGL::VertexArray __fullscreenQuadVA { 6 };

		ObjectGL::UniformBuffer &__attachmentSetter;

		static inline PostProcessor *__boundProcessor = nullptr;

		PostProcessor(const PostProcessor &) = delete;
		PostProcessor &operator=(const PostProcessor &) = delete;

	protected:
		PostProcessor();
		
		void _attach(const ObjectGL::AttachmentType attachmentType, ObjectGL::Attachable &attachment) noexcept;
		bool _detach(const ObjectGL::AttachmentType attachmentType) noexcept;

		void _setInputColorBuffer(const ObjectGL::ColorBufferType type) noexcept;
		void _setOutputColorBuffer(const ObjectGL::ColorBufferType type) noexcept;
		void _setOutputColorBuffers(const std::initializer_list<ObjectGL::ColorBufferType> &types) noexcept;

		virtual void _onRender(
			ObjectGL::UniformBuffer &attachmentSetter, ObjectGL::VertexArray &fullscreenQuadVA) noexcept = 0;

		static constexpr PostProcessor *_getBoundProcessor() noexcept;

	public:
		void bind() noexcept;
		void render() noexcept;

		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept = 0;

		virtual ~PostProcessor() = default;

		static void unbind() noexcept;
	};

	constexpr PostProcessor *PostProcessor::_getBoundProcessor() noexcept
	{
		return __boundProcessor;
	}
}