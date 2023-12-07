#pragma once
#include <SDL_render.h>
#include <cstdio>
#include <SDL_image.h>
#include <SDL_render.h>

#include "Renderer.h"

class Image
{
public:
    Image(const char* path, SDL_FPoint* position, SDL_FPoint* size);
    void Render();
    SDL_FPoint* position;
    SDL_FPoint* size;
    SDL_Texture* texture;
};
