#pragma once

#include "PhongMaterial.h"

namespace Danburite
{
	class ExplodingPhongMaterial : public PhongMaterial
	{
	protected:
		virtual void _onRender(
			MaterialUniformSetter& target, ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) noexcept override;

	public:
		ExplodingPhongMaterial(const VertexAttributeType vertexType) noexcept;

		virtual ~ExplodingPhongMaterial() = default;
	};
}
