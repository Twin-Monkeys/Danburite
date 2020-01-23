#pragma once

#include "Material.h"
#include "ReflectionMaterialComponent.h"

namespace Danburite
{
	class ReflectionMaterial : public Material, public ReflectionMaterialComponent
	{
	protected:
		virtual void _onDeploy(MaterialUniformSetter &materialSetterr) noexcept override;
		virtual void _onRender(
			MaterialUniformSetter &target, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		ReflectionMaterial(const VertexAttributeType vertexType) noexcept;

		using Material::useNormalTexture;

		virtual ~ReflectionMaterial() = default;
	};
}
