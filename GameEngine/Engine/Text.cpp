#include "Text.h"


Text::Text(const char* text, TTF_Font* font, const SDL_Color textColor, SDL_FPoint* position)
{
    if (font == nullptr)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    // render the text into an unoptimized CPU surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    size = new SDL_Point{textSurface->w, textSurface->h};
    if (textSurface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }
    // Create texture GPU-stored texture from surface pixels
    textTexture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), textSurface);
    if (textTexture == nullptr)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        return;
    }
    // Get image dimensions
    Text::position = position;

    //Get rid of old loaded surface
    SDL_FreeSurface(textSurface);

    uiObjects->push_back(this);
}

void Text::Render()
{
    // render the text
    const auto targetRectangle = SDL_Rect{
        static_cast<int>(position->x),
        static_cast<int>(position->y),
        (size->x),
        (size->y)
    };
    SDL_RenderCopy(Renderer::GetRenderer(), textTexture, nullptr, &targetRectangle);
}
