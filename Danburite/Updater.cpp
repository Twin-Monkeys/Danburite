#include "Updater.h"

using namespace std;

namespace Danburite
{
	void Updater::addUpdatable(Updatable &updatable) noexcept
	{
		__updatableSet.emplace(&updatable);
	}

	void Updater::removeUpdatable(Updatable &updatable) noexcept
	{
		__updatableSet.erase(&updatable);
	}

	void Updater::batchUpdate(const float deltaTime) noexcept
	{
		for (Updatable *const pUpdatable : __updatableSet)
			pUpdatable->update(deltaTime);
	}
}
