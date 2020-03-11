#include "ShaderIdentifier.h"

using namespace std;

namespace Danburite
{
	namespace ShaderIdentifier
	{
		namespace Name
		{
			namespace Model
			{
				const string
					MODEL_MATRIX = "model.modelMat";
			}
			 
			namespace Camera
			{
				const string
					POSITION = "camera.pos",
					VIEW_MATRIX = "camera.viewMat",
					PROJECTION_MATRIX = "camera.projMat";
			}

			namespace Light
			{
				const string
					ENABLED = "enabled",
					TYPE = "type",

					ALBEDO = "albedo",
					AMBIENT_STRENGTH = "ambientStrength",
					DIFFUSE_STRENGTH = "diffuseStrength",
					SPECULAR_STRENGTH = "specularStrength",

					POSITION = "pos",
					DIRECTION = "direction",
					ATTENUATION_CONST = "attConst",
					ATTENUATION_LINEAR = "attLinear",
					ATTENUATION_QUAD = "attQuad",

					INNER_CUTOFF = "innerCutOff",
					OUTER_CUTOFF = "outerCutOff",
					
					DEPTH_MAP = "depthMap";
			}

			namespace Material
			{
				const string
					TYPE = "material.type",
					OPTION_FLAG = "material.optionFlag",
					VERTEX_FLAG = "material.vertexFlag",

					DIFFUSE_COLOR = "material.diffuseColor",
					SHININESS = "material.shininess",

					AMBIENT_TEX = "material.ambientTex",
					DIFFUSE_TEX = "material.diffuseTex",
					GAMMA = "material.gamma",

					SPECULAR_TEX = "material.specularTex",
					EMISSIVE_TEX = "material.emissiveTex",
					SHININESS_TEX = "material.shininessTex",
					ALPHA_TEX = "material.alphaTex",
					NORMAL_TEX = "material.normalTex",
					
					Z_NEAR = "material.zNear",
					Z_FAR = "material.zFar",
					
					OUTLINE_COLOR = "material.outlineColor",
					THICKNESS_RATIO = "material.thicknessRatio",
					
					ENVIRONMENT_TEX = "material.environmentTex";
			}

			namespace PostProcess
			{
				const string
					DEPTH_ATTACHMENT = "attachment.depth",
					STENCIL_ATTACHMENT = "attachment.stencil",
					COLOR_ATTACHMENT_ARRAY = "attachment.colors";
			}

			namespace Convolutional
			{
				const string
					SAMPLING_OFFSET = "convolution.samplingOffset",
					KERNEL_SIZE = "convolution.kernelSize",
					KERNEL = "convolution.kernel";
			}

			namespace GammaCorrection
			{
				const std::string
					GAMMA = "gammaCorrection.gamma";
			}

			namespace Cubemap
			{
				const string
					ALBEDO_TEX = "cubemap.albedoTex";
			}
		}
	}
}