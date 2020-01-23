#pragma once

#include "VertexBuffer.h"
#include "Transform.h"
#include "Updatable.h"

namespace Danburite
{
	class ModelMatrixBuffer : private ObjectGL::VertexBuffer, public Updatable
	{
	private:
		size_t __numInstances;
		std::vector<Transform> __transforms;
		std::vector<glm::mat4> __modelMatrices;

	public:
		ModelMatrixBuffer(const size_t numInstances = 1ULL);

		const std::vector<glm::mat4> &getModelMatrices() const noexcept;
		Transform &getTransform(const size_t idx) noexcept;

		size_t getNumInstances() const noexcept;
		void setNumInstances(const size_t numInstances) noexcept;

		virtual void update() noexcept override;
		void update(const std::vector<glm::mat4> &parentModelMatrices) noexcept;

		void selfDeploy() noexcept;

		virtual ~ModelMatrixBuffer() = default;
	};
}