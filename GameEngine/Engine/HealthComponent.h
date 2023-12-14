#pragma once
#include "Component.h"
class HealthComponent : public Component
{
public:
	HealthComponent(int health, float invincibilityFrames);

	int health;
	float invincibilityFrames;

	float timer;

	bool invincible;

	void TakeDamage(int damage);

	virtual void Update(float deltaTime) override;
};

