#pragma once

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

		// Camera
		namespace Camera
		{
			constexpr float Z_NEAR		= 1.f;
			constexpr float Z_FAR		= 1000.f;
			constexpr float MAX_PITCH	= (glm::half_pi<float>() * .9f);
			constexpr float FOV			= glm::quarter_pi<float>();
			constexpr float MAX_FOV		= (FOV * 2.f);
			constexpr float MIN_FOV		= (FOV * .3f);
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
			constexpr GLfloat DEFAULT_GAMMA = 2.2f;
		}
	}
}