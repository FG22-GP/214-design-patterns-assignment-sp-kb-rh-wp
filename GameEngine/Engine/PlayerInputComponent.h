#pragma once
#include "InputComponent.h"

class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent(float moveSpeed);
	virtual void Update(GameObject& gameObject, float deltaTime) override;

private:
	void ApplyMovement(GameObject& gameObject, float deltaTime, SDL_FPoint* direction);
};

