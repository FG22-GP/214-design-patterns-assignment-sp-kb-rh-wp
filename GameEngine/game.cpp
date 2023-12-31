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
#include "Engine/EnemySpawner.h"

//Screen dimension constants
constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;

const char* pikachuImagePath{"img/pikachu.png"};

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


GameObject* SpawnPlayer()
{
    auto* pik_size = new SDL_FPoint{50, 50};

    int maxX, maxY;

    SDL_RenderGetLogicalSize(Renderer::GetRenderer(), &maxX, &maxY);

    auto* pik_pos = new SDL_FPoint{(float) maxX / 2 - pik_size->x / 2, (float) maxY / 2 - pik_size->y / 2};

    auto pikachu = GameObject::Instantiate(pik_pos, pik_size, pikachuImagePath);

    pikachu->AddComponent(new HealthComponent(100, 0.3f));
    pikachu->AddComponent(new ColliderComponent(15, "Player", "Enemy"));
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

    EnemySpawner* enemySpawner = new EnemySpawner(pikachu, 3);

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
        
        // loop through all pending events from Windows (OS)
        while (SDL_PollEvent(&e)) { }

        enemySpawner->Update(deltaTime);
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
