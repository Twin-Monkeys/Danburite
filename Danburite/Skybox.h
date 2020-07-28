#pragma once

#include "VertexArray.h"
#include "UniformBuffer.h"

namespace Danburite
{
	class Skybox abstract
	{
	private:
		ObjectGL::UniformBuffer &__skyBoxSetter;
		std::shared_ptr<ObjectGL::VertexArray> __pCubeVA;

	protected:
		virtual void _onDraw(
			ObjectGL::UniformBuffer &uniformSetter, ObjectGL::VertexArray &cubeVA) noexcept = 0;

	public:
		Skybox() noexcept;

		void draw() noexcept;

		virtual ~Skybox() = default;
	};
}
