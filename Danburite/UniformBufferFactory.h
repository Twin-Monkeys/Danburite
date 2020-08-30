#pragma once

#include "RenderContext.h"
#include <typeindex>
#include <any>
#include "DeferredUniformBuffer.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	class UniformBufferFactory : public ObjectGL::ContextDependentSingleton<UniformBufferFactory>
	{
		friend ObjectGL::ContextDependentSingleton<UniformBufferFactory>;

	private:
		std::unordered_map<std::type_index, std::any> __uniformBufferCache;

		UniformBufferFactory() = default;

	public:
		template <typename $UniformInterfaceType>
		DeferredUniformBuffer<$UniformInterfaceType> &getUniformBuffer();
	};

	template <typename $UniformInterfaceType>
	DeferredUniformBuffer<$UniformInterfaceType> &UniformBufferFactory::getUniformBuffer()
	{
		using namespace std;
		using namespace ObjectGL;

		const type_index RTTI { typeid($UniformInterfaceType) };

		auto resultIt = __uniformBufferCache.find(RTTI);
		if (resultIt != __uniformBufferCache.end())
		{
			const shared_ptr<DeferredUniformBuffer<$UniformInterfaceType>> &pRetVal =
				any_cast<shared_ptr<DeferredUniformBuffer<$UniformInterfaceType>>>(resultIt->second);

			return *pRetVal;
		}

		const shared_ptr<DeferredUniformBuffer<$UniformInterfaceType>> &pRetVal =
			make_shared<DeferredUniformBuffer<$UniformInterfaceType>>();

		__uniformBufferCache.emplace(RTTI, pRetVal);
		return *pRetVal;
	}
}
