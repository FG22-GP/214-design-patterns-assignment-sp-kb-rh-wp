#pragma once
#include <SDL_render.h>
#include <cstdio>
#include <SDL_image.h>
#include <SDL_render.h>

#include "Renderer.h"

class Image
{
public:
    Image(const char* path, SDL_Point* position, SDL_Point* size);
    void Render();
    SDL_Point* position;
    SDL_Point* size;
    SDL_Texture* texture;
};
