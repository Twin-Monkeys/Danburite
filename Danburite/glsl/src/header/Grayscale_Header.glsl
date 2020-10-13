//? #version 460 core

#ifndef __GRAYSCALE_HEADER__
#define __GRAYSCALE_HEADER__

float Grayscale_getGrayscaledColor(const vec3 originalColor)
{
	return dot(vec3(.2126f, .7152f, .0722f), originalColor);
}

#endif