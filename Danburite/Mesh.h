#pragma once

#include "Material.h"
#include "VertexArray.h"

namespace Danburite
{
	class Mesh
	{
	private:
		const std::shared_ptr<ObjectGL::VertexArray> __pVertexArray;
		std::shared_ptr<Material> __pMaterial;

	public:
		Mesh(
			const std::shared_ptr<ObjectGL::VertexArray> &pVertexArray,
			const std::shared_ptr<Material> &pMaterial = nullptr) noexcept;

		const std::shared_ptr<Material> &getMaterial() const noexcept;
		void setMaterial(const std::shared_ptr<Material> &pMaterial) noexcept;

		void addVertexBuffer(const std::shared_ptr<ObjectGL::VertexBuffer> &pVertexBuffer) noexcept;

		void draw(const GLsizei numInstances = 1) noexcept;

		virtual ~Mesh() = default;
	};
}
