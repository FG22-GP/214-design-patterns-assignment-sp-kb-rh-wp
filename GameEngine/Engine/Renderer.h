#pragma once
#include <SDL_render.h>
#include <cstdio>
#include <SDL_hints.h>

class Renderer
{
public:
    Renderer(int width, int height);
    static SDL_Renderer* GetRenderer();

private:
    SDL_Renderer* renderer;
    SDL_Window* window{};

    inline static Renderer* instance = nullptr;
};
