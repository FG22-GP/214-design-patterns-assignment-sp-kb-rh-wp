#pragma once

class GameObject;

class Component
{
public:
	Component();

	virtual void Update(float deltaTime);

	GameObject* parent;
};

