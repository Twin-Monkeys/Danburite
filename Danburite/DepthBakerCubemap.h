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
		ObjectGL::UniformSetter &__depthBakingCubemapSetter;

		std::unique_ptr<ObjectGL::AttachableTextureCubemap> __pDepthMap;
		glm::mat4 __viewProjMatrices[6];

		void __createDepthMap() noexcept;

	protected:
		virtual void _onSetDepthMapSize(const GLsizei width, const GLsizei height) noexcept override;
		virtual void _onBind() noexcept override;

	public:
		DepthBakerCubemap();
		void setProjViewMatrix(const ObjectGL::CubemapSideType sideType, const glm::mat4 &projViewMat) noexcept;

		virtual GLuint64 getDepthMapHandle() noexcept override;
	};
}