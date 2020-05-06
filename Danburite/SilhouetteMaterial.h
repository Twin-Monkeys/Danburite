#pragma once

#include "Material.h"
#include "SilhouetteMaterialComponent.h"
#include "Program.h"

namespace Danburite
{
	class SilhouetteMaterial : public Material, public SilhouetteMaterialComponent
	{
	private:
		ObjectGL::Program &__silhouetteProgram;

	protected:
		virtual void _onRender(
			ObjectGL::UniformSetter &materialSetter,
			ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) noexcept override;

	public:
		SilhouetteMaterial(const VertexAttributeFlag vertexFlag) noexcept;

		virtual ~SilhouetteMaterial() = default;
	};
}
