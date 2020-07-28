#pragma once

#include "Light.h"
#include "LightException.h"
#include "ShaderIdentifier.h"

namespace Danburite
{
	class LightManager
	{
	private:
		ObjectGL::UniformBuffer &__lightSetter;
		std::vector<std::unique_ptr<Light>> __lights;

	public:
		LightManager();

		template <typename $LightType>
		$LightType &createLight();

		void deleteLight(const Light &light) noexcept;

		void selfDeploy() noexcept;

		template <typename $FunctionType, typename ...Args>
		void process(const $FunctionType function, Args &&...args);
	};

	template <typename $LightType>
	$LightType &LightManager::createLight()
	{
		using namespace std;

		static_assert(
			is_base_of_v<Light, $LightType>,
			"The type parameter must be derived from Light or its compatible types.");

		const GLuint idx = GLuint(__lights.size());

		if (idx >= ShaderIdentifier::Value::Light::MAX_NUM_LIGHTS)
			throw LightException("Cannot allocate Light ID");

		return static_cast<$LightType &>(*__lights.emplace_back(make_unique<$LightType>(idx)));
	}

	template <typename $FunctionType, typename ...Args>
	void LightManager::process(const $FunctionType function, Args &&...args)
	{
		using namespace std;

		for (const unique_ptr<Light> &pLight : __lights)
			(pLight.get()->*function)(std::forward<Args>(args)...);
	}
}
