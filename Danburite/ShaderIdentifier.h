#pragma once

#include <string>
#include <gl/glew.h>

namespace Danburite
{
	namespace ShaderIdentifier
	{
		namespace Name
		{
			namespace Model
			{
				extern const std::string
					MODEL_MATRIX;
			}

			namespace Camera
			{
				extern const std::string
					POSITION,
					VIEW_MATRIX,
					PROJECTION_MATRIX;
			}

			namespace Light
			{
				extern const std::string
					ENABLED,
					TYPE,

					ALBEDO,
					AMBIENT_STRENGTH,
					DIFFUSE_STRENGTH,
					SPECULAR_STRENGTH,

					POSITION,
					DIRECTION,
					ATTENUATION_CONST,
					ATTENUATION_LINEAR,
					ATTENUATION_QUAD,

					INNER_CUTOFF,
					OUTER_CUTOFF;
			}

			namespace Material
			{
				extern const std::string
					TYPE,
					OPTION_FLAG,
					VERTEX_FLAG,

					DIFFUSE_COLOR,
					SHININESS,

					AMBIENT_TEX,
					DIFFUSE_TEX,
					GAMMA,

					SPECULAR_TEX,
					EMISSIVE_TEX,
					SHININESS_TEX,
					ALPHA_TEX,
					NORMAL_TEX,

					Z_NEAR,
					Z_FAR,

					OUTLINE_COLOR,
					THICKNESS_RATIO,
					
					ENVIRONMENT_TEX;
			}

			namespace PostProcess
			{
				extern const std::string
					DEPTH_ATTACHMENT,
					STENCIL_ATTACHMENT,
					COLOR_ATTACHMENT_ARRAY;
			}

			namespace Convolutional
			{
				extern const std::string
					SAMPLING_OFFSET,
					KERNEL_SIZE,
					KERNEL;
			}

			namespace GammaCorrection
			{
				extern const std::string
					GAMMA;
			}

			namespace Cubemap
			{
				extern const std::string
					ALBEDO_TEX;
			}
		}

		namespace Value
		{
			namespace VertexAttribute
			{
				constexpr GLuint
					POSITION_LOCATION = 0,
					COLOR_LOCATION = 1,
					NORMAL_LOCATION = 2,
					TEX_COORD_LOCATION = 3;

				constexpr GLuint
					MODEL_MATRIX_LOCATION = 4;
			}

			namespace UniformBlockBindingPoint
			{
				constexpr GLuint
					MATERIAL = 0U,
					LIGHT = 1U,
					CAMERA = 2U,
					CONVOLUTION = 3U,
					GAMMA_CORRECTION = 4U;
			}

			namespace Light
			{
				constexpr GLuint
					MAX_NUM_LIGHTS = 7U;
			}

			namespace PostProcess
			{
				constexpr GLuint
					MAX_NUM_COLOR_ATTACHMENTS = 8U;

				constexpr GLint
					DEPTH_ATTACHMENT_LOCATION = 0,
					STENCIL_ATTACHMENT_LOCATION = 1,
					COLOR_ATTACHMENT_ARRAY_LOCATION = 2;
			}

			namespace MSAA
			{
				constexpr GLuint
					NUM_SAMPLE_POINTS = 4U;
			}

			namespace Convolutional
			{
				constexpr GLuint
					MAX_KERNEL_SIZE = 7U;
			}

			namespace Cubemap
			{
				constexpr GLint
					ALBEDO_TEX_LOCATION = 0;
			}
		}
	}
}