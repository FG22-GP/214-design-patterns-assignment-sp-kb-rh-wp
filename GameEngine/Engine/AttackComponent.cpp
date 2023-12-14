#include "AttackComponent.h"
#include "InputComponent.h"
#include "ColliderComponent.h"

AttackComponent::AttackComponent(float attackSpeed)
{
	this->attackSpeed = attackSpeed;
	attackDirection = new SDL_FPoint{ 0, 0 };
}

void AttackComponent::Update(float deltaTime)
{
	SetAttackDirection();

	if (attackTimer >= attackSpeed)
	{
		Attack();
		attackTimer = 0;
	}
	else
	{
		attackTimer += deltaTime;
	}
}

void AttackComponent::SetAttackDirection()
{
	auto* pos = parent->GetPosition();
	int x = 0;
	int y = 0;

	SDL_GetMouseState(&x, &y);

	attackDirection->x = x - pos->x;
	attackDirection->y = y - pos->y;
	attackDirection->y *= -1;

	if (attackDirection->x > 0)
	{
		parent->SetRotation(180, SDL_FLIP_VERTICAL);
	}
	else
	{
		parent->SetRotation(SDL_FLIP_NONE);
	}
}

void AttackComponent::Attack()
{
	auto* size = new SDL_FPoint{ 30, 30 };

	auto electroBall = GameObject::Instantiate(parent->GetPosition(), size, electroBallImagePath);

	InputComponent* input = new InputComponent();
	electroBall->AddComponent(input);
	electroBall->AddComponent(new ColliderComponent(12, "Bullet", "Enemy"));

	input->movementSpeed = 300;

	input->movementDirection->x = attackDirection->x;
	input->movementDirection->y = attackDirection->y;
}