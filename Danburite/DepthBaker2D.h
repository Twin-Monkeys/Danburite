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

		std::unique_ptr<ObjectGL::AttachableTexture2D> __pDepthMap;
		ObjectGL::UniformSetter &__cameraSetter;

		glm::mat4 __viewMat { 1.f };
		glm::mat4 __projMat { 1.f };

		void __createDepthMap() noexcept;

	protected:
		virtual void _onSetResolution(const GLsizei width, const GLsizei height) noexcept override;
		virtual void _onBind() noexcept override;

	public:
		DepthBaker2D();
		void setViewProjMatrix(const glm::mat4 &viewMat, const glm::mat4 &projMat) noexcept;

		virtual GLuint64 getDepthMapHandle() noexcept override;
	};
}