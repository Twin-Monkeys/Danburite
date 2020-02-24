#include "RCDSRegisterer.h"
#include "RenderContext.h"
#include "VertexArrayFactory.h"
#include "RenderUnitManager.h"
#include "ProgramFactory.h"

using namespace ObjectGL;

namespace Danburite
{
	void RCDSRegisterer::batchRegister() noexcept
	{
		RenderContext::registerContextDependentSingleton<VertexArrayFactory>();
		RenderContext::registerContextDependentSingleton<RenderUnitManager>();
		RenderContext::registerContextDependentSingleton<ProgramFactory>();
	}
}