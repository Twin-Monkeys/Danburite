#pragma once

#include "VertexArray.h"
#include "Material.h"
#include "ModelMatrixBuffer.h"
#include "BoneManager.h"

namespace Danburite
{
	class Mesh
	{
	private:
		const BoneManager &__boneMgr;

		const std::shared_ptr<ObjectGL::VertexArray> __pVertexArray;
		const std::shared_ptr<Material> __pMaterial;

	public:
		Mesh(
			const std::shared_ptr<ObjectGL::VertexArray> &pVertexArray,
			const std::shared_ptr<Material> &pMaterial,
			const std::shared_ptr<ModelMatrixBuffer> &pModelMatrixBuffer,
			const BoneManager &boneManager) noexcept;

		[[nodiscard]]
		constexpr const std::shared_ptr<Material> &getMaterial() const noexcept;

		void draw(const GLsizei numInstances = 1) noexcept;
		void rawDrawcall(const GLsizei numInstances = 1) noexcept;

		template <typename $MaterialQuery>
		void drawIf(const $MaterialQuery query, const GLsizei numInstances = 1) noexcept;

		virtual ~Mesh() = default;
	};

	constexpr const std::shared_ptr<Material> &Mesh::getMaterial() const noexcept
	{
		return __pMaterial;
	}

	template <typename $MaterialQuery>
	void Mesh::drawIf(const $MaterialQuery query, const GLsizei numInstances) noexcept
	{
		Material &material = *__pMaterial;
		if ((material.*query)())
			draw(numInstances);
	}
}
