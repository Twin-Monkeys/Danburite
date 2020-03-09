#include "DepthBaker.h"
#include "Constant.h"
#include "GLFunctionWrapper.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	DepthBaker::DepthBaker() :
		__pFrameBuffer(make_unique<FrameBuffer>()),
		__pDepthAttachment(make_unique<AttachableTexture>())
	{
		__pFrameBuffer->setInputColorBuffer(ColorBufferType::NONE);
		__pFrameBuffer->setOutputColorBuffer(ColorBufferType::NONE);

		__pDepthAttachment->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::NEAREST);
		__pDepthAttachment->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::NEAREST);
		__pDepthAttachment->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::REPEAT);
		__pDepthAttachment->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::REPEAT);

		setResolution(Constant::Shadow::DEFAULT_MAP_WIDTH, Constant::Shadow::DEFAULT_MAP_HEIGHT);
	}

	void DepthBaker::setResolution(const GLsizei width, const GLsizei height) noexcept
	{
		__mapWidth = width;
		__mapHeight = height;

		__pDepthAttachment->memoryAlloc(
			width, height,
			TextureInternalFormatType::DEPTH_COMPONENT, TextureExternalFormatType::DEPTH_COMPONENT,
			TextureDataType::FLOAT);

		__pFrameBuffer->attach(AttachmentType::DEPTH_ATTACHMENT, *__pDepthAttachment);
	}

	void DepthBaker::bind() noexcept
	{
		glGetIntegerv(GL_VIEWPORT, __viewportArgs);
		assert(glGetError() == GL_NO_ERROR);

		glViewport(0, 0, __mapWidth, __mapHeight);
		assert(glGetError() == GL_NO_ERROR);

		__pFrameBuffer->bind();
	}

	void DepthBaker::unbind() noexcept
	{
		FrameBuffer::unbind();

		glViewport(__viewportArgs[0], __viewportArgs[1], __viewportArgs[2], __viewportArgs[3]);
		assert(glGetError() == GL_NO_ERROR);
	}

	AttachableTexture &DepthBaker::getDepthAttachment() const noexcept
	{
		return *__pDepthAttachment;
	}
}