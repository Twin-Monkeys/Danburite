#include "SilhouetteMaterial.h"
#include "ProgramFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	SilhouetteMaterial::SilhouetteMaterial(const VertexAttributeFlag vertexFlag) noexcept :
		Material(MaterialType::SILHOUETTE, vertexFlag),
		__silhouetteProgram(ProgramFactory::getInstance().getProgram(ProgramType::SILHOUETTE))
	{}

	void SilhouetteMaterial::_onRender(
		UniformSetter &materialSetter, VertexArray& vertexArray, const GLsizei numInstances) noexcept
	{
		_deploySilhouetteComponent(materialSetter);

		__silhouetteProgram.bind();
		vertexArray.draw(numInstances);
	}
}