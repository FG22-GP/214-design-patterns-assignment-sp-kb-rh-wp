#pragma once
#include "Component.h"
#include "GameObject.h"

class AttackComponent : public Component
{
public:
	AttackComponent(float attackSpeed);

	const char* electroBallImagePath{ "img/electro_ball.png" };

	float attackSpeed;
	float attackTimer;

	SDL_FPoint* attackDirection;

	virtual void Update(float deltaTime) override;

	void SetAttackDirection();

	void Attack();
};

