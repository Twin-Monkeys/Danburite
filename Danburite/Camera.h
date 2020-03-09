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
		void updateViewMatrix() noexcept;
		void updateProjMatrix() noexcept;

		virtual void update() noexcept override;

		virtual ~Camera() = default;
	};
}
