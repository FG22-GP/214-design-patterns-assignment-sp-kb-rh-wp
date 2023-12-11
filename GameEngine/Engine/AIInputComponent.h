#pragma once
#include "InputComponent.h"
#include <SDL_rect.h>

class AIInputComponent : public InputComponent
{
public:
	GameObject* target;

	AIInputComponent(GameObject* target, float moveSpeed);

	virtual void Update(GameObject& gameObject, float deltaTime) override;
};

