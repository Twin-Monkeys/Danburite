#pragma once

#include "SceneNodeConnecterBase.h"

namespace Danburite
{
	class StaticSceneNodeConnecter : public SceneNodeConnecterBase
	{
	private:
		const glm::mat4 __localConnectingMat;

	protected:
		virtual void _onUpdateLocalMatrix(glm::mat4 &localConnectingMatrix) noexcept override;

	public:
		StaticSceneNodeConnecter(const std::string_view &nodeName, const glm::mat4 &localConnectingMatrix) noexcept;
	};
}
