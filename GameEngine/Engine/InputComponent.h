#pragma once
#include "Component.h"
#include "HelperFunctions.h"
#include "GameObject.h"

class InputComponent : Component
{

public:
	InputComponent();
	virtual void Update(GameObject& gameObject, float deltaTime) {};
	SDL_FPoint* movementDirection;
	float movementSpeed;
	void Move(GameObject& gameObject, float deltaTime);
};

