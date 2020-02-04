#include "DepthMapBaker.h"
#include "Constant.h"
#include "GLFunctionWrapper.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	DepthMapBaker::DepthMapBaker() :
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

	void DepthMapBaker::setResolution(const GLsizei width, const GLsizei height) noexcept
	{
		__pDepthAttachment->memoryAlloc(
			width, height,
			TextureInternalFormatType::DEPTH_COMPONENT, TextureExternalFormatType::DEPTH_COMPONENT,
			TextureDataType::FLOAT);

		__pFrameBuffer->attach(AttachmentType::DEPTH_ATTACHMENT, *__pDepthAttachment);
	}

	void DepthMapBaker::startBaking() noexcept
	{
		glViewport(0, 0, __mapWidth, __mapHeight);

		__pFrameBuffer->bind();

	}

	void DepthMapBaker::endBaking() noexcept
	{
		FrameBuffer::unbind();
	}
}