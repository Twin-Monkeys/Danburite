#include "SilhouetteMaterialComponent.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	void SilhouetteMaterialComponent::_onDeploy(MaterialUniformSetter &materialSetter) noexcept
	{
		Program &silhouetteProgram = materialSetter.getProgram(ProgramType::SILHOUETTE);

		silhouetteProgram.setUniformFloat(ShaderIdentifier::Name::Material::Z_NEAR, __zNear);
		silhouetteProgram.setUniformFloat(ShaderIdentifier::Name::Material::Z_FAR, __zFar);
	}
}