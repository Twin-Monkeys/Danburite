#pragma once

#include "VertexBuffer.h"
#include "Transform.h"
#include "Updatable.h"

namespace Danburite
{
	class ModelMatrixBuffer : private ObjectGL::VertexBuffer
	{
	private:
		size_t __numInstances;
		std::vector<Transform> __transforms;
		std::vector<glm::mat4> __modelMatrices;

	public:
		ModelMatrixBuffer(const size_t numInstances = 1ULL);

		constexpr const std::vector<glm::mat4> &getModelMatrices() const noexcept;
		Transform &getTransform(const size_t idx) noexcept;

		constexpr size_t getNumInstances() const noexcept;
		void setNumInstances(const size_t numInstances) noexcept;

		void updateMatrix(const float deltaTime) noexcept;
		void updateMatrix(const float deltaTime, const std::vector<glm::mat4> &parentModelMatrices) noexcept;

		void selfDeploy() noexcept;

		virtual ~ModelMatrixBuffer() = default;
	};

	constexpr const std::vector<glm::mat4> &ModelMatrixBuffer::getModelMatrices() const noexcept
	{
		return __modelMatrices;
	}

	constexpr size_t ModelMatrixBuffer::getNumInstances() const noexcept
	{
		return __numInstances;
	}
}