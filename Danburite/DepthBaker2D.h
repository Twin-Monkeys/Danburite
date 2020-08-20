#pragma once

#include "DepthBakerBase.h"
#include "Program.h"
#include "AttachableTexture2D.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "UniformBufferFactory.h"

namespace Danburite
{
	class DepthBaker2D : public DepthBakerBase
	{
	private:
		ObjectGL::Program &__depthBakingProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::DEPTH_BAKING_2D);

		ObjectGL::UniformSetter &__depthBaking2DSetter =
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::DEPTH_BAKING_2D);

		std::unique_ptr<ObjectGL::AttachableTexture2D> __pDepthMap;

		glm::mat4 __projViewMat { 1.f };

	protected:
		virtual void _releaseDepthMap()  noexcept override;
		virtual void _allocDepthMap(const GLsizei width, const GLsizei height) noexcept override;
		virtual void _onBind() noexcept override;

	public:
		void setProjViewMatrix(const glm::mat4 &projViewMat) noexcept;

		virtual GLuint64 getDepthMapHandle() noexcept override;
	};
}