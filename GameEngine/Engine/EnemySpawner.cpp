#include "EnemySpawner.h"
#include "GameObject.h"
#include "AIInputComponent.h"
#include "HealthComponent.h"
#include "ColliderComponent.h"

EnemySpawner::EnemySpawner(GameObject* target, float spawnRate)
{
	this->spawnRate = spawnRate;
	this->target = target;
}

void EnemySpawner::Update(float deltaTime)
{
	if (spawnTimer >= spawnRate)
	{
		Spawn();
		spawnTimer = 0;
	}
	else
	{
		spawnTimer += deltaTime;
	}
}

void EnemySpawner::Spawn()
{
	auto charmander = GameObject::Instantiate(RandomizeSpawnPosition(), enemySize, charmanderImagePath);

	charmander->AddComponent(new AIInputComponent(target, 100));
	charmander->AddComponent(new HealthComponent(20, 1));
	charmander->AddComponent(new ColliderComponent(15, "Enemy", "Bullet"));
}

SDL_FPoint* EnemySpawner::RandomizeSpawnPosition()
{
	int side = rand() % 4;

	int maxX, maxY;

	SDL_RenderGetLogicalSize(Renderer::GetRenderer(), &maxX, &maxY);

	float x, y;

	switch (side)
	{
		case 0:
			x = rand() % maxX;
			y = 0;
		break;
		case 1:
			x = maxX;
			y = rand() % maxY;
		break;
		case 2:
			x = rand() % maxX;
			y = maxY;
			break;
		case 3:
			x = 0;
			y = rand() % maxY;
			break;
	}
	
	return new SDL_FPoint{x, y};
}