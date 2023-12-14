#include "InputComponent.h"

InputComponent::InputComponent()
{
	movementDirection = new SDL_FPoint{ 0, 0 };
}

void InputComponent::Update(float deltaTime)
{
	Move(deltaTime, true);
}

void InputComponent::FlipSprite()
{
	if (movementDirection->x > 1)
	{	
		parent->SetRotation(180, SDL_FLIP_VERTICAL);
	}
	else if (movementDirection->x < -1)
	{
		parent->SetRotation(SDL_FLIP_NONE);
	}
}

void InputComponent::Move(float deltaTime, bool flipSprite, bool clampToScreen)
{
	if (flipSprite)
	{
		FlipSprite();
	}

	parent->Move(NormalizeVector(movementDirection), movementSpeed * deltaTime, clampToScreen);
}