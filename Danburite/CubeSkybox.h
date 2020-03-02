#pragma once

#include "Skybox.h"
#include "CubeSkyboxComponent.h"
#include "Program.h"

namespace Danburite
{
	class CubeSkybox : public Skybox, public CubeSkyboxComponent
	{
	private:
		ObjectGL::Program &__skyboxProgram;

	protected:
		virtual void _onDraw(ObjectGL::UniformSetter &uniformSetter) noexcept override;

	public:
		CubeSkybox(ObjectGL::UniformSetter &uniformSetter) noexcept;

		virtual ~CubeSkybox() = default;
	};
}