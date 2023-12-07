#include "Image.h"

Image::Image(const char* path, SDL_FPoint* position, SDL_FPoint* size)
{
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == nullptr)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return;
    }
    //Convert surface to screen format
    texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), loadedSurface);
    if (texture == nullptr)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        return;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    Image::position = position;
    Image::size = size;
}

void Image::Render()
{
    const SDL_Rect rectangle = {(position->x), (position->y), (size->x), (size->y)};
    SDL_RenderCopy(Renderer::GetRenderer(), texture, nullptr, &rectangle);
}
