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
		virtual void _onDraw(ObjectGL::UniformBuffer &skyboxSetter, ObjectGL::VertexArray &cubeVA) noexcept override;

	public:
		CubeSkybox() noexcept;
		virtual ~CubeSkybox() = default;
	};
}