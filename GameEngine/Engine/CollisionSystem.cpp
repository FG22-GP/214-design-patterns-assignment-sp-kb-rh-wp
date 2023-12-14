#include "CollisionSystem.h"
#include "GameObject.h"

void CollisionSystem::Update(float deltaTime)
{
	for (auto it = colliders->begin(); it != colliders->end(); ++it) 
	{
		ColliderComponent* collider = (*it);

		if (collider->parent->destroyTag) continue;

		if (!colliderMap.contains(collider->tagToCheck)) continue;
		
		auto listToCheck = colliderMap.at(collider->tagToCheck);

		for (auto other = listToCheck->begin(); other != listToCheck->end(); ++other)
		{
			ColliderComponent* otherCollider = (*other);

			if (collider->parent->destroyTag) break;
			if (otherCollider->parent->destroyTag) continue;

			if (collider != otherCollider)
			{
				SDL_FPoint* position = collider->parent->GetCenterPosition();
				SDL_FPoint* otherPosition = otherCollider->parent->GetCenterPosition();

				if (CirclesCollide(position->x, position->y, collider->radius, otherPosition->x, otherPosition->y, otherCollider->radius))
				{
					collider->Collided(otherCollider->tag);
				}
			}
		}
	}
}

bool CollisionSystem::CirclesCollide(float x1, float y1, float r1, float x2, float y2, float r2)
{
	return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) < r1 * r2;
}

void CollisionSystem::AddCollider(const char* tag, ColliderComponent* colliderComponent)
{
	colliderMap.at(tag)->push_back(colliderComponent);
	colliders->push_back(colliderComponent);
}