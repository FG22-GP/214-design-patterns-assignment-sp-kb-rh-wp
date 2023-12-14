#pragma once
#include "InputComponent.h"
#include <SDL_rect.h>

class AIInputComponent : public InputComponent
{
public:
	GameObject* target;

	AIInputComponent(GameObject* target, float moveSpeed);

	virtual void Update(float deltaTime) override;
};

