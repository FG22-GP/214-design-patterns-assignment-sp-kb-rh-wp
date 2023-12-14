#pragma once
#include <SDL_render.h>
#include <cstdio>
#include <SDL_image.h>
#include <SDL_render.h>

#include "Renderer.h"

class Image
{
public:
    Image(const char* path, SDL_FPoint* position, SDL_FPoint* size, float angle = 0);
    void Render();
    SDL_FPoint* position = new SDL_FPoint{0, 0};
    SDL_FPoint* size = new SDL_FPoint{ 0, 0 };
    SDL_Texture* texture;

    float angle;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

};
