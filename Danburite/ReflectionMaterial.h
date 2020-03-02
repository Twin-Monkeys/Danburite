#pragma once

#include "Material.h"
#include "ReflectionMaterialComponent.h"

namespace Danburite
{
	class ReflectionMaterial : public Material, public ReflectionMaterialComponent
	{
	protected:
		ObjectGL::Program &_reflectionProgram;

		virtual void _onRender(
			ObjectGL::UniformSetter &uniformSetter, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		ReflectionMaterial(const VertexAttributeType vertexType, ObjectGL::UniformSetter &uniformSetter) noexcept;

		using Material::useNormalTexture;

		virtual ~ReflectionMaterial() = default;
	};
}
