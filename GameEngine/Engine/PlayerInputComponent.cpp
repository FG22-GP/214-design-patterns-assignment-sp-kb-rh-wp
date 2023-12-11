#include "PlayerInputComponent.h"
#include <SDL_keyboard.h>

#include <SDL_rect.h>

PlayerInputComponent::PlayerInputComponent(float moveSpeed)
{
    movementSpeed = moveSpeed;
}

void PlayerInputComponent::Update(GameObject& gameObject, float deltaTime)
{
    // This is an example for how to check, whether keys are currently pressed:
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    printf("%f\n", deltaTime);

    if (keystate[SDL_SCANCODE_UP])
        movementDirection->y = 1;
    else if (keystate[SDL_SCANCODE_DOWN])
        movementDirection->y = -1;
    else
        movementDirection->y = 0;

    if (keystate[SDL_SCANCODE_LEFT])
        movementDirection->x = -1;
    else if (keystate[SDL_SCANCODE_RIGHT])
        movementDirection->x = 1;
    else
        movementDirection->x = 0;

    Move(gameObject, deltaTime);
}

void PlayerInputComponent::ApplyMovement(GameObject& gameObject, float deltaTime, SDL_FPoint* direction)
{
    gameObject.Move(NormalizeVector(direction), 100 * deltaTime);
}
