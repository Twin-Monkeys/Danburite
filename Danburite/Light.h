#pragma once

#include "Object.h"
#include "LightUniformDeployable.h"
#include <array>
#include "ShaderIdentifier.h"
#include "LightUniformSetter.h"
#include "LightType.h"
#include "LightException.h"
#include "DepthBaker.h"

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

		bool __enabled;

		ObjectGL::UniformSetter &__lightParamSetter;
		LightUniformSetter __lightParamSetterWrapper;

		DepthBaker __depthBaker;

		void __release() noexcept;

		static std::unordered_map<ObjectGL::UniformSetter *, LightIDAllocator> &__getAllocatorMap() noexcept;

	protected:
		virtual const glm::mat4 &_getViewMatrix() const noexcept = 0;
		virtual const glm::mat4 &_getProjMatrix() const noexcept = 0;

	public:
		Light(
			const LightType type,
			ObjectGL::UniformSetter &lightParamSetter,
			ObjectGL::UniformSetter &cameraParamSetter);

		void selfDeploy() noexcept;

		constexpr bool isEnabled() const noexcept;
		void setEnabled(const bool enabled) noexcept;
		void setDepthMapResolution(const GLsizei width, const GLsizei height) noexcept;

		void startDepthBaking() noexcept;
		void endDepthBaking() noexcept;

		virtual ~Light() noexcept;
	};

	constexpr bool Light::isEnabled() const noexcept
	{
		return __enabled;
	}
}