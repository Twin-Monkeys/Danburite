#include "RCDSRegisterer.h"
#include "RenderContext.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "FullscreenDrawer.h"

using namespace ObjectGL;

namespace Danburite
{
	void RCDSRegisterer::batchRegister() noexcept
	{
		RenderContext::registerContextDependentSingleton<ProgramFactory>();
		RenderContext::registerContextDependentSingleton<UniformBufferFactory>();
		RenderContext::registerContextDependentSingleton<FullscreenDrawer>();
	}
}