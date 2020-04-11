#pragma once

#include "DepthBakerBase.h"
#include "Program.h"
#include "AttachableTexture2D.h"

namespace Danburite
{
	class DepthBaker2D : public DepthBakerBase
	{
	private:
		ObjectGL::Program &__depthBakingProgram;
		ObjectGL::UniformSetter &__depthBaking2DSetter;

		std::unique_ptr<ObjectGL::AttachableTexture2D> __pDepthMap;

		glm::mat4 __projViewMat { 1.f };

		void __createDepthMap() noexcept;

	protected:
		virtual void _onSetResolution(const GLsizei width, const GLsizei height) noexcept override;
		virtual void _onBind() noexcept override;

	public:
		DepthBaker2D();
		void setProjViewMatrix(const glm::mat4 &projViewMat) noexcept;

		virtual GLuint64 getDepthMapHandle() noexcept override;
	};
}