#include "SetupTransaction.h"
#include "RenderContext.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	void SetupTransaction::setSetupFunction(
		const function<void(ContextStateManager &currentStateMgr)> &setupFunc) noexcept
	{
		__setupFunc = setupFunc;
	}

	void SetupTransaction::setup() const
	{
		__setupFunc(RenderContext::getCurrentStateManager());
	}
}