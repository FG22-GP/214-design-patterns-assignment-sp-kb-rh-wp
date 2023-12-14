#include "AIInputComponent.h"
#include <cmath>

AIInputComponent::AIInputComponent(GameObject* target, float moveSpeed)
{
	this->target = target;
	movementSpeed = moveSpeed;
}

void AIInputComponent::Update(float deltaTime)
{
	if (target == nullptr) return;

	if (target->destroyTag)
	{
		target = nullptr;
		return;
	}

	SDL_FPoint* targetPosition = target->GetPosition();
	SDL_FPoint* currentPosition = parent->GetPosition();

	movementDirection->x = targetPosition->x - currentPosition->x;
	movementDirection->y = targetPosition->y - currentPosition->y;
	movementDirection->y *= -1;

	Move(deltaTime, true);
}