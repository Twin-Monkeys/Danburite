#include "Updater.h"

using namespace std;

namespace Danburite
{
	void Updater::addUpdatable(const weak_ptr<Updatable>& pUpdatable) noexcept
	{
		__updatables.add(pUpdatable);
	}

	void Updater::update(const float deltaTime) noexcept
	{
		__updatables.safeTraverse(&Updatable::update, deltaTime);
	}
}
