#pragma once

#include "DepthBakerBase.h"
#include "Program.h"
#include "AttachableTexture2D.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "DepthBacking2DUniformInterface.h"
#include "SetupTransaction.h"

namespace Danburite
{
	class DepthBaker2D : public DepthBakerBase
	{
	private:
		ObjectGL::Program &__depthBakingProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::DEPTH_BAKING_2D);

		DeferredUniformBuffer<DepthBacking2DUniformInterface> &__depthBaking2DUB =
			UniformBufferFactory::getInstance().getUniformBuffer<DepthBacking2DUniformInterface>();

		SetupTransaction __setupTransaction;

		std::unique_ptr<ObjectGL::AttachableTexture2D> __pDepthMap;

		glm::mat4 __projViewMat { 1.f };

	protected:
		virtual void _releaseDepthMap()  noexcept override;
		virtual void _allocDepthMap(const GLsizei width, const GLsizei height) noexcept override;
		virtual void _onBind() noexcept override;

	public:
		DepthBaker2D();
		void setProjViewMatrix(const glm::mat4 &projViewMat) noexcept;

		virtual GLuint64 getDepthMapHandle() noexcept override;
	};
}