#pragma once
#include "ColliderComponent.h"
#include <unordered_map>
#include <array>
#include <iostream>
#include "HelperFunctions.h"

class CollisionSystem
{
public:
	template<std::size_t SIZE>
	CollisionSystem(std::array<const char*, SIZE> tags)
	{
		for (auto tag : tags)
		{
			auto list = new std::list<ColliderComponent*>();
			colliderMap.insert_or_assign(tag, list);
		}
	}

	static void Update(float deltaTime);

	static void AddCollider(const char* tag, ColliderComponent* colliderComponent);

	static void RemoveCollider(const char* tag, ColliderComponent* colliderComponent);

private:
	static bool CirclesCollide(float x1, float y1, float r1, float x2, float y2, float r2);


	inline static std::list<ColliderComponent*>* colliders = new std::list<ColliderComponent*>();

	inline static std::unordered_map<const char*, std::list<ColliderComponent*>*> colliderMap;
};
