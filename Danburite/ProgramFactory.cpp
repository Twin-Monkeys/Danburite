#include "ProgramFactory.h"
#include <array>
#include <filesystem>
#include "ResourceManager.h"
#include "VertexShaderCompiler.h"
#include "GeometryShaderCompiler.h"
#include "FragmentShaderCompiler.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace filesystem;
using namespace ObjectGL;

namespace Danburite
{
	const string &ProgramFactory::__getProgramPath(const ProgramPathType pathType, const ProgramType programType) noexcept
	{
		static const unordered_map<ProgramType, array<string, 4>> pathMap =
		{
			// Normal programs
			{
				ProgramType::MONO_COLOR,
				{
					"glsl/binary/MonoColor.bin",		// binary
					"glsl/src/PositionOnly_Vert.glsl",	// vertex shader
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
				ProgramType::REFLECTION,
				{
					"glsl/binary/Reflection.bin",
					"glsl/src/Reflection_Vert.glsl",
					"",
					"glsl/src/Reflection_Frag.glsl"
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

			// Skybox
			{
				ProgramType::SKYBOX,
				{
					"glsl/binary/Skybox.bin",
					"glsl/src/Skybox_Vert.glsl",
					"",
					"glsl/src/Skybox_Frag.glsl"
				}
			},

			// Post processing programs
			{
				ProgramType::POST_PROCESS_FORWARD,
				{
					"glsl/binary/PostProcess_Forward.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/PostProcess_Forward_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_NEGATIVE,
				{
					"glsl/binary/PostProcess_Negative.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/PostProcess_Negative_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_GRAYSCALE,
				{
					"glsl/binary/PostProcess_Grayscale.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/PostProcess_Grayscale_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_CONVOLUTIONAL,
				{
					"glsl/binary/PostProcess_Convolutional.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/PostProcess_Convolutional_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_MSAA,
				{
					"glsl/binary/PostProcess_MSAA.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/PostProcess_MSAA_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_GAMMA_CORRECTION,
				{
					"glsl/binary/PostProcess_GammaCorrection.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/PostProcess_GammaCorrection_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_HDR,
				{
					"glsl/binary/PostProcess_HDR.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/PostProcess_HDR_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_BLOOM_COLOR_EXTRACTION,
				{
					"glsl/binary/PostProcess_Bloom_ColorExtraction.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/PostProcess_Bloom_ColorExtraction_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_BLOOM_BLUR_HORIZ,
				{
					"glsl/binary/PostProcess_Bloom_BlurHoriz.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/PostProcess_Bloom_BlurHoriz_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_BLOOM_BLUR_VERT,
				{
					"glsl/binary/PostProcess_Bloom_BlurVert.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/PostProcess_Bloom_BlurVert_Frag.glsl"
				}
			},
			{
				ProgramType::POST_PROCESS_BLOOM_COMPOSITION,
				{
					"glsl/binary/PostProcess_Bloom_Composition.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/PostProcess_Bloom_Composition_Frag.glsl"
				}
			},


			// Depth baking
			{
				ProgramType::DEPTH_BAKING_2D,
				{
					"glsl/binary/DepthBaking2D.bin",
					"glsl/src/DepthBaking2D_Vert.glsl",
					"",
					"glsl/src/DepthBaking2D_Frag.glsl"
				}
			},
			{
				ProgramType::DEPTH_BAKING_CUBEMAP,
				{
					"glsl/binary/DepthBakingCubemap.bin",
					"glsl/src/DepthBakingCubemap_Vert.glsl",
					"glsl/src/DepthBakingCubemap_Geo.glsl",
					"glsl/src/DepthBakingCubemap_Frag.glsl"
				}
			},

			// Rendering Pipeline
			{
				ProgramType::LIGHT_PREPASS_GEOMETRY_EXTRACTION,
				{
					"glsl/binary/LightPrePassGeometryExtraction.bin",
					"glsl/src/LightPrePassGeometryExtraction_Vert.glsl",
					"",
					"glsl/src/LightPrePassGeometryExtraction_Frag.glsl"
				}
			},
			{
			ProgramType::LIGHT_PREPASS_LIGHTING,
				{
					"glsl/binary/LightPrePassLighting.bin",
					"glsl/src/LightPrePassLighting_Vert.glsl",
					"",
					"glsl/src/LightPrePassLighting_Frag.glsl"
				}
			},

			// WBOIT
			{
			ProgramType::WBOIT,
				{
					"glsl/binary/Wboit.bin",
					"glsl/src/FullscreenQuad_Vert.glsl",
					"",
					"glsl/src/Wboit_Frag.glsl"
				}
			}
		};

		return pathMap.at(programType)[size_t(pathType)];
	}

	Program *ProgramFactory::__createProgram(const ProgramType type)
	{
		ResourceManager &resManager = ResourceManager::getInstance();
		
		const string &BIN_PATH = __getProgramPath(ProgramPathType::BINARY, type);
		const string &VS_PATH = __getProgramPath(ProgramPathType::VERTEX_SHADER, type);
		const string &GS_PATH = __getProgramPath(ProgramPathType::GEOMETRY_SHADER, type);
		const string &FS_PATH = __getProgramPath(ProgramPathType::FRAGMENT_SHADER, type);

		if (exists(BIN_PATH))
		{
			const file_time_type
				binLastModified = last_write_time(BIN_PATH),
				vsLastModified = ShaderCompiler::getLastModifiedTime(VS_PATH),
				fsLastModified = ShaderCompiler::getLastModifiedTime(FS_PATH);

			if ((binLastModified > vsLastModified) && (binLastModified > fsLastModified))
			{
				try
				{
					if (GS_PATH.empty())
						return new Program(*resManager.getRaw(BIN_PATH.data()));
					else
					{
						const file_time_type gsLastModified = ShaderCompiler::getLastModifiedTime(GS_PATH);

						if (binLastModified > gsLastModified)
							return new Program(*resManager.getRaw(BIN_PATH.data()));
					}
				}
				catch (const ProgramException &) {}
			}
		}

		unordered_set<shared_ptr<Shader>> shaders;

		VertexShaderCompiler vsCompiler;
		vsCompiler.addSource(VS_PATH);
		shaders.emplace(vsCompiler.compile());

		if (!GS_PATH.empty())
		{
			GeometryShaderCompiler gsCompiler;
			gsCompiler.addSource(GS_PATH);
			shaders.emplace(gsCompiler.compile());
		}

		FragmentShaderCompiler fsCompiler;
		fsCompiler.addSource(FS_PATH);
		shaders.emplace(fsCompiler.compile());

		Program *const pRetVal = new Program(shaders);
		resManager.storeRaw(BIN_PATH, pRetVal->exportBinary());

		return pRetVal;
	}

	Program &ProgramFactory::getProgram(const ProgramType type)
	{
		return *__programCache.getValue(type);
	}

	shared_ptr<Program> ProgramFactory::ProgramCache::_onProvideValue(const ProgramType &key)
	{
		return shared_ptr<Program>(__createProgram(key));
	}

	const unordered_set<ProgramType> &ProgramFactory::
		getUsingProgramsFromUniformBufferName(const string &uniformBufferName) noexcept
	{
		static const unordered_map<string, unordered_set<ProgramType>>
			uniformBufferNameToUsingProgrmsMap =
		{
			{
				ShaderIdentifier::Name::UniformBuffer::MATERIAL,
				{
					ProgramType::MONO_COLOR,
					ProgramType::PHONG,
					ProgramType::REFLECTION,
					ProgramType::REFRACTION,
					ProgramType::SKYBOX,
					ProgramType::LIGHT_PREPASS_GEOMETRY_EXTRACTION
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::LIGHT,
				{
					ProgramType::PHONG,
					ProgramType::LIGHT_PREPASS_LIGHTING
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::CAMERA,
				{
					ProgramType::MONO_COLOR,
					ProgramType::PHONG,
					ProgramType::REFLECTION,
					ProgramType::REFRACTION,
					ProgramType::SKYBOX,
					ProgramType::LIGHT_PREPASS_GEOMETRY_EXTRACTION,
					ProgramType::LIGHT_PREPASS_LIGHTING
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::CONVOLUTION,
				{
					ProgramType::POST_PROCESS_CONVOLUTIONAL
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::GAMMA_CORRECTION,
				{
					ProgramType::POST_PROCESS_GAMMA_CORRECTION
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::SKYBOX,
				{
					ProgramType::SKYBOX
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::TEX_CONTAINER,
				{
					ProgramType::POST_PROCESS_FORWARD,
					ProgramType::POST_PROCESS_NEGATIVE,
					ProgramType::POST_PROCESS_GRAYSCALE,
					ProgramType::POST_PROCESS_CONVOLUTIONAL,
					ProgramType::POST_PROCESS_MSAA,
					ProgramType::POST_PROCESS_GAMMA_CORRECTION,
					ProgramType::POST_PROCESS_HDR,
					ProgramType::POST_PROCESS_BLOOM_COLOR_EXTRACTION,
					ProgramType::POST_PROCESS_BLOOM_BLUR_HORIZ,
					ProgramType::POST_PROCESS_BLOOM_BLUR_VERT,
					ProgramType::POST_PROCESS_BLOOM_COMPOSITION,
					ProgramType::LIGHT_PREPASS_LIGHTING,
					ProgramType::WBOIT
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::DEPTH_BAKING_2D,
				{
					ProgramType::DEPTH_BAKING_2D
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::DEPTH_BAKING_CUBEMAP,
				{
					ProgramType::DEPTH_BAKING_CUBEMAP
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::HDR,
				{
					ProgramType::POST_PROCESS_HDR
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::BLOOM,
				{
					ProgramType::POST_PROCESS_BLOOM_COLOR_EXTRACTION,
					ProgramType::POST_PROCESS_BLOOM_BLUR_HORIZ,
					ProgramType::POST_PROCESS_BLOOM_BLUR_VERT,
					ProgramType::POST_PROCESS_BLOOM_COMPOSITION
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::JOINT,
				{
					ProgramType::MONO_COLOR,
					ProgramType::PHONG,
					ProgramType::REFLECTION,
					ProgramType::REFRACTION,
					ProgramType::DEPTH_BAKING_2D,
					ProgramType::DEPTH_BAKING_CUBEMAP,
					ProgramType::LIGHT_PREPASS_GEOMETRY_EXTRACTION
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::BONE,
				{
					ProgramType::MONO_COLOR,
					ProgramType::PHONG,
					ProgramType::REFLECTION,
					ProgramType::REFRACTION,
					ProgramType::DEPTH_BAKING_2D,
					ProgramType::DEPTH_BAKING_CUBEMAP,
					ProgramType::LIGHT_PREPASS_GEOMETRY_EXTRACTION
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::PHONG,
				{
					ProgramType::PHONG
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::LIGHT_PREPASS,
				{
					ProgramType::PHONG,
					ProgramType::LIGHT_PREPASS_LIGHTING
				}
			},
			{
				ShaderIdentifier::Name::UniformBuffer::TRANSLUCENCY_SWITCHER,
				{
					ProgramType::MONO_COLOR,
					ProgramType::PHONG,
					ProgramType::REFLECTION,
					ProgramType::REFRACTION
				}
			}
		};

		return uniformBufferNameToUsingProgrmsMap.at(uniformBufferName);
	}
}