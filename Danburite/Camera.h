#pragma once

#include "Updatable.h"
#include <glm/glm.hpp>
#include "UniformBufferFactory.h"
#include "CameraUniformInterface.h"

namespace Danburite
{
	class Camera abstract : public Updatable
	{
	private:
		glm::mat4 __viewMat { 1.f };
		glm::mat4 __projMat { 1.f };

		DeferredUniformBuffer<CameraUniformInterface> &__cameraUB =
			UniformBufferFactory::getInstance().getUniformBuffer<CameraUniformInterface>();

	protected:
		virtual void _onDeploy(CameraUniformInterface &cameraUI) noexcept = 0;
		virtual void _onUpdateViewMatrix(glm::mat4 &viewMatrix) noexcept = 0;
		virtual void _onUpdateProjMatrix(glm::mat4 &projMatrix) noexcept = 0;

	public:
		constexpr const glm::mat4 &getViewMatrix() const noexcept;
		constexpr const glm::mat4 &getProjectionMatrix() const noexcept;

		virtual void update(const float deltaTime) noexcept override;
		void selfDeploy() noexcept;

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
