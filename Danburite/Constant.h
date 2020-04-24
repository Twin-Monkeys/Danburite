#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <GL/glew.h>

namespace Danburite
{
	namespace Constant
	{
		namespace Transform
		{
			constexpr float MIN_SCALE = .001f;
			constexpr float MAX_SCALE = 1000.f;
		}

		namespace Matrix
		{
			constexpr glm::mat4 IDENTITY_MATRIX { 1.f };
		}

		namespace Light
		{
			namespace BaseComponent
			{
				constexpr glm::vec3 ALBEDO			= { 1.f, 1.f, 1.f };
				constexpr float AMBIENT_STRENGTH	= .1f;
				constexpr float DIFFUSE_STRENGH		= .8f;
				constexpr float SPECULAR_STRENGH	= .6f;
			}

			namespace AttenuatedComponent
			{
				constexpr float ATT_CONST	= 1.f;
				constexpr float ATT_LINEAR	= 0.f;
				constexpr float ATT_QUAD	= 0.f;
			}

			namespace SpotComponent
			{
				constexpr float INNER_CUTOFF_ANGLE = (glm::quarter_pi<float>() * .5f);
				constexpr float OUTER_CUTOFF_ANGLE = (glm::quarter_pi<float>() * .6f);
			}
		}

		namespace Camera
		{
			// Ortho
			constexpr float DEFAULT_ORTHO_HEIGHT	= 40.f;
			constexpr float MAX_ORTHO_HEIGHT		= 400.f;
			constexpr float MIN_ORTHO_HEIGHT		= 10.f;

			// Perspective
			constexpr float MAX_PITCH				= (glm::half_pi<float>() * .9f);
			constexpr float DEFAULT_FOV				= glm::quarter_pi<float>();
			constexpr float MAX_FOV					= (DEFAULT_FOV * 2.f);
			constexpr float MIN_FOV					= (DEFAULT_FOV * .3f);

			// Common
			constexpr float DEFAULT_ASPECT_RATIO	= 1.f;
			constexpr float DEFAULT_Z_NEAR			= 1.f;
			constexpr float DEFAULT_Z_FAR			= 1000.f;
		}

		namespace Material
		{
			namespace Phong
			{
				constexpr float DEFAULT_SHININESS = 40.f;
			}
		}

		namespace Convolutional
		{
			constexpr GLfloat sharpenKernel3x3[] =
			{
				-1.f, -1.f, -1.f,
				-1.f, 9.f, -1.f,
				-1.f, -1.f, -1.f
			};

			constexpr GLfloat blurKernel3x3[] =
			{
				1.f / 16.f, 2.f / 16.f, 1.f / 16.f,
				2.f / 16.f, 4.f / 16.f, 2.f / 16.f,
				1.f / 16.f, 2.f / 16.f, 1.f / 16.f
			};

			constexpr GLfloat edgeDetectingKernel3x3[] =
			{
				1.f, 1.f, 1.f,
				1.f, -8.f, 1.f,
				1.f, 1.f, 1.f
			};

			constexpr GLfloat blurKernel5x5[] =
			{
				1.f / 273.f, 4.f / 273.f, 7.f / 273.f, 4.f / 273.f, 1.f / 273.f,
				4.f / 273.f, 16.f / 273.f, 26.f / 273.f, 16.f / 273.f, 4.f / 273.f,
				7.f / 273.f, 26.f / 273.f, 41.f / 273.f, 26.f / 273.f, 7.f / 273.f,
				4.f / 273.f, 16.f / 273.f, 26.f / 273.f, 16.f / 273.f, 4.f / 273.f,
				1.f / 273.f, 4.f / 273.f, 7.f / 273.f, 4.f / 273.f, 1.f / 273.f
			};
		}

		namespace GammaCorrection
		{
			constexpr float DEFAULT_GAMMA = 2.2f;
		}

		namespace DepthBaking
		{
			constexpr GLsizei DEFAULT_MAP_WIDTH		= 1024;
			constexpr GLsizei DEFAULT_MAP_HEIGHT	= 1024;
		}

		namespace HDR
		{
			constexpr GLfloat DEFAULT_EXPOSURE		= 5.f;
		}
	}
}