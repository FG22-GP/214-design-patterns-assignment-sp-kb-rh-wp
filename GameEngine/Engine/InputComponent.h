#pragma once
#include "Component.h"
#include "HelperFunctions.h"
#include "GameObject.h"

class InputComponent : public Component
{

public:
	InputComponent();
	virtual void Update(float deltaTime);
	SDL_FPoint* movementDirection;
	float movementSpeed;

	void FlipSprite();
	void Move(float deltaTime, bool flipSprite = false, bool clampToScreen = false);
};

