#include "SilhouetteMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SilhouetteMaterial::SilhouetteMaterial(
		const VertexAttributeType vertexType, UniformSetter &uniformSetter) noexcept :
		Material(MaterialType::SILHOUETTE, vertexType, uniformSetter),
		__silhouetteProgram(ProgramFactory::getInstance().getProgram(ProgramType::SILHOUETTE))
	{}

	void SilhouetteMaterial::_onRender(
		UniformSetter &uniformSetter, VertexArray& vertexArray, const GLsizei numInstances) noexcept
	{
		uniformSetter.directDeploy(*this);

		__silhouetteProgram.bind();
		vertexArray.draw(numInstances);
	}
}