//Using SDL and standard IO
#include <list>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Engine/GameObject.h"
#include "Engine/Image.h"
#include "Engine/Renderer.h"

//Screen dimension constants
constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;

const char* pikachuImagePath{"img/pikachu.png"};

int main(int argc, char* args[])
{
    // initialize SDL_Image for image loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    // initialize SDL_ttf for font loading
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

    //Start up SDL and create window
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    auto renderer = new Renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

    auto* pik_pos = new SDL_FPoint{0, 0};
    auto* pik_size = new SDL_FPoint{50, 50};

    auto pikachu = GameObject::Instantiate(pik_pos, pik_size, pikachuImagePath);

    // load font
    auto font = TTF_OpenFont("font/lazy.ttf", 100);
    if (font == nullptr)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    // create text from font
    SDL_Color textColor = {0xff, 0xff, 0xff};
    //Render text surface
    SDL_Texture* textTexture; // The final optimized image

    // render the text into an unoptimized CPU surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "The lazy fox, blah blah", textColor);
    int textWidth, textHeight;
    if (textSurface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }
    // Create texture GPU-stored texture from surface pixels
    textTexture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), textSurface);
    if (textTexture == nullptr)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        return -1;
    }
    // Get image dimensions
    auto width = textSurface->w;
    auto height = textSurface->h;
    textWidth = textSurface->w;
    textHeight = textSurface->h;
    //Get rid of old loaded surface
    SDL_FreeSurface(textSurface);

    SDL_Event e;
    bool quit = false;
    auto prevTime = SDL_GetTicks64();

    // while the user doesn't want to quit
    while (quit == false)
    {
        const auto currentTime = SDL_GetTicks64();
        const float deltaTime = (currentTime - prevTime) / 1000.0f;
        prevTime = currentTime;
        // can be used, to see, how much time in ms has passed since app start


        // loop through all pending events from Windows (OS)
        while (SDL_PollEvent(&e))
        {
            // check, if it's an event we want to react to:
            switch (e.type)
            {
            case SDL_QUIT:
                {
                    quit = true;
                }
                break;

            // This is an example on how to use input events:
            case SDL_KEYDOWN:
                {
                    // input example: if left, then make pikachu move left
                    if (e.key.keysym.sym == SDLK_LEFT)
                    {
                    }
                    // if right, then make pikachu move right
                    if (e.key.keysym.sym == SDLK_RIGHT)
                    {
                    }
                }
                break;
            }
        }

        // This is an example for how to check, whether keys are currently pressed:
        const Uint8* keystate = SDL_GetKeyboardState(nullptr);
        printf("%f\n", deltaTime);
        if (keystate[SDL_SCANCODE_UP])
        {
            pikachu->Move(new SDL_FPoint{0, 1}, 100 * deltaTime);
        }
        if (keystate[SDL_SCANCODE_DOWN])
        {
            pikachu->Move(new SDL_FPoint{0, -1}, 100 * deltaTime);
        }
        if (keystate[SDL_SCANCODE_LEFT])
        {
            pikachu->Move(new SDL_FPoint{-1, 0}, 100 * deltaTime);
        }
        if (keystate[SDL_SCANCODE_RIGHT])
        {
            pikachu->Move(new SDL_FPoint{1, 0}, 100 * deltaTime);
        }

        GameObject::UpdateAll(deltaTime);

        // clear the screen
        SDL_SetRenderDrawColor(Renderer::GetRenderer(), 120, 60, 255, 255);
        SDL_RenderClear(Renderer::GetRenderer());

        GameObject::RenderAll();

        // render the text
        auto targetRectangle = SDL_Rect{
            500,
            500,
            textWidth,
            textHeight
        };
        SDL_RenderCopy(Renderer::GetRenderer(), textTexture, nullptr, &targetRectangle);

        // present screen (switch buffers)
        SDL_RenderPresent(Renderer::GetRenderer());

        SDL_Delay(0); // can be used to wait for a certain amount of ms
    }

    return 0;
}
