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
		BoneManager &__boneMgr;

		const std::shared_ptr<ObjectGL::VertexArray> __pVertexArray;
		const std::shared_ptr<Material> __pMaterial;

	public:
		Mesh(
			const std::shared_ptr<ObjectGL::VertexArray> &pVertexArray,
			const std::shared_ptr<ModelMatrixBuffer> &pModelMatrixBuffer,
			const std::shared_ptr<Material> &pMaterial,
			BoneManager &boneManager) noexcept;

		constexpr const std::shared_ptr<Material> &getMaterial() const noexcept;

		void updateBoneMatrices(const glm::mat4 &jointMatrix) noexcept;

		void draw(const GLsizei numInstances = 1) noexcept;
		void rawDrawcall(const GLsizei numInstances = 1) noexcept;

		virtual ~Mesh() = default;
	};

	constexpr const std::shared_ptr<Material> &Mesh::getMaterial() const noexcept
	{
		return __pMaterial;
	}
}
