#pragma once

#include "BoneManager.h"
#include "Material.h"
#include "VertexArray.h"

namespace Danburite
{
	class Mesh
	{
	private:
		const std::unique_ptr<BoneManager> __pBoneMgr;

		const std::shared_ptr<ObjectGL::VertexArray> __pVertexArray;
		std::shared_ptr<Material> __pMaterial;

	public:
		Mesh(
			const std::shared_ptr<ObjectGL::VertexArray> &pVertexArray,
			const std::shared_ptr<Material> &pMaterial = nullptr,
			std::unique_ptr<BoneManager> pBoneManager = std::make_unique<BoneManager>()) noexcept;

		constexpr const std::shared_ptr<Material> &getMaterial() const noexcept;
		void setMaterial(const std::shared_ptr<Material> &pMaterial) noexcept;

		void addVertexBuffer(const std::shared_ptr<ObjectGL::VertexBuffer> &pVertexBuffer) noexcept;

		void updateBones(const Animation &animation) noexcept;

		void draw(const GLsizei numInstances = 1) noexcept;
		void rawDrawcall(const GLsizei numInstances = 1) noexcept;

		virtual ~Mesh() = default;
	};

	constexpr const std::shared_ptr<Material> &Mesh::getMaterial() const noexcept
	{
		return __pMaterial;
	}
}
