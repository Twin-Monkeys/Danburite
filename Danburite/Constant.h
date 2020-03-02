#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <GL/glew.h>

namespace Danburite
{
	namespace Constant
	{
		namespace Matrix
		{
			constexpr glm::mat4 IDENTITY_MATRIX { 1.f };
		}

		namespace Camera
		{
			constexpr float DEFAULT_X_LEFT		= -20.f;
			constexpr float DEFAULT_X_RIGHT		= 20.f;
			constexpr float DEFAULT_Y_BOTTOM	= -20.f;
			constexpr float DEFAULT_Y_TOP		= 20.f;
			constexpr float DEFAULT_Z_NEAR		= 1.f;
			constexpr float DEFAULT_Z_FAR		= 1000.f;
			constexpr float MAX_PITCH			= (glm::half_pi<float>() * .9f);
			constexpr float DEFAULT_FOV			= glm::quarter_pi<float>();
			constexpr float MAX_FOV				= (DEFAULT_FOV * 2.f);
			constexpr float MIN_FOV				= (DEFAULT_FOV * .3f);
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

		namespace Shadow
		{
			constexpr GLsizei DEFAULT_MAP_WIDTH		= 1024;
			constexpr GLsizei DEFAULT_MAP_HEIGHT	= 1024;
		}
	}
}