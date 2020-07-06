//? #version 460 core

#ifndef __GRAYSCALE_HEADER__
#define __GRAYSCALE_HEADER__

float Grayscale_getGrayscaledColor(const vec3 originalColor)
{
	return ((.2126f * originalColor.r) + (.7152f * originalColor.g) + (.0722f * originalColor.b));
}

#endif