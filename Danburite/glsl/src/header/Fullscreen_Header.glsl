//? #version 460 core

#ifndef __FULLSCREEN_HEADER__
#define __FULLSCREEN_HEADER__

vec2 Fullscreen_getTexCoord(const int vertexID)
{
	vec2 retVal;
	retVal.x = float(((vertexID + 2) / 3) % 2);
    retVal.y = float(((vertexID + 1) / 3) % 2);

	return retVal;
}

vec4 Fullscreen_getPosition(const vec2 texCoord)
{
    return vec4(-1.f + (texCoord.x * 2.f), -1.f + (texCoord.y * 2.f), 0.f, 1.f);
}

vec4 Fullscreen_getPosition(const int vertexID)
{
    return Fullscreen_getPosition(Fullscreen_getTexCoord(vertexID));
}

#endif