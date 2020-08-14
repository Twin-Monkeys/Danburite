#pragma once

#include "FrameBuffer.h"
#include "FullscreenDrawer.h"
#include "UniformBuffer.h"
#include "AttachmentServer.h"

namespace Danburite
{
	class PostProcessor abstract
	{
	private:
		std::unique_ptr<ObjectGL::FrameBuffer> __pFrameBuffer =
			std::make_unique<ObjectGL::FrameBuffer>();

		FullscreenDrawer __fullscreenDrawer;

		AttachmentServer *__pAttachmentServer = nullptr;
		ObjectGL::UniformBuffer &__texContainerSetter;

		PostProcessor(const PostProcessor &) = delete;
		PostProcessor &operator=(const PostProcessor &) = delete;

	protected:
		PostProcessor();
		
		void _attach(const ObjectGL::AttachmentType attachmentType, ObjectGL::Attachable &attachment) noexcept;
		bool _detach(const ObjectGL::AttachmentType attachmentType) noexcept;

		void _setInputColorBuffer(const ObjectGL::ColorBufferType type) noexcept;
		void _setOutputColorBuffer(const ObjectGL::ColorBufferType type) noexcept;
		void _setOutputColorBuffers(const std::initializer_list<ObjectGL::ColorBufferType> &types) noexcept;

		[[nodiscard]]
		std::shared_ptr<ObjectGL::AttachableTextureRectangle>
			_getTexRectangle(
				const GLsizei width, const GLsizei height,
				const ObjectGL::TextureInternalFormatType internalFormat,
				const ObjectGL::TextureExternalFormatType externalFormat,
				const ObjectGL::TextureDataType dataType,
				const ObjectGL::TextureMinFilterValue minFilter,
				const ObjectGL::TextureMagFilterValue magFilter,
				const size_t retrievingIndex = 0ULL) noexcept;

		[[nodiscard]]
		std::shared_ptr<ObjectGL::TextureMultisample>
			_getTexMultisample(
				const GLsizei width, const GLsizei height,
				const ObjectGL::TextureInternalFormatType internalFormat,
				const GLsizei numSamplePoints = ShaderIdentifier::Value::MSAA::NUM_SAMPLE_POINTS,
				const bool fixedSampleLocations = true,
				const size_t retrievingIndex = 0ULL);

		[[nodiscard]]
		std::shared_ptr<ObjectGL::RenderBuffer>
			_getRenderBuffer(
				const GLsizei width, const GLsizei height,
				const ObjectGL::RenderBufferInternalFormatType internalFormat,
				const size_t retrievingIndex = 0ULL);

		[[nodiscard]]
		std::shared_ptr<ObjectGL::RenderBufferMultisample>
			_getRenderBufferMultisample(
				const GLsizei width, const GLsizei height,
				const ObjectGL::RenderBufferInternalFormatType internalFormat,
				const GLsizei numSamplePoints = ShaderIdentifier::Value::MSAA::NUM_SAMPLE_POINTS,
				const size_t retrievingIndex = 0ULL);

		virtual void _onRender(
			ObjectGL::FrameBuffer &renderTarget,
			ObjectGL::UniformBuffer &texContainerSetter,
			FullscreenDrawer &fullscreenDrawer) noexcept = 0;

	public:
		ObjectGL::FrameBuffer &getFrameBuffer() noexcept;
		const ObjectGL::FrameBuffer &getFrameBuffer() const noexcept;

		void render(ObjectGL::FrameBuffer &renderTarget) noexcept;

		constexpr void setAttachmentServer(AttachmentServer *const pAttachmentServer) noexcept;

		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept = 0;

		virtual ~PostProcessor() = default;
	};

	constexpr void PostProcessor::setAttachmentServer(AttachmentServer *const pAttachmentServer) noexcept
	{
		__pAttachmentServer = pAttachmentServer;
	}
}