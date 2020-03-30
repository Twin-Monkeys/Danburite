#pragma once

#include "RenderContext.h"
#include "Cache.h"
#include "UniformBuffer.h"

namespace Danburite
{
	class UniformBufferFactory : public ObjectGL::ContextDependentSingleton<UniformBufferFactory>
	{
		friend ObjectGL::ContextDependentSingleton<UniformBufferFactory>;

	private:
		class UniformBufferCache : public ObjectGL::Cache<GLuint, std::shared_ptr<ObjectGL::UniformBuffer>>
		{
		protected:
			virtual std::shared_ptr<ObjectGL::UniformBuffer> _onProvideValue(const GLuint &key) override;
		};

		UniformBufferCache __uniformBufferCache;

		UniformBufferFactory() = default;

	public:
		ObjectGL::UniformBuffer &getUniformBuffer(const GLuint uniformBlockBindingPoint);
	};
}
