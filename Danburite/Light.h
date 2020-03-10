#pragma once

#include "Object.h"
#include "LightUniformDeployable.h"
#include <array>
#include "ShaderIdentifier.h"
#include "LightUniformSetter.h"
#include "LightType.h"
#include "LightException.h"

namespace Danburite
{
	class Light abstract : public ObjectGL::Object<glm::uint>, virtual public LightUniformDeployable
	{
	private:
		class LightIDAllocator
		{
		private:
			std::array<bool, ShaderIdentifier::Value::Light::MAX_NUM_LIGHTS> __occupationMap { false };

		public:
			glm::uint allocate();
			void deallocate(const glm::uint id) noexcept;
		};

		ObjectGL::UniformSetter &__uniformSetter;
		LightUniformSetter __lightUniformSetter;
		const std::string __enabledName;

		void __release() noexcept;

		static std::unordered_map<ObjectGL::UniformSetter *, LightIDAllocator> &__getAllocatorMap() noexcept;

	public:
		Light(ObjectGL::UniformSetter &uniformSetter, const LightType type) noexcept;

		void setEnabled(const bool enabled) noexcept;
		void selfDeploy() noexcept;

		virtual void bakeDepthMap() noexcept = 0;

		virtual ~Light() noexcept;
	};
}