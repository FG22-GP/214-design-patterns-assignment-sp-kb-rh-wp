#include "ColliderComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "CollisionSystem.h"

ColliderComponent::ColliderComponent(float radius, const char* tag, const char* tagToCheck)
{
	this->radius = radius;
	this->tag = tag;
	this->tagToCheck = tagToCheck;
	
	CollisionSystem::AddCollider(tag, this);
}

void ColliderComponent::Destroyed()
{
	CollisionSystem::RemoveCollider(tag, this);
}

void ColliderComponent::Update(float deltaTime)
{
	
}

bool ColliderComponent::CirclesCollide(float x1, float y1, float r1, float x2, float y2, float r2)
{
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) < r1 * r2;
}

void ColliderComponent::Collided(const char* otherTag)
{
	if (tag == "Player")
	{
		for (auto it = parent->components->begin(); it != parent->components->end(); ++it)
		{
			auto healthComponent = dynamic_cast<HealthComponent*>((*it));

			if (healthComponent != NULL)
			{
				healthComponent->TakeDamage(10);
				break;
			}
		}
	}
	else if(tag == "Enemy")
	{
		for (auto it = parent->components->begin(); it != parent->components->end(); ++it)
		{
			auto healthComponent = dynamic_cast<HealthComponent*>((*it));

			if (healthComponent != NULL)
			{
				healthComponent->TakeDamage(10);
				break;
			}
		}
	}
	else if (tag == "Bullet")
	{
		parent->DestroyGameObject();
	}
}