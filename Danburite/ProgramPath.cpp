#pragma warning(disable: 6011)

#include "ProgramPath.h"
#include <unordered_map>
#include <array>

using namespace std;

namespace Danburite
{
	const string &ProgramPath::getPath(const ProgramPathType pathType, const ProgramType programType) noexcept
	{
		static const unordered_map<ProgramType, array<string, 4>> pathMap =
		{
			// Normal programs
			{
				ProgramType::MONO_COLOR,
				{
					"glsl/binary/MonoColor.bin",		// binary
					"glsl/src/MonoColor_Vert.glsl",		// vertex shader
					"",									// geometry shader
					"glsl/src/MonoColor_Frag.glsl"		// fragment shader
				},
			},
			{
				ProgramType::PHONG,
				{
					"glsl/binary/Phong.bin",
					"glsl/src/Phong_Vert.glsl",
					"",
					"glsl/src/Phong_Frag.glsl"
				}
			},
			{
				ProgramType::SILHOUETTE,
				{
					"glsl/binary/Silhouette.bin",
					"glsl/src/Silhouette_Vert.glsl",
					"",
					"glsl/src/Silhouette_Frag.glsl"
				}
			},
			{
				ProgramType::OUTLINE,
				{
					"glsl/binary/Outline.bin",
					"glsl/src/Outline_Vert.glsl",
					"",
					"glsl/src/Outline_Frag.glsl"
				}
			},
			{
				ProgramType::OUTLINE,
				{
					"glsl/binary/Outline.bin",
					"glsl/src/Outline_Vert.glsl",
					"",
					"glsl/src/Outline_Frag.glsl"
				}
			},
			{
				ProgramType::REFLECTION,
				{
					"glsl/binary/Reflection.bin",
					"glsl/src/Reflection_Vert.glsl",
					"",
					"glsl/src/Reflection_Frag.glsl"
				}
			},
			{
				ProgramType::REFLECTION_PHONG,
				{
					"glsl/binary/ReflectionPhong.bin",
					"glsl/src/Phong_Vert.glsl",
					"",
					"glsl/src/ReflectionPhong_Frag.glsl"
				}
			},
			{
				ProgramType::REFRACTION,
				{
					"glsl/binary/Refraction.bin",
					"glsl/src/Refraction_Vert.glsl",
					"",
					"glsl/src/Refraction_Frag.glsl"
				}
			},
			{
				ProgramType::GEOMETRY_DEMO,
				{
					"glsl/binary/GeometryDemo.bin",
					"glsl/src/GeometryDemo_Vert.glsl",
					"glsl/src/GeometryDemo_Geo.glsl",
					"glsl/src/GeometryDemo_Frag.glsl"
				}
			},
			{
				ProgramType::EXPLODING_PHONG,
				{
					"glsl/binary/ExplodingPhong.bin",
					"glsl/src/ExplodingPhong_Vert.glsl",
					"glsl/src/ExplodingPhong_Geo.glsl",
					"glsl/src/ExplodingPhong_Frag.glsl"
				}
			},

			// Skybox
			{
				ProgramType::SKYBOX,
				{
					"glsl/binary/Cubemap.bin",
					"glsl/src/Cubemap_Vert.glsl",
					"",
					"glsl/src/Cubemap_Frag.glsl"
				}
			},

			// Post processing programs
			{
				ProgramType::POST_PROCESS_FORWARD,
				{
					"glsl/binary/PostProcess_Forward.bin",
					"glsl/src/PostProcess_Common_Vert.glsl",
					"",
					"glsl/src/PostProcess_Forward_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_NEGATIVE,
				{
					"glsl/binary/PostProcess_Negative.bin",
					"glsl/src/PostProcess_Common_Vert.glsl",
					"",
					"glsl/src/PostProcess_Negative_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_GRAYSCALE,
				{
					"glsl/binary/PostProcess_Grayscale.bin",
					"glsl/src/PostProcess_Common_Vert.glsl",
					"",
					"glsl/src/PostProcess_Grayscale_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_CONVOLUTIONAL,
				{
					"glsl/binary/PostProcess_Convolutional.bin",
					"glsl/src/PostProcess_Common_Vert.glsl",
					"",
					"glsl/src/PostProcess_Convolutional_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_MSAA,
				{
					"glsl/binary/PostProcess_MSAA.bin",
					"glsl/src/PostProcess_Common_Vert.glsl",
					"",
					"glsl/src/PostProcess_MSAA_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_GAMMA_CORRECTION,
				{
					"glsl/binary/PostProcess_GammaCorrection.bin",
					"glsl/src/PostProcess_Common_Vert.glsl",
					"",
					"glsl/src/PostProcess_GammaCorrection_Frag.glsl"
				}
			},

			// Depth baking
			{
				ProgramType::DEPTH_BAKING,
				{
					"glsl/binary/DepthBaking.bin",
					"glsl/src/DepthBaking_Vert.glsl",
					"",
					"glsl/src/DepthBaking_Frag.glsl"
				}
			}
		};

		return pathMap.at(programType)[size_t(pathType)];
	}
}