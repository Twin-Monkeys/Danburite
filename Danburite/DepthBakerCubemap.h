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

		glm::vec3 __center;
		float __zFar;
		glm::mat4 __viewProjMatrices[6];

	protected:
		virtual void _releaseDepthMap()  noexcept override;
		virtual void _allocDepthMap(const GLsizei width, const GLsizei height) noexcept override;
		virtual void _onBind() noexcept override;

	public:
		DepthBakerCubemap();

		constexpr void setCenter(const glm::vec3& center) noexcept;
		constexpr void setFar(const float zFar) noexcept;
		void setProjViewMatrix(const ObjectGL::CubemapSideType sideType, const glm::mat4 &projViewMat) noexcept;

		virtual GLuint64 getDepthMapHandle() noexcept override;
	};

	constexpr void DepthBakerCubemap::setCenter(const glm::vec3 &center) noexcept
	{
		__center = center;
	}

	constexpr void DepthBakerCubemap::setFar(const float zFar) noexcept
	{
		__zFar = zFar;
	}
}