#include "DepthBaker2D.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "UniformBufferFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	DepthBaker2D::DepthBaker2D() :
		__depthBakingProgram(
			ProgramFactory::getInstance().getProgram(ProgramType::DEPTH_BAKING_2D)),

		__depthBaking2DSetter(
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::DEPTH_BAKING_2D))
	{
		__createDepthMap();
	}

	void DepthBaker2D::__createDepthMap() noexcept
	{
		__pDepthMap = make_unique<AttachableTexture2D>();
		__pDepthMap->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pDepthMap->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_BORDER);
		__pDepthMap->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_BORDER);
		__pDepthMap->setStates(TextureParamType::TEXTURE_BORDER_COLOR, {1.f, 1.f, 1.f, 1.f });
	}

	void DepthBaker2D::_onSetResolution(const GLsizei width, const GLsizei height) noexcept
	{
		if (__pDepthMap->isHandleCreated())
			__createDepthMap();

		__pDepthMap->memoryAlloc(
			width, height,
			TextureInternalFormatType::DEPTH_COMPONENT, TextureExternalFormatType::DEPTH_COMPONENT,
			TextureDataType::FLOAT);

		_attachTextureToFrameBuffer(AttachmentType::DEPTH_ATTACHMENT, *__pDepthMap);
	}

	void DepthBaker2D::_onBind() noexcept
	{
		__depthBaking2DSetter.setUniformMat4(
			ShaderIdentifier::Name::DepthBaking2D::PROJ_VIEW_MATRIX, __projViewMat);

		__depthBakingProgram.bind();
	}

	void DepthBaker2D::setProjViewMatrix(const mat4 &projViewMat) noexcept
	{
		__projViewMat = projViewMat;
	}

	GLuint64 DepthBaker2D::getDepthMapHandle() noexcept
	{
		return __pDepthMap->getHandle();
	}
}