#pragma once

#include "DepthBakerBase.h"
#include "Program.h"
#include "AttachableTextureCubemap.h"

namespace Danburite
{
	class DepthBakerCubemap : public DepthBakerBase
	{
	private:
		ObjectGL::Program &__depthBakingProgram;

		std::unique_ptr<ObjectGL::AttachableTextureCubemap> __pDepthMap;
		glm::mat4 __viewProjMatrices[6];

		void __createDepthMap() noexcept;

	protected:
		virtual void _onSetResolution(const GLsizei width, const GLsizei height) noexcept override;
		virtual void _onBind() noexcept override;

	public:
		DepthBakerCubemap();

		void setViewProjMatrix(
			const ObjectGL::CubemapSideType sideType, const glm::mat4 &viewProjMat) noexcept;

		void setViewProjMatrix(
			const ObjectGL::CubemapSideType sideType, const glm::mat4 &viewMat, const glm::mat4 &projMat) noexcept;

		virtual GLuint64 getDepthMapHandle() noexcept override;
	};
}