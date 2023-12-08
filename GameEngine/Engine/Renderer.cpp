#include "Renderer.h"


Renderer::Renderer(const int width, const int height)
{
    if (instance)
    {
        printf("Renderer already exists!\n");
        return;
    }
    instance = this;
    // Create Window and Renderer
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer);
    if (!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"); // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(renderer, 1024, 768);
}

SDL_Renderer* Renderer::GetRenderer()
{
    return instance->renderer;
}
