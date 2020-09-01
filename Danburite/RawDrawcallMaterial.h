#pragma once

#include "Material.h"
#include "MaterialException.h"

namespace Danburite
{
	class RawDrawcallMaterial : public Material
	{
	protected:
		virtual void _onRender(
			DeferredUniformBuffer<MaterialUniformInterface> &materialUB,
			ObjectGL::VertexArray &vertexArray, const GLsizei numInstances) override;

		virtual void _onRawDrawcall(
			DeferredUniformBuffer<MaterialUniformInterface> &materialUB,
			ObjectGL::VertexArray& vertexArray, const GLsizei numInstances) override;

	public:
		RawDrawcallMaterial(const VertexAttributeFlag vertexFlag) noexcept;

		virtual ~RawDrawcallMaterial() = default;
	};
}