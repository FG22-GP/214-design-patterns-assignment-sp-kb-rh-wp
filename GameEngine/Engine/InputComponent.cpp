#include "InputComponent.h"

InputComponent::InputComponent()
{
	movementDirection = new SDL_FPoint{ 0, 0 };
}

void InputComponent::Move(GameObject& gameObject, float deltaTime)
{
	gameObject.Move(NormalizeVector(movementDirection), movementSpeed * deltaTime);
}
