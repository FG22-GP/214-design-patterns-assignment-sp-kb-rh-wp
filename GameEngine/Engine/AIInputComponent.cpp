#include "AIInputComponent.h"

#include <cmath>

AIInputComponent::AIInputComponent(GameObject* target, float moveSpeed)
{
	this->target = target;
	movementSpeed = moveSpeed;
}

void AIInputComponent::Update(GameObject& gameObject, float deltaTime)
{
	SDL_FPoint* targetPosition = target->GetPosition();
	SDL_FPoint* currentPosition = gameObject.GetPosition();

	movementDirection->x = targetPosition->x - currentPosition->x;
	movementDirection->y = targetPosition->y - currentPosition->y;
	movementDirection->y *= -1;

	Move(gameObject, deltaTime);
}