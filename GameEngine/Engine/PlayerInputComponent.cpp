#include "PlayerInputComponent.h"
#include <SDL_keyboard.h>

#include <SDL_rect.h>

PlayerInputComponent::PlayerInputComponent(float moveSpeed)
{
    movementSpeed = moveSpeed;
}

void PlayerInputComponent::Update(float deltaTime)
{
    // This is an example for how to check, whether keys are currently pressed:
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    //printf("%f\n", deltaTime);

    if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
        movementDirection->y = 1;
    else if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S])
        movementDirection->y = -1;
    else
        movementDirection->y = 0;

    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
    {
        movementDirection->x = -1;
    }
    else if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
    {
        movementDirection->x = 1;
    }
    else
        movementDirection->x = 0;

    Move(deltaTime, false, true);
}