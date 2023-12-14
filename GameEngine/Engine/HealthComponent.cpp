#include "HealthComponent.h"
#include <stdio.h>
#include "GameObject.h"

HealthComponent::HealthComponent(int health, float invincibilityFrames)
{
	this->health = health;
	this->invincibilityFrames = invincibilityFrames;
}

void HealthComponent::TakeDamage(int damage)
{
	if (invincible) return;

	health -= damage;

	if (health <= 0)
	{
		parent->DestroyGameObject();
	}

	invincible = true;
}

void HealthComponent::Update(float deltaTime)
{
	if (!invincible) return;

	if (timer >= invincibilityFrames)
	{
		invincible = false;
		timer = 0;
	}
	else
	{
		timer += deltaTime;
	}
}