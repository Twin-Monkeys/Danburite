#pragma once

#include "BoneOffsetManager.h"
#include "Material.h"
#include "VertexArray.h"

namespace Danburite
{
	class Mesh
	{
	private:
		const std::unique_ptr<BoneOffsetManager> __pBoneOffsetMgr;

		const std::shared_ptr<ObjectGL::VertexArray> __pVertexArray;
		std::shared_ptr<Material> __pMaterial;

	public:
		Mesh(
			const std::shared_ptr<ObjectGL::VertexArray> &pVertexArray,
			const std::shared_ptr<Material> &pMaterial = nullptr,
			std::unique_ptr<BoneOffsetManager> pBoneOffsetManager = std::make_unique<BoneOffsetManager>()) noexcept;

		constexpr const std::shared_ptr<Material> &getMaterial() const noexcept;
		void setMaterial(const std::shared_ptr<Material> &pMaterial) noexcept;

		void addVertexBuffer(const std::shared_ptr<ObjectGL::VertexBuffer> &pVertexBuffer) noexcept;

		void updateBoneMatrices(const Animation &animation) noexcept;

		void draw(const GLsizei numInstances = 1) noexcept;
		void rawDrawcall(const GLsizei numInstances = 1) noexcept;

		virtual ~Mesh() = default;
	};

	constexpr const std::shared_ptr<Material> &Mesh::getMaterial() const noexcept
	{
		return __pMaterial;
	}
}
