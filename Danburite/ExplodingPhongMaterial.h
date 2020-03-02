#pragma once

#include "PhongMaterial.h"

namespace Danburite
{
	class ExplodingPhongMaterial : public Material, public PhongMaterialComponent
	{
	protected:
		ObjectGL::Program &_explodingPhongProgram;

		virtual void _onRender(
			ObjectGL::UniformSetter &uniformSetter,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) noexcept override;

	public:
		ExplodingPhongMaterial(
			const VertexAttributeType vertexType, ObjectGL::UniformSetter &uniformSetter) noexcept;

		virtual ~ExplodingPhongMaterial() = default;
	};
}
