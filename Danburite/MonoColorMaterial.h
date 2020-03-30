#pragma once

#include "Material.h"
#include "Program.h"
#include "MonoColorMaterialComponent.h"

namespace Danburite
{
	class MonoColorMaterial : public Material, public MonoColorMaterialComponent
	{
	protected:
		ObjectGL::Program &_monoColorProgram;

		virtual void _onRender(
			ObjectGL::UniformSetter &uniformSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		MonoColorMaterial(const VertexAttributeType vertexType) noexcept;

		virtual ~MonoColorMaterial() = default;
	};
}