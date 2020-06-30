#pragma once

#include "VertexBuffer.h"
#include "Transform.h"
#include "Updatable.h"

namespace Danburite
{
	class ModelMatrixBuffer : private ObjectGL::VertexBuffer
	{
	private:
		std::vector<Transform> __transforms;
		std::vector<glm::mat4> __modelMatrices;

	public:
		ModelMatrixBuffer(const size_t numInstances = 1ULL);

		constexpr const std::vector<glm::mat4> &getModelMatrices() const noexcept;
		Transform &getTransform(const size_t idx) noexcept;

		size_t getNumInstances() const noexcept;
		void setNumInstances(const size_t numInstances) noexcept;

		void updateMatrices(const glm::mat4 &jointMatrix = glm::mat4 { 1.f }) noexcept;
		void updateMatrices(
			const std::vector<glm::mat4> &parentModelMatrices,
			const glm::mat4 &jointMatrix = glm::mat4 { 1.f }) noexcept;

		void selfDeploy() noexcept;

		virtual ~ModelMatrixBuffer() = default;
	};

	constexpr const std::vector<glm::mat4> &ModelMatrixBuffer::getModelMatrices() const noexcept
	{
		return __modelMatrices;
	}
}