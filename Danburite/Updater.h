#pragma once

#include "Updatable.h"
#include "WeakPointerContainer.h"

namespace Danburite
{
	class Updater
	{
	private:
		ObjectGL::WeakPointerContainer<Updatable> __updatables;

	public:
		void addUpdatable(const std::weak_ptr<Updatable> &pUpdatable) noexcept;
		void update(const float deltaTime) noexcept;
	};
}