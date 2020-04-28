#pragma once

namespace Danburite
{
	class Scene abstract
	{
	protected:
		Scene() = default;

	public:
		virtual bool update(const float deltaTime) noexcept;
		virtual void draw() noexcept = 0;

		virtual ~Scene() = default;
	};
}