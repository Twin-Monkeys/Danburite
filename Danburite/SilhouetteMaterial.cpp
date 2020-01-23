#include "SilhouetteMaterial.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SilhouetteMaterial::SilhouetteMaterial(const VertexAttributeType vertexType) noexcept :
		Material({ ProgramType::SILHOUETTE }, MaterialType::SILHOUETTE, vertexType)
	{}

	void SilhouetteMaterial::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		SilhouetteMaterialComponent::_onDeploy(materialSetter);
	}

	void SilhouetteMaterial::_onRender(MaterialUniformSetter &target, VertexArray &vertexArray, const GLsizei numInstances) noexcept
	{
		target.getProgram(ProgramType::SILHOUETTE).bind();
		vertexArray.draw(numInstances);
	}
}