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