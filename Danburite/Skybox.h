#pragma once

#include "VertexArray.h"
#include "UniformSetter.h"

namespace Danburite
{
	class Skybox abstract
	{
	private:
		ObjectGL::UniformSetter &__skyBoxSetter;
		std::shared_ptr<ObjectGL::VertexArray> __pCubeVA;

	protected:
		virtual void _onDraw(ObjectGL::UniformSetter &uniformSetter) noexcept = 0;
		void _drawBoxVA() noexcept;

	public:
		Skybox() noexcept;

		void draw() noexcept;

		virtual ~Skybox() = default;
	};
}
