#pragma once

#include "Material.h"
#include "RefractionMaterialComponent.h"

namespace Danburite
{
	class RefractionMaterial : public Material, public RefractionMaterialComponent
	{
	protected:
		virtual void _onDeploy(MaterialUniformSetter &materialSetterr) noexcept override;
		virtual void _onRender(
			MaterialUniformSetter &target, ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		RefractionMaterial(const VertexAttributeType vertexType) noexcept;

		using Material::useNormalTexture;

		virtual ~RefractionMaterial() = default;
	};
}
