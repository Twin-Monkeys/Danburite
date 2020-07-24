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
		__pFrameBuffer(make_unique<FrameBuffer>()),
		__attachmentSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::ATTACHMENT))
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

	void PostProcessor::bind() noexcept
	{
		__boundProcessor = this;
		__pFrameBuffer->bind();
	}

	void PostProcessor::render() noexcept
	{
		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, false);
		_onRender(__attachmentSetter, __fullscreenQuadVA);
		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
	}

	void PostProcessor::unbind() noexcept
	{
		__boundProcessor = nullptr;
		FrameBuffer::unbind();
	}
}