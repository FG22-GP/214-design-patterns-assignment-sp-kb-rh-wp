#pragma once
#include <SDL_rect.h>
#include <SDL_video.h>
#include <cmath>
#include <SDL.h>
#include "Renderer.h"

static SDL_FPoint* NormalizeVector(SDL_FPoint* point)
{
	float length = sqrt((point->x * point->x) + (point->y * point->y));
	if (length != 0)
	{
		point->x = point->x / length;
		point->y = point->y / length;
	}

	return point;
}