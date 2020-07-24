#pragma once

#include "FrameBuffer.h"
#include "VertexArray.h"
#include "UniformBuffer.h"
#include "AttachmentServer.h"

namespace Danburite
{
	class PostProcessor abstract
	{
	private:
		std::unique_ptr<ObjectGL::FrameBuffer> __pFrameBuffer;
		ObjectGL::VertexArray __fullscreenQuadVA { 6 };

		AttachmentServer *__pAttachmentServer = nullptr;
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

		/*
			retrievingIndex는 순차적으로 접근해야 함에 주의.
		*/
		std::shared_ptr<ObjectGL::AttachableTextureRectangle>
			_getTexRectangle(
				const GLsizei width, const GLsizei height,
				const ObjectGL::TextureInternalFormatType internalFormat,
				const ObjectGL::TextureExternalFormatType externalFormat,
				const ObjectGL::TextureDataType dataType,
				const ObjectGL::TextureMinFilterValue minFilter,
				const ObjectGL::TextureMagFilterValue magFilter,
				const size_t retrievingIndex = 0ULL) noexcept;

		virtual void _onRender(
			ObjectGL::UniformBuffer &attachmentSetter, ObjectGL::VertexArray &fullscreenQuadVA) noexcept = 0;

		static constexpr PostProcessor *_getBoundProcessor() noexcept;

	public:
		void bind() noexcept;
		void render() noexcept;

		constexpr void setAttachmentServer(AttachmentServer *const pAttachmentServer) noexcept;

		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept = 0;

		virtual ~PostProcessor() = default;

		static void unbind() noexcept;
	};

	constexpr void PostProcessor::setAttachmentServer(AttachmentServer *const pAttachmentServer) noexcept
	{
		__pAttachmentServer = pAttachmentServer;
	}

	constexpr PostProcessor *PostProcessor::_getBoundProcessor() noexcept
	{
		return __boundProcessor;
	}
}