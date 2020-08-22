#include "SetupTransaction.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void SetupTransaction::setup(const function<void(ContextStateManager &currentStateMgr)> &setupFunc) noexcept
	{
		__setupFunc = setupFunc;
	}

	void SetupTransaction::operator()() const
	{
		__setupFunc(__stateMgr);
	}
}