//Using SDL and standard IO
#include <list>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Engine/GameObject.h"
#include "Engine/Image.h"
#include "Engine/Renderer.h"
#include "Engine/Text.h"

#include "Engine/PlayerInputComponent.h"
#include "Engine/AIInputComponent.h"
#include "Engine/ColliderComponent.h"
#include "Engine/HealthComponent.h"
#include "Engine/AttackComponent.h"
#include "Engine/CollisionSystem.h"

//Screen dimension constants
constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;

const char* pikachuImagePath{"img/pikachu.png"};
const char* charmanderImagePath{"img/charmander.png"};

Renderer* renderer = new Renderer(SCREEN_WIDTH, SCREEN_HEIGHT);

bool Initialize()
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
        return false;
    }

    return true;
}

void SpawnCharmanders(GameObject* pikachu, int amount)
{
    auto* cha_pos = new SDL_FPoint{ 0, 0 };
    auto* cha_size = new SDL_FPoint{ 50, 50 };

    for (int i = 0; i < amount; i++)
    {
        auto charmander = GameObject::Instantiate(cha_pos, cha_size, charmanderImagePath);

        charmander->AddComponent(new AIInputComponent(pikachu, 100));
        charmander->AddComponent(new HealthComponent(20, 1));
        charmander->AddComponent(new ColliderComponent(10, "Enemy", "Bullet"));
    }
}

GameObject* SpawnPlayer()
{
    auto* pik_pos = new SDL_FPoint{20, 20};
    auto* pik_size = new SDL_FPoint{50, 50};

    auto pikachu = GameObject::Instantiate(pik_pos, pik_size, pikachuImagePath);

    pikachu->AddComponent(new HealthComponent(100, 1));
    pikachu->AddComponent(new ColliderComponent(10, "Player"));
    pikachu->AddComponent(new AttackComponent(1));
    pikachu->AddComponent(new PlayerInputComponent(200));

    return pikachu;
}

void SetUpCollisionSystem()
{
    std::array<const char*, 3> tags = { "Player", "Enemy", "Bullet" };

    new CollisionSystem(tags);
}

int main(int argc, char* args[])
{
    if (!Initialize()) return -1;

    SetUpCollisionSystem();

    GameObject* pikachu = SpawnPlayer();

    SpawnCharmanders(pikachu, 1);

    // load font
    auto font = TTF_OpenFont("font/lazy.ttf", 100);
    if (font == nullptr)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    // create text from font
    SDL_Color textColor = {0xff, 0xff, 0xff};

    auto text = new Text("Hej hej", font, textColor, new SDL_FPoint{50, 0});

    SDL_Event e;
    bool quit = false;
    auto prevTime = SDL_GetTicks64();

    // while the user doesn't want to quit
    while (quit == false)
    {
        const Uint8* keystate = SDL_GetKeyboardState(nullptr);
        if (keystate[SDL_SCANCODE_ESCAPE])
        {
            quit = true;
        }

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

        GameObject::UpdateAll(deltaTime);
        CollisionSystem::Update(deltaTime);

        // clear the screen
        SDL_SetRenderDrawColor(Renderer::GetRenderer(), 120, 60, 255, 255);
        SDL_RenderClear(Renderer::GetRenderer());

        GameObject::RenderAll();
        UiObject::RenderAll();

        // present screen (switch buffers)
        SDL_RenderPresent(Renderer::GetRenderer());

        GameObject::DeleteDestroyedGameObjects();

        SDL_Delay(0); // can be used to wait for a certain amount of ms
    }

    return 0;
}
