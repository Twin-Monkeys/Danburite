#pragma once

#include "ModelMatrixBuffer.h"
#include "AnimationManager.h"
#include "SceneObjectNode.h"
#include "Drawable.h"
#include "JointManager.h"

namespace Danburite
{
	class SceneObject : public Updatable, public Drawable
	{
	private:
		const std::shared_ptr<ModelMatrixBuffer> __pModelMatrixBuffer = std::make_shared<ModelMatrixBuffer>();
		AnimationManager __animMgr;
		JointManager __jointMgr;

		std::vector<std::unique_ptr<SceneObjectNode>> __nodes;
		std::unordered_map<std::string, SceneObjectNode *> __nameToNodeMap;

		SceneObjectNode *__pRootNode = nullptr;

	public:
		SceneObject() noexcept;

		SceneObjectNode &addNode(const bool setAsRoot = true, const std::string &name = "NO_NAME_NODE");
		SceneObjectNode &addNode(
			const std::shared_ptr<ObjectGL::VertexArray> &pVertexArray,
			const std::shared_ptr<Material> &pMaterial,
			const bool setAsRoot = true, const std::string& name = "NO_NAME_NODE");

		size_t getNumInstances() const noexcept;
		void setNumInstances(const GLsizei numInstances) noexcept;

		Transform &getTransform(const size_t idx = 0) noexcept;
		const Transform &getTransform(const size_t idx = 0) const noexcept;

		constexpr SceneObjectNode *getRootNode() noexcept;
		constexpr const SceneObjectNode *getRootNode() const noexcept;

		constexpr SceneObject &setRootNode(SceneObjectNode &node) noexcept;

		SceneObjectNode *getNode(const std::string &name) noexcept;
		const SceneObjectNode *getNode(const std::string &name) const noexcept;

		AnimationManager &getAnimationManager() noexcept;
		const AnimationManager &getAnimationManager() const noexcept;

		virtual void update(const float deltaTime) noexcept override;
		virtual void draw() noexcept override;
		virtual void rawDrawcall() noexcept override;

		template <typename MaterialType, typename FunctionType, typename ...Args>
		void traverseMaterial(const FunctionType function, Args &&...args);
	};

	constexpr SceneObjectNode *SceneObject::getRootNode() noexcept
	{
		return __pRootNode;
	}

	constexpr const SceneObjectNode *SceneObject::getRootNode() const noexcept
	{
		return __pRootNode;
	}

	constexpr SceneObject &SceneObject::setRootNode(SceneObjectNode &node) noexcept
	{
		__pRootNode = &node;
		return *this;
	}

	template <typename MaterialType, typename FunctionType, typename ...Args>
	void SceneObject::traverseMaterial(const FunctionType function, Args &&...args)
	{
		__pRootNode->traverseMaterial<MaterialType>(function, std::forward<Args>(args)...);
	}
}