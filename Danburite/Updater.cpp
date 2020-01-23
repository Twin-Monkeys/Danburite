#include "Updater.h"

using namespace std;

namespace Danburite
{
	void Updater::addUpdatable(const weak_ptr<Updatable> &pUpdatable) noexcept
	{
		__updatables.add(pUpdatable);
	}

	void Updater::batchUpdate() noexcept
	{
		__updatables.safeTraverse(&Updatable::update);
	}
}
