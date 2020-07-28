#pragma once

#include <unordered_set>
#include "Updatable.h"

namespace Danburite
{
	class Updater
	{
	private:
		std::unordered_set<Updatable *> __updatableSet;

	public:
		void addUpdatable(Updatable &updatable) noexcept;
		void removeUpdatable(Updatable &updatable) noexcept;

		void batchUpdate(const float deltaTime) noexcept;
	};
}