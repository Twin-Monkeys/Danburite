#include "DepthBaker.h"
#include "Constant.h"
#include "GLFunctionWrapper.h"
#include "Material.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DepthBaker::DepthBaker() :
		__depthBakingProgram(ProgramFactory::getInstance().getProgram(ProgramType::DEPTH_BAKING)),
		__pFrameBuffer(make_unique<FrameBuffer>()),
		__pDepthMap(make_unique<AttachableTexture2D>()),
		__cameraSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Value::UniformBlockBindingPoint::CAMERA))
	{
		__pFrameBuffer->setInputColorBuffer(ColorBufferType::NONE);
		__pFrameBuffer->setOutputColorBuffer(ColorBufferType::NONE);

		__createDepthMap();
		setResolution(Constant::Shadow::DEFAULT_MAP_WIDTH, Constant::Shadow::DEFAULT_MAP_HEIGHT);
	}

	void DepthBaker::__createDepthMap() noexcept
	{
		__pDepthMap = make_unique<AttachableTexture2D>();
		__pDepthMap->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pDepthMap->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_BORDER);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_BORDER);
		__pDepthMap->setStates(TextureParamType::TEXTURE_BORDER_COLOR, {1.f, 1.f, 1.f, 1.f });
	}

	void DepthBaker::setResolution(const GLsizei width, const GLsizei height) noexcept
	{
		__mapWidth = width;
		__mapHeight = height;

		if (__pDepthMap->isHandleCreated())
			__createDepthMap();

		__pDepthMap->memoryAlloc(
			width, height,
			TextureInternalFormatType::DEPTH_COMPONENT, TextureExternalFormatType::DEPTH_COMPONENT,
			TextureDataType::FLOAT);

		__pFrameBuffer->attach(AttachmentType::DEPTH_ATTACHMENT, *__pDepthMap);
	}

	void DepthBaker::deployViewProjMatrix(const mat4 &viewMat, const mat4 &projMat) noexcept
	{
		__cameraSetter.setUniformMat4(ShaderIdentifier::Name::Camera::VIEW_MATRIX, viewMat);
		__cameraSetter.setUniformMat4(ShaderIdentifier::Name::Camera::PROJECTION_MATRIX, projMat);
	}

	void DepthBaker::bind() noexcept
	{
		glGetIntegerv(GL_VIEWPORT, __viewportArgs);
		glViewport(0, 0, __mapWidth, __mapHeight);

		__depthBakingProgram.bind();
		__pFrameBuffer->clearDepthBuffer(1.f);
	}

	void DepthBaker::unbind() noexcept
	{
		FrameBuffer::unbind();
		glViewport(__viewportArgs[0], __viewportArgs[1], __viewportArgs[2], __viewportArgs[3]);
	}

	GLuint64 DepthBaker::getDepthMapHandle() noexcept
	{
		return __pDepthMap->getHandle();
	}
}