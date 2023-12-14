#pragma once

class GameObject;

class Component
{
public:
	Component();

	virtual void Update(float deltaTime);
	virtual void Destroyed() {};

	GameObject* parent;

	bool destroyTag;
};

