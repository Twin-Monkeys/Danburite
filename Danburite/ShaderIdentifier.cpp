#include "ShaderIdentifier.h"
#include <unordered_map>

using namespace std;

namespace Danburite
{
	namespace ShaderIdentifier
	{
		namespace Name
		{
			namespace UniformBuffer
			{
				const string
					MATERIAL				= "UBMaterial",
					LIGHT					= "UBLight",
					CAMERA					= "UBCamera",
					CONVOLUTION				= "UBConvolution",
					GAMMA_CORRECTION		= "UBGammaCorrection",
					SKYBOX					= "UBSkybox",
					TEX_CONTAINER			= "UBTextureContainer",
					DEPTH_BAKING_2D			= "UBDepthBaking2D",
					DEPTH_BAKING_CUBEMAP	= "UBDepthBakingCubemap",
					HDR						= "UBHDR",
					BLOOM					= "UBBloom",
					JOINT					= "UBJoint",
					BONE					= "UBBone",
					PHONG					= "UBPhong",
					LIGHT_PREPASS			= "UBLightPrePass",
					TRANSLUCENCY_SWITCHER	= "UBTranslucencySwitcher"
					;
			}
		}
	}
}