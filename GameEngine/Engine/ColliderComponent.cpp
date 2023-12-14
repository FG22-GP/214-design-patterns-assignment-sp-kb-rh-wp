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

	//colliders->push_back(this);
}

void ColliderComponent::Update(float deltaTime)
{
	/*SDL_FPoint* position = new SDL_FPoint{parent->GetPosition()->x, parent->GetPosition()->y};

	for (auto it = colliders->begin(); it != colliders->end(); ++it)
	{
		ColliderComponent* other = (*it);

		if (other != this)
		{
			SDL_FPoint* otherPosition = new SDL_FPoint{ other->parent->GetPosition()->x, other->parent->GetPosition()->y };
			if (CirclesCollide(position->x, position->y, radius, otherPosition->x, otherPosition->y, other->radius))
			{
				for (auto it = other->parent->components->begin(); it != other->parent->components->end(); ++it)
				{
					auto healthComponent = dynamic_cast<HealthComponent*>((*it));

					if (healthComponent != NULL)
					{
						healthComponent->TakeDamage(10);
						break;
					}
				}
			}
		}
	}*/
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