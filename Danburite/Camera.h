#pragma once

#include "Updatable.h"
#include "UniformDeployable.h"
#include <glm/glm.hpp>
#include "UniformSetter.h"

namespace Danburite
{
	class Camera abstract : public Updatable, public ObjectGL::UniformDeployable
	{
	private:
		glm::mat4 __viewMat;
		glm::mat4 __projMat;

	protected:
		virtual void _onUpdateViewMatrix(glm::mat4 &viewMatrix) noexcept = 0;
		virtual void _onUpdateProjMatrix(glm::mat4 &projMatrix) noexcept = 0;
		virtual void _onDeploy(ObjectGL::UniformSetter &uniformSetter) const noexcept override;

	public:
		constexpr const glm::mat4 &getViewMatrix() const noexcept;
		constexpr const glm::mat4 &getProjectionMatrix() const noexcept;

		virtual void update(const float deltaTime) noexcept override;

		virtual ~Camera() = default;
	};

	constexpr const glm::mat4 &Camera::getViewMatrix() const noexcept
	{
		return __viewMat;
	}

	constexpr const glm::mat4 &Camera::getProjectionMatrix() const noexcept
	{
		return __projMat;
	}
}
