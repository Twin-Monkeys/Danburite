#pragma once

#include "AnimatingSceneNodeConnecter.h"
#include "StaticSceneNodeConnecter.h"
#include "SceneNodeConnecterException.h"

namespace Danburite
{
	class SceneNodeConnecterManager
	{
	private:
		const float &__timestampRef;
		std::unordered_map<std::string, std::unique_ptr<SceneNodeConnecterBase>> __connecterMap;

	public:
		SceneNodeConnecterManager(const float &timestampReference) noexcept;

		AnimatingSceneNodeConnecter& addAnimatingSceneNodeConnecter(const std::string& nodeName);
		StaticSceneNodeConnecter& addStaticSceneNodeConnecter(const std::string& nodeName, const glm::mat4& localConnectingMat);

		SceneNodeConnecterBase* getSceneNodeConnecter(const std::string& nodeName) noexcept;
		const SceneNodeConnecterBase* getSceneNodeConnecter(const std::string& nodeName) const noexcept;
	};
}
