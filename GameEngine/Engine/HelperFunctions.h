#pragma once
#include <SDL_rect.h>
#include <cmath>

static SDL_FPoint* NormalizeVector(SDL_FPoint* point)
{
	float length = sqrt((point->x * point->x) + (point->y * point->y));
	if (length != 0)
	{
		point->x = point->x / length;
		point->y = point->y / length;
	}
	//SDL_FPoint* normalizedVector = new SDL_FPoint{ point->x / length, point->y / length };
	return point;
}