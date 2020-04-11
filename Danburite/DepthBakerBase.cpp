#include "DepthBakerBase.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DepthBakerBase::DepthBakerBase() :
		__pFrameBuffer(make_unique<FrameBuffer>())
	{
		__pFrameBuffer->setInputColorBuffer(ColorBufferType::NONE);
		__pFrameBuffer->setOutputColorBuffer(ColorBufferType::NONE);
	}

	void DepthBakerBase::_attachTextureToFrameBuffer(const AttachmentType attachmentType, Attachable &attachment) noexcept
	{
		__pFrameBuffer->attach(attachmentType, attachment);
	}

	void DepthBakerBase::setDepthMapSize(const GLsizei width, const GLsizei height) noexcept
	{
		__depthMapSize.x = width;
		__depthMapSize.y = height;

		_onSetDepthMapSize(width, height);
		__resolutionInit = true;
	}

	void DepthBakerBase::bind() noexcept
	{
		if (!__resolutionInit)
			setDepthMapSize(Constant::DepthBaking::DEFAULT_MAP_WIDTH, Constant::DepthBaking::DEFAULT_MAP_HEIGHT);

		glGetIntegerv(GL_VIEWPORT, __viewportArgs);
		glViewport(0, 0, __depthMapSize.x, __depthMapSize.y);

		__pFrameBuffer->clearDepthBuffer(1.f);
		_onBind();
	}

	void DepthBakerBase::unbind() noexcept
	{
		FrameBuffer::unbind();
		glViewport(__viewportArgs[0], __viewportArgs[1], __viewportArgs[2], __viewportArgs[3]);
	}
}