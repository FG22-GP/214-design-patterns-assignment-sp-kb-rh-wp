#pragma once
#include "Component.h"
#include <list>
#include <SDL_rect.h>
#include <unordered_map>

class HealthComponent;

class ColliderComponent : public Component
{
public:
	ColliderComponent(float radius, const char* tag, const char* tagToCheck = "");

	float radius;
	const char* tag;
	const char* tagToCheck;

	inline static std::list<ColliderComponent*>* colliders = new std::list<ColliderComponent*>();

	virtual void Update(float deltaTime) override;

	bool CirclesCollide(float x1, float y1, float r1, float x2, float y2, float r2);

	void Collided(const char* otherTag);
};