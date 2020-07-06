#pragma once

#include "PostProcessor.h"
#include "AttachableTexture2D.h"
#include "RenderBuffer.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"
#include <array>

namespace Danburite
{
	template <size_t NUM_COLOR_ATTACHMENTS = 1>
	class ForwardPostProcessor : public PostProcessor
	{
	private:
		ObjectGL::Program &__program;

		std::array<std::unique_ptr<ObjectGL::AttachableTexture2D>, NUM_COLOR_ATTACHMENTS> __pColorAttachments;
		std::unique_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

	protected:
		ForwardPostProcessor(ObjectGL::Program &program);

		virtual void _onRender(
			ObjectGL::UniformBuffer &attachmentSetter, ObjectGL::VertexArray &fullscreenQuadVA) noexcept override;

	public:
		ForwardPostProcessor();
		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~ForwardPostProcessor() = default;
	};

	template <size_t NUM_COLOR_ATTACHMENTS>
	ForwardPostProcessor<NUM_COLOR_ATTACHMENTS>::ForwardPostProcessor(ObjectGL::Program &program) :
		__program(program),
		__pDepthStencilAttachment(std::make_unique<ObjectGL::RenderBuffer>())
	{
		using namespace std;
		using namespace ObjectGL;

		for (unique_ptr<AttachableTexture2D> &pColorAttachment : __pColorAttachments)
		{
			pColorAttachment = make_unique<AttachableTexture2D>();
			pColorAttachment->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
			pColorAttachment->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
			pColorAttachment->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
			pColorAttachment->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
		}
	}

	template <size_t NUM_COLOR_ATTACHMENTS>
	ForwardPostProcessor<NUM_COLOR_ATTACHMENTS>::ForwardPostProcessor() :
		ForwardPostProcessor(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_FORWARD))
	{}

	template <size_t NUM_COLOR_ATTACHMENTS>
	void ForwardPostProcessor<NUM_COLOR_ATTACHMENTS>::_onRender(
		ObjectGL::UniformBuffer &attachmentSetter, ObjectGL::VertexArray &fullscreenQuadVA) noexcept
	{
		using namespace std;
		using namespace ObjectGL;

		for (size_t i = 0ULL; i < __pColorAttachments.size(); i++)
		{
			const unique_ptr<AttachableTexture2D> &pColorAttachment = __pColorAttachments[i];

			const string &colorAttachmentName =
				ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT_ARRAY[i];

			attachmentSetter.setUniformUvec2(colorAttachmentName, TextureUtil::getHandleIfExist(pColorAttachment));
		}

		__program.bind();
		fullscreenQuadVA.draw();
	}

	template <size_t NUM_COLOR_ATTACHMENTS>
	void ForwardPostProcessor<NUM_COLOR_ATTACHMENTS>::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		using namespace std;
		using namespace ObjectGL;

		for (size_t i = 0ULL; i < __pColorAttachments.size(); i++)
		{
			const unique_ptr<AttachableTexture2D> &pColorAttachment = __pColorAttachments[i];

			pColorAttachment->memoryAlloc(
				width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB);

			_attach(AttachmentType::COLOR_ATTACHMENT0 + unsigned(i), *pColorAttachment);
		}

		__pDepthStencilAttachment->memoryAlloc(
			width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

		_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
	}
}