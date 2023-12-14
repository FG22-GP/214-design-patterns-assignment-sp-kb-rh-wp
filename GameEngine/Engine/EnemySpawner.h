#pragma once
#include <SDL_rect.h>

class GameObject;

class EnemySpawner
{
public:
	EnemySpawner(GameObject* target, float SpawnRate);
	void Update(float deltaTime);

private:
	float spawnRate;
	float spawnTimer;
	SDL_FPoint* enemySize = new SDL_FPoint{ 50, 50 };
	const char* charmanderImagePath{ "img/charmander.png" };
	GameObject* target;

	SDL_FPoint* RandomizeSpawnPosition();


	void Spawn();
};

