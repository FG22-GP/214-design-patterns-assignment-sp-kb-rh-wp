#pragma once

class GameObject;

class Component
{
public:
	Component();

	virtual void Update(GameObject&, float deltaTime);
};

