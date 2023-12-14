#pragma once
#include "InputComponent.h"

class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent(float moveSpeed);
	virtual void Update(float deltaTime) override;
};

