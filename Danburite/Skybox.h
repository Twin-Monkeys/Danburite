#pragma once

#include "VertexArray.h"
#include "UniformSetter.h"

namespace Danburite
{
	class Skybox abstract
	{
	private:
		ObjectGL::UniformSetter &__skyBoxSetter;

	protected:
		virtual void _onDraw(ObjectGL::UniformSetter &uniformSetter) noexcept = 0;
		static void _drawBoxVA() noexcept;

	public:
		Skybox() noexcept;

		void draw() noexcept;

		virtual ~Skybox() = default;
	};
}
