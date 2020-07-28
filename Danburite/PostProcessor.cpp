#include "PostProcessor.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "GLFunctionWrapper.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PostProcessor::PostProcessor() :
		__texContainerSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::TEX_CONTAINER))
	{}

	void PostProcessor::_attach(const AttachmentType attachmentType, Attachable &attachment) noexcept
	{
		__pFrameBuffer->attach(attachmentType, attachment);
	}

	bool PostProcessor::_detach(const AttachmentType attachmentType) noexcept
	{
		return __pFrameBuffer->detach(attachmentType);
	}

	void PostProcessor::_setInputColorBuffer(const ColorBufferType type) noexcept
	{
		__pFrameBuffer->setInputColorBuffer(type);
	}

	void PostProcessor::_setOutputColorBuffer(const ColorBufferType type) noexcept
	{
		__pFrameBuffer->setOutputColorBuffer(type);
	}

	void PostProcessor::_setOutputColorBuffers(const initializer_list<ColorBufferType> &types) noexcept
	{
		__pFrameBuffer->setOutputColorBuffers(types);
	}

	shared_ptr<AttachableTextureRectangle>
		PostProcessor::_getTexRectangle(
			const GLsizei width, const GLsizei height,
			const TextureInternalFormatType internalFormat, const TextureExternalFormatType externalFormat,
			const TextureDataType dataType,
			const TextureMinFilterValue minFilter, const TextureMagFilterValue magFilter,
			const size_t retrievingIndex) noexcept
	{
		shared_ptr<AttachableTextureRectangle> pRetVal;

		if (!__pAttachmentServer)
		{
			pRetVal = make_shared<AttachableTextureRectangle>();
			pRetVal->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
			pRetVal->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
			pRetVal->setState(TextureParamType::TEXTURE_MIN_FILTER, minFilter);
			pRetVal->setState(TextureParamType::TEXTURE_MAG_FILTER, magFilter);
			pRetVal->memoryAlloc(width, height, internalFormat, externalFormat, dataType);
			pRetVal->getHandle();
		}
		else
		{
			pRetVal = __pAttachmentServer->getTexRectangle(
				width, height, internalFormat, externalFormat,
				dataType, minFilter, magFilter, retrievingIndex);
		}

		return pRetVal;
	}

	shared_ptr<TextureMultisample>
		PostProcessor::_getTexMultisample(
			const GLsizei width, const GLsizei height,
			const TextureInternalFormatType internalFormat,
			const GLsizei numSamplePoints, const bool fixedSampleLocations, const size_t retrievingIndex)
	{
		shared_ptr<TextureMultisample> pRetVal;

		if (!__pAttachmentServer)
		{
			pRetVal = make_shared<TextureMultisample>();
			pRetVal->getHandle();
		}
		else
		{
			pRetVal = __pAttachmentServer->getTexMultisample(
				width, height, internalFormat, numSamplePoints,
				fixedSampleLocations, retrievingIndex);
		}

		return pRetVal;
	}

	shared_ptr<RenderBuffer>
		PostProcessor::_getRenderBuffer(
			const GLsizei width, const GLsizei height,
			const RenderBufferInternalFormatType internalFormat,
			const size_t retrievingIndex)
	{
		shared_ptr<RenderBuffer> pRetVal;

		if (!__pAttachmentServer)
			pRetVal = make_shared<RenderBuffer>();
		else
		{
			pRetVal = __pAttachmentServer->getRenderBuffer(
				width, height, internalFormat, retrievingIndex);
		}

		return pRetVal;
	}

	shared_ptr<RenderBufferMultisample>
		PostProcessor::_getRenderBufferMultisample(
			const GLsizei width, const GLsizei height,
			const RenderBufferInternalFormatType internalFormat,
			const GLsizei numSamplePoints, const size_t retrievingIndex)
	{
		shared_ptr<RenderBufferMultisample> pRetVal;

		if (!__pAttachmentServer)
			pRetVal = make_shared<RenderBufferMultisample>();
		else
		{
			pRetVal = __pAttachmentServer->getRenderBufferMultisample(
				width, height, internalFormat, numSamplePoints, retrievingIndex);
		}

		return pRetVal;
	}

	FrameBuffer &PostProcessor::getFrameBuffer() noexcept
	{
		return *__pFrameBuffer;
	}

	const FrameBuffer &PostProcessor::getFrameBuffer() const noexcept
	{
		return *__pFrameBuffer;
	}

	void PostProcessor::bind() noexcept
	{
		__pFrameBuffer->bind();
	}

	void PostProcessor::render(PostProcessor* const pBoundProcessor) noexcept
	{
		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, false);
		_onRender(pBoundProcessor, __texContainerSetter, __fullscreenDrawer);
		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	}

	void PostProcessor::unbind() noexcept
	{
		FrameBuffer::unbind();
	}
}