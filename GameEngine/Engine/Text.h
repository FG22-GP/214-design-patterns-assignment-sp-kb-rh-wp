#pragma once
#include <SDL_render.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "UiObject.h"

class Text : UiObject
{
public:
    Text(const char* text, TTF_Font* font, SDL_Color textColor, SDL_FPoint* position);
    void Render() override;

    SDL_Point* size;
    SDL_FPoint* position;

private:
    SDL_Texture* textTexture;
};
