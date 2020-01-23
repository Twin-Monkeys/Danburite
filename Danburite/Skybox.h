#pragma once

#include "SkyboxUniformDeployable.h"
#include "VertexArray.h"

namespace Danburite
{
	class Skybox abstract : virtual public SkyboxUniformDeployable
	{
	private:
		SkyboxUniformSetter __skyboxUniformSetter;

	protected:
		virtual void _onDraw(SkyboxUniformSetter &target) noexcept = 0;
		static void _drawBoxVA() noexcept;

	public:
		Skybox(const std::unordered_set<ProgramType> &programTypes) noexcept;

		void draw() noexcept;

		virtual ~Skybox() = default;
	};
}
