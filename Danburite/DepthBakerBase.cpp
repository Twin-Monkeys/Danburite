#include "DepthBakerBase.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DepthBakerBase::DepthBakerBase()
	{
		__pFrameBuffer->setInputColorBuffer(ColorBufferType::NONE);
		__pFrameBuffer->setOutputColorBuffer(ColorBufferType::NONE);
	}

	void DepthBakerBase::_attachTextureToFrameBuffer(const AttachmentType attachmentType, Attachable &attachment) noexcept
	{
		__pFrameBuffer->attach(attachmentType, attachment);
	}

	void DepthBakerBase::setEnabled(const bool enabled) noexcept
	{
		if (__enabled == enabled)
			return;

		__enabled = enabled;

		if (!enabled)
		{
			_releaseDepthMap();
			__allocated = false;
		}
	}

	void DepthBakerBase::setDepthMapSize(const GLsizei width, const GLsizei height) noexcept
	{
		__depthMapSize.x = width;
		__depthMapSize.y = height;
		__allocated = false;
	}

	void DepthBakerBase::bind() noexcept
	{
		if (!__allocated)
		{
			_allocDepthMap(__depthMapSize.x, __depthMapSize.y);
			__allocated = true;
		}

		glGetIntegerv(GL_VIEWPORT, __viewportArgs);
		glViewport(0, 0, __depthMapSize.x, __depthMapSize.y);

		__pFrameBuffer->clearDepthBuffer(1.f);
		_onBind();
	}

	void DepthBakerBase::unbind() noexcept
	{
		glViewport(__viewportArgs[0], __viewportArgs[1], __viewportArgs[2], __viewportArgs[3]);
	}
}