#pragma once

#include <string>
#include <gl/glew.h>

namespace Danburite
{
	namespace ShaderIdentifier
	{
		namespace Name
		{
			namespace UniformBuffer
			{
				extern const std::string
					MATERIAL,
					LIGHT,
					CAMERA,
					CONVOLUTION,
					GAMMA_CORRECTION,
					SKYBOX,
					TEX_CONTAINER,
					DEPTH_BAKING_2D,
					DEPTH_BAKING_CUBEMAP,
					HDR,
					BLOOM,
					JOINT,
					BONE,
					PHONG,
					LIGHT_PREPASS,
					TRANSLUCENCY_SWITCHER
					;
			}
		}

		namespace Value
		{
			namespace VertexAttribute
			{
				constexpr GLuint
					POSITION_LOCATION		= 0U,
					COLOR_LOCATION			= 1U,
					NORMAL_LOCATION			= 2U,
					TEX_COORD_LOCATION		= 3U,
					TANGENT_LOCATION		= 4U,
					BONE_INDICES_LOCATION	= 5U,
					BONE_WEIGHTS_LOCATION	= 6U,
					MODEL_MATRIX_LOCATION	= 7U
					;
			}

			namespace UniformBlockBindingPoint
			{
				constexpr GLuint
					MATERIAL				= 0U,
					LIGHT					= 1U,
					CAMERA					= 2U,
					CONVOLUTION				= 3U,
					GAMMA_CORRECTION		= 4U,
					SKYBOX					= 5U,
					TEX_CONTAINER			= 6U,
					DEPTH_BAKING_2D			= 7U,
					DEPTH_BAKING_CUBEMAP	= 8U,
					HDR						= 9U,
					BLOOM					= 10U,
					JOINT					= 11U,
					BONE					= 12U,
					PHONG					= 13U,
					LIGHT_PREPASS			= 14U,
					TRANSLUCENCY_SWITCHER	= 15U
					;
			}

			namespace PostProcess
			{
				constexpr GLuint
					MAX_NUM_COLOR_ATTACHMENTS = 8U;
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
		}
	}
}