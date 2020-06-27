#pragma once

#include "BoneManager.h"
#include "Material.h"
#include "VertexArray.h"

namespace Danburite
{
	class Mesh
	{
	private:
		BoneManager *const __pBoneMgr;

		const std::shared_ptr<ObjectGL::VertexArray> __pVertexArray;
		std::shared_ptr<Material> __pMaterial;

	public:
		Mesh(
			const std::shared_ptr<ObjectGL::VertexArray> &pVertexArray,
			const std::shared_ptr<Material> &pMaterial = nullptr,
			BoneManager* const pBoneManager = nullptr) noexcept;

		constexpr const std::shared_ptr<Material> &getMaterial() const noexcept;
		void setMaterial(const std::shared_ptr<Material> &pMaterial) noexcept;

		void addVertexBuffer(const std::shared_ptr<ObjectGL::VertexBuffer> &pVertexBuffer) noexcept;

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
